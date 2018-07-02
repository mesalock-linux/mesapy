#include "common_header.h"
#include "structdef.h"       /* for struct pypy_threadlocal_s */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "src/threadlocal.h"


/* this is a spin-lock that must be acquired around each doubly-linked-list
   manipulation (because such manipulations can occur without the GIL) */
static long pypy_threadlocal_lock = 0;

static int check_valid(void);

#ifdef _WIN32
= TLS_OUT_OF_INDEXES
#endif
;

static struct pypy_threadlocal_s linkedlist_head = {
    -1,                     /* ready     */
    NULL,                   /* stack_end */
    &linkedlist_head,       /* prev      */
    &linkedlist_head };     /* next      */

static int check_valid(void)
{
    struct pypy_threadlocal_s *prev, *cur;
    prev = &linkedlist_head;
    while (1) {
        cur = prev->next;
        assert(cur->prev == prev);
        if (cur == &linkedlist_head)
            break;
        assert(cur->ready == 42);
        assert(cur->next != cur);
        prev = cur;
    }
    assert(cur->ready == -1);
    return 1;
}

static void cleanup_after_fork(void)
{
    /* assume that at most one pypy_threadlocal_s survived, the current one */
    struct pypy_threadlocal_s *cur;
    cur = (struct pypy_threadlocal_s *)_RPy_ThreadLocals_Get();
    if (cur && cur->ready == 42) {
        cur->next = cur->prev = &linkedlist_head;
        linkedlist_head.next = linkedlist_head.prev = cur;
    }
    else {
        linkedlist_head.next = linkedlist_head.prev = &linkedlist_head;
    }
}


struct pypy_threadlocal_s *
_RPython_ThreadLocals_Enum(struct pypy_threadlocal_s *prev)
{
    if (prev == NULL)
        prev = &linkedlist_head;
    if (prev->next == &linkedlist_head)
        return NULL;
    return prev->next;
}

struct pypy_threadlocal_s *_RPython_ThreadLocals_Head(void)
{
    return &linkedlist_head;
}

static void _RPy_ThreadLocals_Init(void *p)
{
    struct pypy_threadlocal_s *tls = (struct pypy_threadlocal_s *)p;
    struct pypy_threadlocal_s *oldnext;
    memset(p, 0, sizeof(struct pypy_threadlocal_s));

#ifdef RPY_TLOFS_p_errno
    tls->p_errno = &errno;
#endif
#ifdef RPY_TLOFS_thread_ident
    tls->thread_ident =
#    ifdef _WIN32
        GetCurrentThreadId();
#    else
        (long)pthread_self();    /* xxx This abuses pthread_self() by
                  assuming it just returns a integer.  According to
                  comments in CPython's source code, the platforms
                  where it is not the case are rather old nowadays. */
#    endif
#endif
    oldnext = linkedlist_head.next;
    tls->prev = &linkedlist_head;
    tls->next = oldnext;
    linkedlist_head.next = tls;
    oldnext->prev = tls;
    tls->ready = 42;
}

static void threadloc_unlink(void *p)
{
    /* warning: this can be called at completely random times without
       the GIL. */
    struct pypy_threadlocal_s *tls = (struct pypy_threadlocal_s *)p;
    if (tls->ready == 42) {
        tls->next->prev = tls->prev;
        tls->prev->next = tls->next;
        memset(tls, 0xDD, sizeof(struct pypy_threadlocal_s));  /* debug */
        tls->ready = 0;
    }
#ifndef USE___THREAD
    free(p);
#endif
}

#ifdef _WIN32
/* xxx Defines a DllMain() function.  It's horrible imho: it only
   works if we happen to compile a DLL (not a EXE); and of course you
   get link-time errors if two files in the same DLL do the same.
   There are some alternatives known, but they are horrible in other
   ways (e.g. using undocumented behavior).  This seems to be the
   simplest, but feel free to fix if you need that.

   For this reason we have the line 'not _win32 or config.translation.shared'
   in rpython.rlib.rthread.
*/
BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD     reason_for_call,
                    LPVOID    reserved)
{
    LPVOID p;
    switch (reason_for_call) {
    case DLL_THREAD_DETACH:
        if (pypy_threadlocal_key != TLS_OUT_OF_INDEXES) {
            p = TlsGetValue(pypy_threadlocal_key);
            if (p != NULL) {
                TlsSetValue(pypy_threadlocal_key, NULL);
                threadloc_unlink(p);
            }
        }
        break;
    default:
        break;
    }
    return TRUE;
}
#endif

/* ------------------------------------------------------------ */
#ifdef USE___THREAD
/* ------------------------------------------------------------ */


/* in this situation, we always have one full 'struct pypy_threadlocal_s'
   available, managed by gcc. */
__thread struct pypy_threadlocal_s pypy_threadlocal;

char *_RPython_ThreadLocals_Build(void)
{
    RPyAssert(pypy_threadlocal.ready == 0, "unclean thread-local");
    _RPy_ThreadLocals_Init(&pypy_threadlocal);

    /* we also set up &pypy_threadlocal as a POSIX thread-local variable,
       because we need the destructor behavior. */

    return (char *)&pypy_threadlocal;
}

void RPython_ThreadLocals_ThreadDie(void)
{
    threadloc_unlink(&pypy_threadlocal);
}


/* ------------------------------------------------------------ */
#else
/* ------------------------------------------------------------ */


/* this is the case where the 'struct pypy_threadlocal_s' is allocated
   explicitly, with malloc()/free(), and attached to (a single) thread-
   local key using the API of Windows or pthread. */



/* ------------------------------------------------------------ */
#endif
/* ------------------------------------------------------------ */
