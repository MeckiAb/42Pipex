/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:56 by labderra          #+#    #+#             */
/*   Updated: 2024/07/13 19:09:03 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*triple_strjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) 
		+ ft_strlen(s3) + 1));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	while (*s2)
		p[i++] = *s2++;
	while (*s3)
		p[i++] = *s3++;
	p[i] = '\0';
	return (p);
}

t_proc	*setup_pipes(char **argv, int len)
{
	t_proc	*pipe_list;
	int		pipe_fd[2];
	int		i;
	
	pipe_list = (t_proc *)malloc(sizeof(t_proc) * len);
	if (!pipe_list)
		return (perror("malloc"), NULL);
	i = 0;
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	pipe_list[i].std_in = open(argv[1], O_RDONLY);
	if (pipe_list[i] == -1)
		perror(argv[1]);
	while (i < len - 1)
	{
		pipe_list[i].cmd = argv[i + 2];
		pipe_list[i].pid = 0;
		pipe_list[i].std_out = pipe_fd[1];
		if (pipe(pipe_fd) == -1)
			perror("pipe");
		pipe_list[i + 1].std_in = pipe_fd[0];
		i++;		
	}
	
}

void	exec_cmds(t_proc *pipe_list, int len, char **envp);

int	wait_signals(t_proc *pipe_list, int len)
{
	int	status;
	int	i;
	int	w_error;

	i = 0;
	status = 0;
	while (i < len)
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			w_error = waitpid(pipe_list[i].pid, &status, 0);
			if (w_error == -1)
				error("waitpid");
		}
		i++;
	}
	// close_pipes(proc_list, len);
	// free_proc_lst(proc_list, 2);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_proc	*pipe_list;
	
	if (argc != 5)
		error("Usage: ./pipex file1 cmd1 cmd2 file2");
	pipe_list = setup_pipes(argv, argc - 3);
	exec_cmds(pipe_list, argc - 3, envp);
	return(WEXITSTATUS(wait_signals(pipe_list, argc - 3)));
}