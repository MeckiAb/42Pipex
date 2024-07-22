/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:37:04 by labderra          #+#    #+#             */
/*   Updated: 2024/07/22 13:10:04 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_input(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(infile);
		fd = open("/dev/null", O_RDONLY);
	}
	return (fd);
}

static int	open_output(char *outfile, int mode)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | mode, 0666);
	if (fd == -1)
	{
		perror(outfile);
		fd = open("/dev/null", O_WRONLY);
	}
	return (fd);
}

t_proc	*setup_pipes(char **arg, int len)
{
	t_proc	*pipe_list;
	int		pipe_fd[2];
	int		i;

	pipe_list = (t_proc *)malloc(sizeof(t_proc) * len);
	if (!pipe_list)
		return (perror("malloc"), NULL);
	i = 0;
	pipe_list[i].std_in = open_input(arg[1]);
	while (i < len - 1)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), NULL);
		pipe_list[i].std_out = pipe_fd[1];
		pipe_list[i].cmd = arg[i + 2];
		pipe_list[++i].std_in = pipe_fd[0];
	}
	pipe_list[i].cmd = arg[i + 2];
	pipe_list[i].std_out = open_output(arg[i + 3], O_TRUNC);
	return (pipe_list);
}

void	close_pipes(t_proc *pipe_list, int len)
{
	while (len--)
	{
			close(pipe_list[len].std_in);
			close(pipe_list[len].std_out);
	}
}
