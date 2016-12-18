#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
  // Error checking omitted for expository purposes
  sem_t *sem = sem_open("test_semaphore", O_CREAT|O_EXCL, 0, 1);
  sem_unlink("test_semaphore");
  int child = fork();
  printf("pid %d about to wait\n", getpid());
  sem_wait(sem);
  printf("pid %d done waiting\n", getpid());
  sleep(1);
  printf("pid %d done sleeping\n", getpid());
  sem_post(sem);

  if(child > 0)
  {gii
    int status;
    printf("parent done, waiting for child\n");
    wait(&status);
  }

  printf("pid %d exiting\n", getpid());
  return 0;
}
