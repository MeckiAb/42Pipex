/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:17:01 by labderra          #+#    #+#             */
/*   Updated: 2024/06/21 11:36:27 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	setup_pipes(t_proc *proc_list, int len, char *infile, char *outfile)
{
	int	pipe_fd[2];
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (pipe(pipe_fd) == -1)
			error("Error");
		proc_list[i].std_out = pipe_fd[1];
		proc_list[i].std_in = pipe_fd[0];
		i++;
	}
	proc_list[i].std_out = open(infile, O_RDONLY);
	proc_list[0].std_in = open(outfile, O_CREAT | O_WRONLY);
	if (proc_list[i].std_out == -1 || proc_list[0].std_in == -1)
		error("Error");
}

int	main(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;

	proc_list = process_init(argc, argv, envp);
	setup_pipes(proc_list, argc - 3, argv[1], argv[argc - 1]);
}
