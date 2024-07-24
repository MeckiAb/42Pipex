/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:56 by labderra          #+#    #+#             */
/*   Updated: 2024/07/22 18:41:13 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	return (wait_signals(pipe_list, argc - 3));
}
