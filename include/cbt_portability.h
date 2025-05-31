#ifndef CBT_PORTABILITY_H
#define CBT_PORTABILITY_H

#ifdef _WIN32
    #include <direct.h>   // For _mkdir
    #include <io.h>       // For _open, _read, _write, _close
    #include <fcntl.h>
    #include <errno.h>

    #define mkdir(path, mode) _mkdir(path)  // Ignore 'mode' on Windows
    #define open  _open
    #define read  _read
    #define write _write
    #define close _close
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
#endif

#endif // CBT_PORTABILITY_H