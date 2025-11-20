#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <sys/wait.h>
#include  <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 100 

void  ChildProcess(int iter_count); /* child processor */            
void  ParentProcess(void); /* parent processor */              

int main(void)
{
  int iter_count1, iter_count2;
  pid_t  pid1, pid2;
  srandom(time(NULL) ^ getpid() ^ getppid());
  iter_count1 = random()%30+1;

  pid1 = fork();
  if (pid1 < 0) {
    perror("fork failed");
    exit(1);
  }
  if (pid1 == 0) {
    ChildProcess(iter_count1);
  }

  iter_count2 = random() % 30 + 1;
    
  pid2 = fork();
  if (pid2 < 0) {
    perror("fork failed");
    exit(1);
  }
  if (pid2 == 0) {
    ChildProcess(iter_count2);
  }

  ParentProcess();
  return 0;
}

void  ChildProcess(int iter_count) { 
  char buf[BUF_SIZE];
  int i, pid, ppid;
  int sleep_time;
  
  pid = getpid();
  ppid = getppid();

  srandom(time(NULL) ^ pid);
  
  for (i = 1; i <= iter_count; i++){        
    sprintf(buf, "Child Pid: %d is going to sleep!\n", pid);
    write(1, buf, strlen(buf));
    
    sleep_time = random()%10+1;
    sleep(sleep_time);
  }
  
  sprintf(buf, "Child Pid: %d is awake! Where is my Parent: %d?\n", pid, ppid);
  write(1, buf, strlen(buf));
  exit(0);
}

void  ParentProcess(void)
{
  pid_t  child_pid;
  char   buf[BUF_SIZE];
  int status; 

  child_pid = wait(&status);
  if (child_pid < 0) { 
    perror("wait failed");
    exit(1);
  }
  sprintf(buf, "Child Pid: %d has completed\n", child_pid);
  write(1, buf, strlen(buf));

  child_pid = wait(&status);
  if (child_pid < 0) { 
    perror("wait failed");
    exit(1);
  }
  sprintf(buf, "Child Pid: %d has completed\n", child_pid);
  write(1, buf, strlen(buf));
}
