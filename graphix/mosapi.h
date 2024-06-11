#ifndef MOS_H_
#define MOS_H_

//#include <unistd.h>

#define O_ACCMODE	   0003
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#ifndef O_CREAT
# define O_CREAT	   0100	/* Not fcntl.  */
#endif
#ifndef O_EXCL
# define O_EXCL		   0200	/* Not fcntl.  */
#endif
#ifndef O_NOCTTY
# define O_NOCTTY	   0400	/* Not fcntl.  */
#endif
#ifndef O_TRUNC
# define O_TRUNC	  01000	/* Not fcntl.  */
#endif
#ifndef O_APPEND
# define O_APPEND	  02000
#endif
#ifndef O_NONBLOCK
# define O_NONBLOCK	  04000
#endif
#ifndef O_NDELAY
# define O_NDELAY	O_NONBLOCK
#endif
#ifndef O_SYNC
# define O_SYNC	       04010000
#endif
#define O_FSYNC		O_SYNC
#ifndef O_ASYNC
# define O_ASYNC	 020000
#endif
#ifndef __O_LARGEFILE
# define __O_LARGEFILE	0100000
#endif

#ifndef __O_DIRECTORY
# define __O_DIRECTORY	0200000
#endif
#ifndef __O_NOFOLLOW
# define __O_NOFOLLOW	0400000
#endif
#ifndef __O_CLOEXEC
# define __O_CLOEXEC   02000000
#endif
#ifndef __O_DIRECT
# define __O_DIRECT	 040000
#endif
#ifndef __O_NOATIME
# define __O_NOATIME   01000000
#endif
#ifndef __O_PATH
# define __O_PATH     010000000
#endif
#ifndef __O_DSYNC
# define __O_DSYNC	 010000
#endif
#ifndef __O_TMPFILE
# define __O_TMPFILE   (020000000 | __O_DIRECTORY)
#endif

/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

typedef          int fd_t;
typedef unsigned int pid_t;
typedef unsigned int mode_t;

typedef unsigned int size_t;
typedef unsigned int off_t;

void exit(int code) {
    asm volatile("int $0x80" : : "a"(1), "b"(code));
    for(;;);
}

pid_t fork(void) {
    return 0;
}

size_t read(fd_t __fd, char *__buf, size_t __nbytes) {
    size_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(3), "b"(__fd), "c"(__buf), "d"(__nbytes));
    return ret;
}

size_t write(fd_t __fd, const char *__buf, size_t __n) {
    size_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(4), "b"(__fd), "c"(__buf), "d"(__n));
    return ret;
}

fd_t open(const char* __path, int __flags) {
    fd_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(5), "b"(__path), "c"(__flags));
    return ret;
}

int close(fd_t __fd) {
    fd_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(6), "b"(__fd));
    return ret;
}

off_t lseek(fd_t __fd, off_t __offset, int __whence) {
    fd_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(19), "b"(__fd), "c"(__offset), "d"(__whence));
    return ret;
}

off_t tell(int __fd) {
    return lseek(__fd, 0, SEEK_CUR);
}

int chdir(const char* path) {
    pid_t ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(12), "b"(path));
    return ret;
}

void prntnum(unsigned int n) {
    asm volatile("int $0x80" : : "b"(n), "a"(200));
}

void* malloc(size_t size) {
    void* ret;
    asm volatile("int $0x80" : "=b"(ret) : "a"(500), "b"(size));
    return ret;
}

void free(void* ptr) {
    asm volatile("int $0x80" : :"a"(501), "b"(ptr));
}

void ProcessClearSTDIN() {
    asm volatile("int $0x80" : :"a"(80200));
}

#endif //MOS_H_