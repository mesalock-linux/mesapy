class SGXStatus:
    SGX_SUCCESS                  = 0x00000000

    SGX_ERROR_UNEXPECTED         = 0x00000001      # Unexpected error
    SGX_ERROR_INVALID_PARAMETER  = 0x00000002      # The parameter is incorrect
    SGX_ERROR_OUT_OF_MEMORY      = 0x00000003      # Not enough memory is available to complete this operation
    SGX_ERROR_ENCLAVE_LOST       = 0x00000004      # Enclave lost after power transition or used in child process created by linux:fork()
    SGX_ERROR_INVALID_STATE      = 0x00000005      # SGX API is invoked in incorrect order or state

    SGX_ERROR_INVALID_FUNCTION   = 0x00001001      # The ecall/ocall index is invalid
    SGX_ERROR_OUT_OF_TCS         = 0x00001003      # The enclave is out of TCS
    SGX_ERROR_ENCLAVE_CRASHED    = 0x00001006      # The enclave is crashed
    SGX_ERROR_ECALL_NOT_ALLOWED  = 0x00001007      # The ECALL is not allowed at this time, e.g. ecall is blocked by the dynamic entry table, or nested ecall is not allowed during initialization
    SGX_ERROR_OCALL_NOT_ALLOWED  = 0x00001008      # The OCALL is not allowed at this time, e.g. ocall is not allowed during exception handling
    SGX_ERROR_STACK_OVERRUN      = 0x00001009      # The enclave is running out of stack

    SGX_ERROR_UNDEFINED_SYMBOL      = 0x00002000      # The enclave image has undefined symbol.
    SGX_ERROR_INVALID_ENCLAVE       = 0x00002001      # The enclave image is not correct.
    SGX_ERROR_INVALID_ENCLAVE_ID    = 0x00002002      # The enclave id is invalid
    SGX_ERROR_INVALID_SIGNATURE     = 0x00002003      # The signature is invalid
    SGX_ERROR_NDEBUG_ENCLAVE        = 0x00002004      # The enclave is signed as product enclave, and can not be created as debuggable enclave.
    SGX_ERROR_OUT_OF_EPC            = 0x00002005      # Not enough EPC is available to load the enclave
    SGX_ERROR_NO_DEVICE             = 0x00002006      # Can't open SGX device
    SGX_ERROR_MEMORY_MAP_CONFLICT   = 0x00002007      # Page mapping failed in driver
    SGX_ERROR_INVALID_METADATA      = 0x00002009      # The metadata is incorrect.
    SGX_ERROR_DEVICE_BUSY           = 0x0000200c      # Device is busy, mostly EINIT failed.
    SGX_ERROR_INVALID_VERSION       = 0x0000200d      # Metadata version is inconsistent between uRTS and sgx_sign or uRTS is incompatible with current platform.
    SGX_ERROR_MODE_INCOMPATIBLE     = 0x0000200e      # The target enclave 32/64 bit mode or sim/hw mode is incompatible with the mode of current uRTS.
    SGX_ERROR_ENCLAVE_FILE_ACCESS   = 0x0000200f      # Can't open enclave file.
    SGX_ERROR_INVALID_MISC          = 0x00002010      # The MiscSelct/MiscMask settings are not correct.
    SGX_ERROR_INVALID_LAUNCH_TOKEN  = 0x00002011      # The launch token is not correct.

    SGX_ERROR_MAC_MISMATCH       = 0x00003001      # Indicates verification error for reports, sealed datas, etc
    SGX_ERROR_INVALID_ATTRIBUTE  = 0x00003002      # The enclave is not authorized
    SGX_ERROR_INVALID_CPUSVN     = 0x00003003      # The cpu svn is beyond platform's cpu svn value
    SGX_ERROR_INVALID_ISVSVN     = 0x00003004      # The isv svn is greater than the enclave's isv svn
    SGX_ERROR_INVALID_KEYNAME    = 0x00003005      # The key name is an unsupported value

    SGX_ERROR_SERVICE_UNAVAILABLE       = 0x00004001   # Indicates aesm didn't respond or the requested service is not supported
    SGX_ERROR_SERVICE_TIMEOUT           = 0x00004002   # The request to aesm timed out
    SGX_ERROR_AE_INVALID_EPIDBLOB       = 0x00004003   # Indicates epid blob verification error
    SGX_ERROR_SERVICE_INVALID_PRIVILEGE = 0x00004004   # Enclave has no privilege to get launch token
    SGX_ERROR_EPID_MEMBER_REVOKED       = 0x00004005   # The EPID group membership is revoked.
    SGX_ERROR_UPDATE_NEEDED             = 0x00004006   # SGX needs to be updated
    SGX_ERROR_NETWORK_FAILURE           = 0x00004007   # Network connecting or proxy setting issue is encountered
    SGX_ERROR_AE_SESSION_INVALID        = 0x00004008   # Session is invalid or ended by server
    SGX_ERROR_BUSY                      = 0x0000400a   # The requested service is temporarily not availabe
    SGX_ERROR_MC_NOT_FOUND              = 0x0000400c   # The Monotonic Counter doesn't exist or has been invalided
    SGX_ERROR_MC_NO_ACCESS_RIGHT        = 0x0000400d   # Caller doesn't have the access right to specified VMC
    SGX_ERROR_MC_USED_UP                = 0x0000400e   # Monotonic counters are used out
    SGX_ERROR_MC_OVER_QUOTA             = 0x0000400f   # Monotonic counters exceeds quota limitation
    SGX_ERROR_KDF_MISMATCH              = 0x00004011   # Key derivation function doesn't match during key exchange
    SGX_ERROR_UNRECOGNIZED_PLATFORM     = 0x00004012   # EPID Provisioning failed due to platform not recognized by backend server

    SGX_ERROR_NO_PRIVILEGE              = 0x00005002   # Not enough privilege to perform the operation

    # SGX Protected Code Loader Error codes
    SGX_ERROR_PCL_ENCRYPTED             = 0x00006001   # trying to encrypt an already encrypted enclave
    SGX_ERROR_PCL_NOT_ENCRYPTED         = 0x00006002   # trying to load a plain enclave using sgx_create_encrypted_enclave
    SGX_ERROR_PCL_MAC_MISMATCH          = 0x00006003   # section mac result does not match build time mac
    SGX_ERROR_PCL_SHA_MISMATCH          = 0x00006004   # Unsealed key MAC does not match MAC of key hardcoded in enclave binary
    SGX_ERROR_PCL_GUID_MISMATCH         = 0x00006005   # GUID in sealed blob does not match GUID hardcoded in enclave binary

    # SGX errors are only used in the file API when there is no appropriate EXXX (EINVAL, EIO etc.) error code
    SGX_ERROR_FILE_BAD_STATUS               = 0x00007001	# The file is in bad status, run sgx_clearerr to try and fix it
    SGX_ERROR_FILE_NO_KEY_ID                = 0x00007002    # The Key ID field is all zeros, can't re-generate the encryption key
    SGX_ERROR_FILE_NAME_MISMATCH            = 0x00007003    # The current file name is different then the original file name (not allowed, substitution attack)
    SGX_ERROR_FILE_NOT_SGX_FILE             = 0x00007004    # The file is not an SGX file
    SGX_ERROR_FILE_CANT_OPEN_RECOVERY_FILE  = 0x00007005    # A recovery file can't be opened, so flush operation can't continue (only used when no EXXX is returned)
    SGX_ERROR_FILE_CANT_WRITE_RECOVERY_FILE = 0x00007006    # A recovery file can't be written, so flush operation can't continue (only used when no EXXX is returned)
    SGX_ERROR_FILE_RECOVERY_NEEDED          = 0x00007007    # When openeing the file, recovery is needed, but the recovery process failed
    SGX_ERROR_FILE_FLUSH_FAILED             = 0x00007008    # fflush operation (to disk) failed (only used when no EXXX is returned)
    SGX_ERROR_FILE_CLOSE_FAILED             = 0x00007009	# fclose operation (to disk) failed (only used when no EXXX is returned)

    SGX_INTERNAL_ERROR_ENCLAVE_CREATE_INTERRUPTED = 0x0000F001 # The ioctl for enclave_create unexpectedly failed with EINTR.

class SGXError(Exception):
    def __init__(self, status):
        self.status

    def __str__(self):
        return "SGX_ERROR #: " + self.status
