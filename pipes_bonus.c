/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:37:04 by labderra          #+#    #+#             */
/*   Updated: 2024/07/18 21:34:49 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

t_proc	*setup_heredoc(char **arg, int len)
{
	(void) arg;
	(void) len;
	
	return (NULL);
}

void	close_pipes(t_proc *pipe_list, int len)
{
	while (len--)
	{
		if (pipe_list[len].std_in != -1)
			close(pipe_list[len].std_in);
		if (pipe_list[len].std_out != -1)
			close(pipe_list[len].std_out);
	}
}
