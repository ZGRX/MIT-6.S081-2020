#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
// void
// xargs(char *path){
//     char buf[512];
//     int n;
//     n = read(0,buf,sizeof(buf));

//     if(n > 0){
//         write(1,buf,n);
//     }
// }
int
main(int argc, char *argv[])
{
    char buf[512];
    int n;
    n = read(0,buf,sizeof(buf));//把数据放到buf里面

    if(n > 0){
        write(1,buf,n);
    }
    
    exit(0);
}
