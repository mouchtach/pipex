#include <stdio.h>
#include <unistd.h>

int main()
{
    // char *test;
    // int fd[2];
    int i = 3;
    int f;
    int ac = 3;

    while (i--)
    {
        f = fork();
        if (f == 0)
            printf("hello\n");
    }
    // f = fork();
    // if (f == 0)
    //     printf("hello\n");
    // f = fork();
    // if (f == 0)
    //     printf("hello\n");
    // f = fork();
    // if (f == 0)
    //     printf("hello\n");
        // if (f > 0)
            
}