#include "control.h"

int create_sem(){
  int fd = open("data.txt",O_CREAT | O_TRUNC);

  int shm = shmget(SHMKEY,4,IPC_CREAT | 0600);
  int *d = shmat(shm,0,0);
  *d = 0;

  int sem = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  union semun us;
  us.val = 1;
  int r = semctl(sem,0,SETVAL,us);

  return 0;
}

int remove_sem(){
  int sem = semget(SEMKEY,1,0);
  int r = semctl(sem,IPC_RMID,0);

  int shm = shmget(SHMKEY,0,0);
  r = shmctl(shm,IPC_RMID,0);

  int fd = open("data.txt",O_RDONLY);
  char s[1024];
  int i = read(fd, s,1024);
  s[i] = '\0';
  remove("data.txt");

  return 0;
}

int main (int argc, char *argv[]){
  if (argc < 2){
    printf("create -c, remove -r");
    return 0;
  }
  if (!strcmp(argv[1],"-c")){
    create_sem();
  }
  else if (!strcmp(argv[1],"-r")){
    remove_sem();
  }
  else{
    printf("create -c, remove -r");
  }
  return 0;
}
