from pypy.interpreter.mixedmodule import MixedModule
from rpython.rlib import rposix

import os
exec 'import %s as posix' % os.name

class Module(MixedModule):
    """This module provides access to operating system functionality that is
standardized by the C Standard and the POSIX standard (a thinly
disguised Unix interface).  Refer to the library manual and
corresponding Unix manual entries for more information on calls."""

    applevel_name = os.name

    appleveldefs = {
        'error': 'app_posix.error',
        'stat_result': 'app_posix.stat_result',
        'statvfs_result': 'app_posix.statvfs_result',
        'fdopen': 'app_posix.fdopen',
        'tmpfile': 'app_posix.tmpfile',
        'popen': 'app_posix.popen',
        'tmpnam': 'app_posix.tmpnam',
        'tempnam': 'app_posix.tempnam',
    }
    if os.name == 'nt':
        appleveldefs.update({
            'popen2': 'app_posix.popen2',
            'popen3': 'app_posix.popen3',
            'popen4': 'app_posix.popen4',
            'startfile': 'app_startfile.startfile',
        })

    interpleveldefs = {
        'open': 'interp_posix.open',
        'lseek': 'interp_posix.lseek',
        'write': 'interp_posix.write',
        'isatty': 'interp_posix.isatty',
        'read': 'interp_posix.read',
        'close': 'interp_posix.close',
        'closerange': 'interp_posix.closerange',

        'fstat': 'interp_posix.fstat',
        'stat': 'interp_posix.stat',
        'lstat': 'interp_posix.lstat',
        'stat_float_times': 'interp_posix.stat_float_times',

        'getcwd': 'interp_posix.getcwd',
        'getcwdu': 'interp_posix.getcwdu',
#        'environ': 'interp_posix.get(space).w_environ',
        'strerror': 'interp_posix.strerror',
        '_statfields': 'interp_posix.getstatfields(space)',
        'urandom': 'interp_posix.urandom',
    }

    if hasattr(posix, '_getfullpathname'):
        interpleveldefs['_getfullpathname'] = 'interp_posix._getfullpathname'


    def startup(self, space):
        from pypy.module.posix import interp_posix
        interp_posix.get(space).startup(space)

for constant in dir(os):
    value = getattr(os, constant)
    if constant.isupper() and type(value) is int:
        Module.interpleveldefs[constant] = "space.wrap(%s)" % value
