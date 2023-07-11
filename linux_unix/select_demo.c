#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

// other tips:
// kill -l: list all signals that can be sent

void handler(int sig) {
        //main will exit directly without print select ret if have no signal hangler. why??
        signal(sig, handler);
        printf("Receive signal: %d\n", sig);
}

int main()
{
        char buf[10]="";
        fd_set rdfds;
        //struct timeval tv;
        int ret;
        FD_ZERO(&rdfds);
        FD_SET(0,&rdfds);   //文件描述符0表示stdin键盘输入
        //tv.tv_sec = 3;
        //tv.tv_usec = 500;

        signal(SIGINT, handler);
        signal(SIGALRM, handler);

        printf("pid = %d\n", getpid());
        printf("start select...\n");
        while (1) {
                // if interrupt by signals, it seemed not need set rdfds again.
                ret = select(1, &rdfds, NULL, NULL, NULL);      //第一个参数是监控句柄号+1
                printf("end select...\n");
                if(ret < 0)
                        printf("selcet error, ret =%d, errno = %d \n", ret, errno);
                else if(ret == 0)
                        printf("timeout \n");
                else {
                        printf("ret = %d \n",ret);
                        break;
                }
        }

        if(FD_ISSET(0, &rdfds)){         //监控输入的确是已经发生了改变
                printf(" reading : \n");
                read(0, buf, 9);                 //从键盘读取输入
        }

        write(1,buf,strlen(buf));          //在终端中回显
        printf(" %ld \r\n", strlen(buf));
        return 0;
}

