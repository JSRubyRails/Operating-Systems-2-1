#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <sys/wait.h>
#include  <sys/types.h>
#include <time.h>

#define MAX_COUNT 200
#define BUF_SIZE 100 

void  ChildProcess(int iter_count); /* child processor */            
void  ParentProcess(void); /* parent processor */              

void  main(void)
{
  int iter_count, seed;
  pid_t  pid, child_pid;
    
    srandom(time(NULL));
    iter_count =random()%30+1;

     pid = fork();
     if (pid == 0)  {
          ChildProcess(iter_count);
      }
     else if (pid>0) {
        
          pid = fork();
          iter_count =random()%30+1;
          
          if (pid == 0){
            ChildProcess(iter_count);
          }
       }

     ParentProcess();

}

void  ChildProcess(int iter_count)
{ 
    char   buf[BUF_SIZE];
     int   i, pid, ppid;
     int sleep_time;

     pid = getpid();
     ppid = getppid();
     srandom(pid);
     
     for (i = 1; i <= iter_count; i++){        
      sprintf(buf, "Child Pid: %d is going to sleep!\n", pid);
      write(1, buf, strlen(buf));
      sleep_time = random()%10+1;
      // sprintf(buf, "%d\n", sleep_time);
      // write(1, buf, strlen(buf));
      sleep(sleep_time);
     }
     sprintf(buf, "Child Pid: %d is awake! Where is my Parent: %d?\n", pid, ppid);
     write(1, buf, strlen(buf));
     exit(0);
}

void  ParentProcess(void)
{
  // TODO: print out child pid using wait(0)
     pid_t  child_pid;
     
     char   buf[BUF_SIZE];
     child_pid = wait(0);
    sprintf(buf, "Child Pid: %d has completed\n", child_pid);
    write(1, buf, strlen(buf));

     child_pid = wait(0);
    sprintf(buf, "Child Pid: %d has completed\n", child_pid);
    write(1, buf, strlen(buf));
}