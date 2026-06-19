#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
//样例用了find，所以要处理：按换行符 \n 拆成多行，每一行执行一次命令。
int
main(int argc, char *argv[])
{
    char *newargv[MAXARG];//xv6的用户栈很小，第一次开了512炸了
    char buf[512];
    char *line;
    int n, i;

    if(argc < 2){
        fprintf(2, "usage: xargs command [args...]\n");
        exit(1);
    }

    n = read(0,buf,sizeof(buf)-1);//把数据放到buf里面
    if(n > 0){
        buf[n] = 0;
    }

    //把输入的字符放进去
    for(i = 1; i <argc; i++){
        newargv[i-1] = argv[i];
    }

    line = buf;
    for(i = 0; i < n; i++){
        if(buf[i] == '\n'){
            buf[i] = 0;
            newargv[argc-1] = line; // 把当前这一行作为最后一个参数
            newargv[argc] = 0;     // argv 数组必须以 0 结尾
            //子进程
            int pid = fork();
            if(pid == 0){
                exec(argv[1],newargv);
                fprintf(2, "exec %s failed\n", argv[1]);
                exit(1);
            }
            else{
                wait(0);
            }
            line = &buf[i+1];
        }
    }

    exit(0);
}
