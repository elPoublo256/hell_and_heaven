#include "hh_exceptions.h"

using namespace hell_and_haven;

ErrnoException::ErrnoException()
{

}

//TODO check
const char* ErrnoException::what()
{
    switch (_errno) {
          case( E2BIG           ) : return " Argument list too long (POSIX.1-2001).";

          case( EACCES          ) : return " Permission denied (POSIX.1-2001).";

          case( EADDRINUSE      ) : return " Address already in use (POSIX.1-2001).";

          case( EADDRNOTAVAIL   ) : return " Address not available (POSIX.1-2001).";

          case( EAFNOSUPPORT    ) : return " Address family not supported (POSIX.1-2001).";

          case( EAGAIN          ) : return " Resource temporarily unavailable (may be the same value as EWOULDBLOCK) (POSIX.1-2001).";

          case( EALREADY        ) : return " Connection already in progress (POSIX.1-2001).";

          case( EBADE           ) : return " Invalid exchange.";

          case( EBADF           ) : return " Bad file descriptor (POSIX.1-2001).";

          case( EBADFD          ) : return " File descriptor in bad state.";

          case( EBADR           ) : return " Invalid request descriptor.";

          case( EBADRQC         ) : return " Invalid request code.";

           case( EBADSLT        ) : return " Invalid slot.";

           case( EBUSY          ) : return " Device or resource busy (POSIX.1-2001).";

           case( ECANCELED      ) : return " Operation canceled (POSIX.1-2001).";

           case( ECHILD         ) : return " No child processes (POSIX.1-2001).";

           case( ECHRNG         ) : return " Channel number out of range.";

           case( ECOMM          ) : return " Communication error on send.";

           case( ECONNABORTED   ) : return " Connection aborted (POSIX.1-2001).";

           case( ECONNREFUSED   ) : return " Connection refused (POSIX.1-2001).";

           case( ECONNRESET     ) : return " Connection reset (POSIX.1-2001).";

           case( EDEADLK        ) : return " Resource deadlock avoided (POSIX.1-2001).";

           //case( EDEADLOCK      ) : return " Synonym for EDEADLK.";

           case( EDESTADDRREQ   ) : return " Destination address required (POSIX.1-2001).";

           case( EDOM           ) : return " Mathematics argument out of domain of function (POSIX.1, C99).";

          case( EDQUOT          ) : return " Disk quota exceeded (POSIX.1-2001).";

           case( EEXIST         ) : return " File exists (POSIX.1-2001).";

           case( EFAULT         ) : return " Bad address (POSIX.1-2001).";

           case( EFBIG          ) : return " File too large (POSIX.1-2001).";

           case( EHOSTDOWN      ) : return " Host is down.";

           case( EHOSTUNREACH   ) : return " Host is unreachable (POSIX.1-2001).";

           case( EHWPOISON      ) : return " Memory page has hardware error.";

           case( EIDRM          ) : return " Identifier removed (POSIX.1-2001).";

           case( EILSEQ         ) : return " Invalid or incomplete multibyte or wide character (POSIX.1, C99). The text shown here is the glibc error description; in POSIX.1, this error is described as)Illegal byte sequence .";

          case( EINPROGRESS     ) : return " Operation in progress (POSIX.1-2001).";

          case( EINTR           )  : return " Interrupted function call (POSIX.1-2001); see signal(7).";

          case(EINVAL           )  : return " Invalid argument (POSIX.1-2001).";

          case( EIO             )  : return " Input/output error (POSIX.1-2001).";

          case( EISCONN         )  : return " Socket is connected (POSIX.1-2001).";

           case( EISDIR         )  : return "  Is a directory (POSIX.1-2001).";

           case( EISNAM         )  : return "  Is a named type file.";

           case( EKEYEXPIRED    )  : return "  Key has expired.";

           case( EKEYREJECTED   )  : return "  Key was rejected by service.";

           case( EKEYREVOKED    )  : return "  Key has been revoked.";

           case( EL2HLT         )  : return "  Level 2 halted.";

           case( EL2NSYNC       )  : return "  Level 2 not synchronized.";

           case( EL3HLT         )  : return "  Level 3 halted.";

           case( EL3RST         )  : return "  Level 3 reset.";

           case( ELIBACC        )  : return "  Cannot access a needed shared library.";

           case( ELIBBAD        )  : return "  Accessing a corrupted shared library.";

           case( ELIBMAX        )  : return "  Attempting to link in too many shared libraries.";

           case( ELIBSCN        )  : return "  .lib section in a.out corrupted";

           case( ELIBEXEC       )  : return "  Cannot exec a shared library directly.";

           //case( ELNRANGE     )  : return "    Link number out of range.";

           case( ELOOP          )  : return "  Too many levels of symbolic links (POSIX.1-2001).";

           case( EMEDIUMTYPE    )  : return "  Wrong medium type.";

           case( EMFILE         )  : return "  Too many open files (POSIX.1-2001).  Commonly caused by exceeding the RLIMIT_NOFILE resource limit described in getrlimit(2).";

           case( EMLINK         )  : return " Too many links (POSIX.1-2001).";

           case( EMSGSIZE       )  : return " Message too long (POSIX.1-2001).";

           case( EMULTIHOP      )  : return " Multihop attempted (POSIX.1-2001).";

           case( ENAMETOOLONG   )  : return " Filename too long (POSIX.1-2001).";

           case( ENETDOWN       )  : return " Network is down (POSIX.1-2001).";

           case( ENETRESET      )  : return " Connection aborted by network (POSIX.1-2001).";

           case( ENETUNREACH    )  : return " Network unreachable (POSIX.1-2001).";

           case( ENFILE         )  : return " Too many open files in system (POSIX.1-2001).  On Linux, this is probably a result of encountering the /proc/sys/fs/file-max limit (see proc(5)).";

           case( ENOANO         )  : return " No anode.";

           case( ENOBUFS        )  : return " No buffer space available (POSIX.1 (XSI STREAMS option)).";

           case( ENODATA        )  : return " No message is available on the STREAM head read queue (POSIX.1-2001).";

           case( ENODEV         )  : return " No such device (POSIX.1-2001).";

           case( ENOENT         )  : return " No such file or directory (POSIX.1-2001). Typically, this error results when a specified pathname does not exist, or one of the components in the directory prefix of a pathname does not exist, or the specified pathname is a dangling symbolic link.";

           case( ENOEXEC        )  : return " Exec format error (POSIX.1-2001).";

           case( ENOKEY         )  : return " Required key not available.";

           case( ENOLCK         )  : return " No locks available (POSIX.1-2001).";

           case( ENOLINK        )  : return " Link has been severed (POSIX.1-2001).";

           case( ENOMEDIUM      )  : return " No medium found.";

           case( ENOMEM         )  : return " Not enough space/cannot allocate memory (POSIX.1-2001).";

           case( ENOMSG         )  : return " No message of the desired type (POSIX.1-2001).";

           case( ENONET         )  : return " Machine is not on the network.";

           case( ENOPKG         )  : return " Package not installed.";

           case( ENOPROTOOPT    )  : return " Protocol not available (POSIX.1-2001).";

           case( ENOSPC         )  : return " No space left on device (POSIX.1-2001).";

           case( ENOSR          )  : return " No STREAM resources (POSIX.1 (XSI STREAMS option)).";

           case( ENOSTR         )  : return " Not a STREAM (POSIX.1 (XSI STREAMS option)).";

           case( ENOSYS         )  : return " Function not implemented (POSIX.1-2001).";

           case( ENOTBLK        )  : return " Block device required.";

           case( ENOTCONN       )  : return " The socket is not connected (POSIX.1-2001).";

           case( ENOTDIR        )  : return " Not a directory (POSIX.1-2001).";

           case( ENOTEMPTY      )  : return " Directory not empty (POSIX.1-2001).";

           case( ENOTRECOVERABLE)  : return " State not recoverable (POSIX.1-2008).";

           case( ENOTSOCK       )  : return " Not a socket (POSIX.1-2001).";

          case( ENOTSUP         )  : return " Operation not supported (POSIX.1-2001).";

           case( ENOTTY         )  : return " Inappropriate I/O control operation (POSIX.1-2001).";

           case( ENOTUNIQ       )  : return " Name not unique on network.";

           case( ENXIO          )  : return " No such device or address (POSIX.1-2001).";

           //case( EOPNOTSUPP     )  : return " Operation not supported on socket (POSIX.1-2001). (ENOTSUP and EOPNOTSUPP have the same value on Linux, but according to POSIX.1 these error values should be distinct.)";

           case( EOVERFLOW      )  : return " Value too large to be stored in data type (POSIX.1-2001).";

           case( EOWNERDEAD     )  : return " Owner died (POSIX.1-2008).";

           case( EPERM          )  : return " Operation not permitted (POSIX.1-2001).";

           case( EPFNOSUPPORT   )  : return " Protocol family not supported.";

           case( EPIPE          )  : return " Broken pipe (POSIX.1-2001).";

           case( EPROTO         )  : return " Protocol error (POSIX.1-2001).";

           case( EPROTONOSUPPORT)  : return " Protocol not supported (POSIX.1-2001).";

           case( EPROTOTYPE     )  : return " Protocol wrong type for socket (POSIX.1-2001).";

           case( ERANGE         )  : return " Result too large (POSIX.1, C99).";

           case( EREMCHG        )  : return " Remote address changed.";

           case( EREMOTE        )  : return " Object is remote.";

           case( EREMOTEIO      )  : return " Remote I/O error.";

           case( ERESTART       )  : return " Interrupted system call should be restarted.";

           case( ERFKILL        )  : return " Operation not possible due to RF-kill.";

           case( EROFS          )  : return " Read-only filesystem (POSIX.1-2001).";

           case( ESHUTDOWN      )  : return " Cannot send after transport endpoint shutdown.";

           case( ESPIPE         )  : return " Invalid seek (POSIX.1-2001).";

           case( ESOCKTNOSUPPORT)  : return " Socket type not supported.";

           case( ESRCH          )  : return " No such process (POSIX.1-2001).";

           case( ESTALE         )  : return " Stale file handle (POSIX.1-2001). This error can occur for NFS and for other filesystems.";

           case( ESTRPIPE       )  : return " Streams pipe error.";

           case( ETIME          )  : return " Timer expired (POSIX.1 (XSI STREAMS option)). (POSIX.1 says STREAM ioctl(2) timeout.)";

           case( ETIMEDOUT      )  : return " Connection timed out (POSIX.1-2001).";

           case( ETOOMANYREFS   )  : return " Too many references: cannot splice.";

           case( ETXTBSY        )  : return " Text file busy (POSIX.1-2001).";

           case( EUCLEAN        )  : return " Structure needs cleaning.";

           case( EUNATCH        )  : return " Protocol driver not attached.";

           case( EUSERS         )  : return " Too many users.";

           //case( EWOULDBLOCK    )  : return " Operation would block (may be same value as EAGAIN) (POSIX.1-2001).";

           case( EXDEV          )  : return " Improper link (POSIX.1-2001).";

           case( EXFULL         ) :  return "Exchange full.";

           default                : return "sory, but i dont know what is this value of errno ";
    }

}
