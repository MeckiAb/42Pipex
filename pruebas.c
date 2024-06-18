#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
/* 
int main (int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		wstatus;
	char	*str;
	(void) argv;
	(void) envp;
	(void) argc;

	if (pipe(pipefd) != 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		//dup2(pipefd[0], STDIN_FILENO);
		ft_printf("Child\n");
		str = get_next_line(pipefd[0]);
		ft_printf("%s\n", str);
		free(str);
		str = get_next_line(pipefd[0]);
		ft_printf("%s\n", str);
		free(str);
	}
	else 
	{
 		dup2(STDIN_FILENO, pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
		ft_printf("%s from parent\n", str);
		free (str);
		ft_printf("Parent\n");
		wait(&wstatus);
	}
	return (0);
}
 */

void	execute(void)
{
	char	*str; 

	str = get_next_line(0);
	while (str)
	{
		printf("%s", str);
		get_next_line(0);
		free(str);
	}
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	int		i = 0;
	int		n = 5;
	pid_t	cpid;
	int		fd[2];
	int		wstatus;
	(void) argv;
	(void) argc;
	(void) envp;

	if (pipe(fd) != 0)
		exit(EXIT_FAILURE);
	if ((cpid = fork()) == -1)
		exit(EXIT_FAILURE);
	if (cpid != 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execute();
		waitpid(cpid, &wstatus, 0);
	}
	else
	{
		while(i < n)
		{
			if (cpid != 0)
			{
				dup2(fd[1], 1);
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
				execute();
				waitpid(cpid, &wstatus, 0);
			}
			else
			{			
				if (pipe(fd) != 0)
					exit(EXIT_FAILURE);
				if ((cpid = fork()) == -1)
					exit(EXIT_FAILURE);
			}
			i++;
		}
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execute();
	}

}