
# Package initialisation
from pypy.interpreter.mixedmodule import MixedModule

class Module(MixedModule):
    appleveldefs = {
       'mesatee_appdefs' : 'app_mesatee.mesatee_appdefs'
    }

    interpleveldefs = {
       'mesatee_read_file'                      : 'interp_mesatee.mesatee_read_file',
       'mesatee_save_file_for_task_creator'     : 'interp_mesatee.mesatee_save_file_for_task_creator',
       'mesatee_save_file_for_all_participants' : 'interp_mesatee.mesatee_save_file_for_all_participants',
       'mesatee_save_file_for_file_owner'       : 'interp_mesatee.mesatee_save_file_for_file_owner',
}

