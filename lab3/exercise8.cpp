#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    int ret = fork();
    int i = 5;
    if (ret < 0)
        printf("error\n");
    else if (ret == 0)
    {
        while (i > 0)
        {
            i--;
            printf("child process with pid num %d\n", getpid());
            sleep(1);
        }
        exit(1);
    }
    else
    {
        while (i > 0)
        {
            i--;
            printf("father process has a child with pid num %d\n", ret);
            sleep(1);
        }
        exit(1);
    }
    return 0;
}