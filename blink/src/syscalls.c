#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

int _write(int file, char *ptr, int len) { return len; }
int _read(int file, char *ptr, int len) { return 0; }
int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
void _exit(int status) { while(1); }
void _kill(int pid, int sig) { }
int _getpid() { return 1; }
caddr_t _sbrk(int incr) { extern char end; static char *heap = &end; char *prev = heap; heap += incr; return (caddr_t) prev; }
