#include "control.h"

int main(){
  int sem = semget(SEMKEY,1,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(sem,&sb,1);

  int shm = shmget(SHMKEY, 4, 0);
  int *len = shmat(shm,0,0);

  int fd = open("data.txt", O_RDWR | O_APPEND);
  char *s = malloc(1024);
  lseek(fd,-(*len),SEEK_END);
  read(fd,s,1024);
  printf("current line: %s\n", s);
  printf("input new line with max %d characters: \n", 1024);
  fgets(s,1024,stdin);
  lseek(fd,0,SEEK_END);
  write(fd,s,strlen(s));
  *len = strlen(s);
  printf("wrote to file\n");

  shmdt(len);
  sb.sem_op = 1;
  semop(sem, &sb,1);

  return 0;
}
