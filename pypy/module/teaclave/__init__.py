
# Package initialisation
from pypy.interpreter.mixedmodule import MixedModule
import pypy.module._io.interp_io

class Module(MixedModule):
    appleveldefs = {
    }

    interpleveldefs = {
        'open' : 'pypy.module._io.interp_io.open',
    }
