#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

//参考ls.c的设计
void
find(char *path){
  char buf[512], *p;
  int fd;
  struct dirent de;//包括ushort inum和char name[DIRSIZ]
  struct stat st;    

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);//0：标准输入，1：标准输出，2：标准错误
    return;
  }
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }


  switch(st.type){
    case T_FILE:
        //printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
        break;

    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
        printf("ls: path too long\n");
        break;
        }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while(read(fd,&de,sizeof(de))==sizeof(de)){
      if(de.inum == 0)
      continue;
      memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    }
}
    close(fd);
}
int
main()
{
  find(".");
  exit(0);
}