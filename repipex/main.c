/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:56 by labderra          #+#    #+#             */
/*   Updated: 2024/07/16 11:58:34 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_proc	*setup_pipes(char **arg, int len)
{
	t_proc	*pipe_list;
	int		pipe_fd[2];
	int		i;

	pipe_list = (t_proc *)malloc(sizeof(t_proc) * len);
	if (!pipe_list)
		return (perror("malloc"), NULL);
	i = 0;
	pipe_list[i].std_in = open(arg[1], O_RDONLY);
	if (pipe_list[i].std_in == -1)
		perror(arg[1]);
	while (i < len - 1)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), NULL);
		pipe_list[i].std_out = pipe_fd[1];
		pipe_list[i].cmd = arg[i + 2];
		pipe_list[++i].std_in = pipe_fd[0];
	}
	pipe_list[i].cmd = arg[i + 2];
	pipe_list[i].std_out = open(arg[i + 3], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pipe_list[i].std_out == -1)
		perror(arg[i + 3]);
	return (pipe_list);
}

int	wait_signals(t_proc *pipe_list, int len)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < len)
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			if (waitpid(pipe_list[i].pid, &status, WNOHANG | WUNTRACED) == -1)
			{
				perror("waitpid");
				break ;
			}
		}
		i++;
	}
	while (len--)
	{
		close(pipe_list[len].std_in);
		close(pipe_list[len].std_out);
	}
	free(pipe_list);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_proc	*pipe_list;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	pipe_list = setup_pipes(argv, argc - 3);
	if (!pipe_list)
		return (-1);
	exec_cmds(pipe_list, argc - 3, envp);
	return (WEXITSTATUS(wait_signals(pipe_list, argc - 3)));
}
