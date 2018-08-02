# Formal Verification of MesaPy: Towards Verifying RPython Translator/JIT and Libraries

Since there are still several unavoidable C code in the MesaPy's codebase, we
seek to formally verify these code to guarantee their memory safety. These C
code are located in RPython's translator/JIT backends and its libraries.
To cross validate our verification results, We utilize three state-of-the-art
verification tools --
[Seahorn](http://seahorn.github.io/blog/),
[Smack](https://github.com/smackers/smack), and
[TIS](https://trust-in-soft.com/) to
prove conclusively that the memory safety issues can never occur.

The memory safety issues in our current checks include

* Buffer overflow
* Buffer over-read
* Null pointer dereference
* Memory leak

## Verification tools

Here are three verification tools:

  - **Seahorn**: leverages the SMT solver and Abstract Interpretation techniques to
    check memory safte issues. http://seahorn.github.io/blog/

  - **SMACK**: translates the LLVM compiler's popular intermediate representation
    (IR) into the Boogie intermediate verification language (IVL), and leverages
    the Boogie and Corral verifiers for memory safety checks.
    https://github.com/smackers/smack

  - **TrustInSoft Analyzer**: uses formal methods to deliver mathematical
    guarantees. With an extensible framework that enables collaboration between
    different formal methods, TrustInSoft Analyzer can mathematically guarantee
    that a given flaw is not present in your source code.
    https://trust-in-soft.com/

## List of C sources and functions embedded in Python

We aim to formally verify all C code in MesaPy. Here is a list of all C sources
(except code for Windows platform).

  - `rpython/jit/backend/llsupport/src/codemap.c`
  - `rpython/jit/backend/llsupport/src/skiplist.c`
  - `rpython/translator/c/gcc/test/elf64/track_jumptable.c`
  - `rpython/translator/c/src/threadlocal.c`
  - `rpython/translator/c/src/exception.c`
  - `rpython/translator/c/src/entrypoint.c`
  - `rpython/translator/c/src/signals.c`
  - `rpython/translator/c/src/stacklet/tests.c`
  - `rpython/translator/c/src/stacklet/stacklet.c`
  - `rpython/translator/c/src/mem.c`
  - `rpython/translator/c/src/profiling.c`
  - `rpython/translator/c/src/ll_math.c`
  - `rpython/translator/c/src/thread_pthread.c`
  - `rpython/translator/c/src/stack.c`
  - `rpython/translator/c/src/int.c`
  - `rpython/translator/c/src/thread.c`
  - `rpython/translator/c/src/asm.c`
  - `rpython/translator/c/src/support.c`
  - `rpython/translator/c/src/instrument.c`
  - `rpython/translator/c/src/dtoa.c`
  - `rpython/translator/c/src/debug_print.c`
  - `rpython/translator/c/src/debug_traceback.c`
  - `rpython/translator/c/src/asm_gcc_x86.c`
  - `rpython/translator/c/src/ll_strtod.c`
  - `rpython/translator/c/src/rtyper.c`

We also found that besides above C sources, there are some C functions embedded
in Python sources. When building MesaPy, the embedded functions will be filled into
cache files for later building and linking. Therefore, we also consider to verify
these C functions to make sure all possible C source code are verified.

  - `${PYPY_USESSION_DIR}/module_cache/module_22.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_23.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_24.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_25.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_26.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_27.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_28.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_29.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_30.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_31.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_32.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_33.c`
  - `${PYPY_USESSION_DIR}/module_cache/module_34.c`

In each directory of verification tools, we also list C sources and functions we
have already verified.

## Potential Vulnerabilites in RPython Backend

```
static Bigint *
Balloc(int k)
{
    int x;
    Bigint *rv;
    unsigned int len;

    if (0<=k <= Kmax && (rv = freelist[k]))
        freelist[k] = rv->next;
    else {
        x = 1 << k;  -----------------------------> potential Integer Overflow
        len = (sizeof(Bigint) + (x-1)*sizeof(ULong) + sizeof(double) - 1)
            /sizeof(double);
        if (k <= Kmax && pmem_next - private_mem + len <= PRIVATE_mem) {
            rv = (Bigint*)pmem_next;
            pmem_next += len;
        }
        else {
            rv = (Bigint*)MALLOC(len*sizeof(double));
            if (rv == NULL)
                return NULL;
        }
        rv->k = k;
        rv->maxwds = x;
    }
    rv->sign = rv->wds = 0;
    return rv;
}
```

Above example locates in dtoa.c, and it shows there could be a potential Integer Overflow at labeled line. K could be any value including these greater than 32. In such case, x will be overflowed.

```
RPY_EXTERN
long *pypy_jit_codemap_del(unsigned long addr, unsigned int size)
{
    unsigned long search_key = addr + size - 1;
    long *result;
    skipnode_t *node;

    /* There should be either zero or one codemap entry in the range.
       In theory it should take the complete range, but for alignment
       reasons the [addr, addr+size] range can be slightly bigger. */
    node = skiplist_search(&jit_codemap_head, search_key); 

    pypy_codemap_invalid_set(1);
    skiplist_remove(&jit_codemap_head, node->key);  -----------> Invalid memory access
    pypy_codemap_invalid_set(0);

    /* there should be at most one */
    assert(skiplist_search(&jit_codemap_head, search_key)->key < addr);

    result = ((codemap_data_t *)node->data)->bytecode_info;
    free(node);
    return result;
}
```
Above example locates in codemap.c. It shows a potential invalid memory access. skiplist_search could return NULL, and node could be NULL. As a result, node->key will cause a crash. 