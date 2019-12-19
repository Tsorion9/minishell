#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void	func(int a)
{
	printf("signal | PID %d\n", getpid());
	printf("signal number %d\n", a);
}

int	main()
{
	signal(SIGINT, func);
	char	buf[100];
	int b;
	int a = 0;
	int status;
	char *av[]= {"/Users/kristinaafonina/Desktop/ft_ls/ft_ls", "-la", 0};
	pid_t p;
	p = fork();
	printf("fork returned %d\n", p);
 	if (p == 0)
	{
		printf("In child process,  pid=%d,  ppid=%d\n", 
                        getpid(),  getppid());
		while (++a < 110)
			printf("%d\n", a);
		//sleep(5);
		//execv(av[0], av);
	}
	else
	{
		kill(0, SIGINT);
                printf("In parent,  pid=%d,  fork returned=%d\n",
                        getpid(),  p);
		while (++a < 100)
		{
			printf("%d\n", a);
			buf[a] = 0;
		}
		//sleep(5);
        }
	printf("status = %d\n", status);
	write (1, "&>", 2);
	b = read(1, buf, 1000);
	buf[b] = 0;
	printf("%s\n", buf);
	//sleep(10);
	return (0);
}
