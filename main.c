/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:17:01 by labderra          #+#    #+#             */
/*   Updated: 2024/06/27 19:36:19 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}



int	main(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;

	proc_list = process_init(argc - 3, argv, envp);
	setup_pipes(proc_list, argc - 3, argv[1], argv[argc - 1]);
	exec_cmds(proc_list, argc - 3);
	return (wait_signals(proc_list, argc - 3));
}
