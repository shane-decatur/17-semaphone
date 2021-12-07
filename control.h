#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SEMKEY 1234
#define SHMKEY 4321

// union semun{
//   int val;
//   struct semid_ds *buf;
//   unsigned short *array;
//   struct seminfo *__buf;
// };
