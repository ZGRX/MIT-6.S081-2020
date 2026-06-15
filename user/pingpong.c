#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc , char*argv[]){
    char buf[1];//用给read的缓冲区buf
    int p1[2];
    int p2[2];
    if(pipe(p1)<0||pipe(p2)<0){
        exit(1);
    }

    int pid = fork();
    //pipe[0]端读 pipe[1]端写
    if(pid > 0){//
        int pid_parent = getpid();
        write(p1[1],"x",1);
        read(p2[0],buf,1);
        printf("%d: received pong\n",pid_parent);
        wait(0);
        exit(0);
    }
    else if(pid ==0){//子进程
        int pid_child = getpid();
        read(p1[0],buf,1);
        printf("%d: received ping\n",pid_child);
        write(p2[1],"x",1);
        exit(0);
    }
    else{
        fprintf(2, "fork error\n");
        exit(1);
    }
}
