#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    int data = 0;

    int ret = fork();
    int i = 8;
    if (ret == 0)
    {
        data = 2;
        while (i != 0)
        {
            i--;
            printf("Child Process: Pong %d, %d;\n", data, i);
            sleep(1);
           // sleep(128);
        }
        exit(1);
    }
    else if (ret != -1)
    {
        data = 1;
        while (i != 0)
        {
            i--;
            printf("Father Process: Ping %d, %d;\n", data, i);
             sleep(1);
            //sleep(128);
        }
        exit(1);
    }

    return 0;
}
