/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:47:07 by labderra          #+#    #+#             */
/*   Updated: 2024/06/14 13:29:16 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <errno.h>

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		error("Unable to find PATH variable");
	paths = ft_split(&envp[i][5], ':');
	if (!paths)
		error("Error");
	return (paths);
}

char	*get_command(char *cmd, char **paths)
{
	int		i;
	char	*aux;
	char	*check_path;

	aux = ft_strjoin("/", cmd);
	if (!aux)
		error("Error");
	i = 0;
	while (paths[i])
	{
		check_path = ft_strjoin(paths[i], aux);
		if (!check_path)
			error("Error");
		if (!access(check_path, F_OK))
			return (check_path);
		free(check_path);
		i++;
	}
	error("Command error");
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	
	if (argc != 5)
		error("Error: Wrong number of arguments");
	if (access(argv[1], F_OK | R_OK) == -1 || access(argv[4], W_OK))
		error("Invalid Argument");
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	paths = get_paths(envp);
	
	cmd1 = get_command(argv[2], paths);
	cmd2 = get_command(argv[3], paths);
	execve(cmd1, ft_split(argv[2], ' '), envp);
	execve(cmd2, ft_split(argv[3], ' '), envp);
	
	return (0);
}

       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

int	main(int argc, char *argv[])
       {
           int pipefd[2];
           pid_t cpid;
           char buf;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <string>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
               close(pipefd[1]);          /* Close unused write end */

               while (read(pipefd[0], &buf, 1) > 0)
                   write(STDOUT_FILENO, &buf, 1);

               write(STDOUT_FILENO, "\n", 1);
               close(pipefd[0]);
               _exit(EXIT_SUCCESS);

           } else {            /* Parent writes argv[1] to pipe */
               close(pipefd[0]);          /* Close unused read end */
               write(pipefd[1], argv[1], strlen(argv[1]));
               close(pipefd[1]);          /* Reader will see EOF */
               wait(NULL);                /* Wait for child */
               exit(EXIT_SUCCESS);
           }
       }
