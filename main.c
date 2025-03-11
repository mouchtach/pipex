
#include <stdio.h>
#include <unistd.h>

int main()
{
    // char *test;
    // int fd[2];
    int i = 0;
    int f;
    int ac = 3;

    while (i < ac)
    {
        f = fork();
        if (f == 0)
            printf("hello\n");
        if (f > 0)
            i++;
    }
    // pipe(fd);
    // while (i < 2)
    // {
    //     f = fork();
    //     if (f == 0)
    //     {
    //         if (i == 0)
    //         {
    //             dup2(fd[1], 1);
    //             printf("1\n");
    //         }
    //         else
    //         {
    //             dup2(fd[0], 0);
    //             test = malloc(3);
    //             read(0, test, 2);
    //             test[2] = '\0';
    //             printf("%s", test);
    //         }
    //         close(fd[0]);
    //         close(fd[1]);
    //     }
    //     else 
    //     {
    //         while(wait(NULL) > 0);
    //         // close(fd[0]);
    //         // close(fd[1]);

    //     }
    //     i++;

    




    // while(i <= ac)
    // {
    //     pipe(fd);
    //     f = fork();
    //     if(f == 0)
    //     {
    //         if (i == 0)
    //             dup2(fd[1], 1);
    //         else if (i < ac)
    //         {
    //             dup2(fd[0], 0);
    //             dup2(fd[1], 1);
    //         }
    //         else
    //             dup2(fd[0], 0);
    //         test = malloc(5);
    //         read(0, test, 4);
    //         test[5] = '\0';
    //         printf("test\n");
    //         close(fd[1]);
    //         close(fd[0]);
    //         exit(0);
            
    //     }
    //     if (f > 0)
    //     {
    //         while (wait(NULL) > 0);
    //         close(fd[1]);
    //         close(fd[0]);
    //     }
    //     i++;


    // }
}