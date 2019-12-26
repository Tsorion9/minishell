#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int     main()
{
    printf("hello\n");
    sleep(2);
    return (0);
}