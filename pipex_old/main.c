/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:17:01 by labderra          #+#    #+#             */
/*   Updated: 2024/07/13 11:53:33 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_proc_lst(t_proc *proc_list, int len)
{
	while (len--)
	{
		free(proc_list[len].cmd_path);
		free(proc_list[len].cmd_args);		
	}
	free(proc_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;

	if (argc != 5)
		error("Incorrect number of arguments");
	proc_list = process_init(2, argv, envp);
	setup_pipes(proc_list, 2, argv[1], argv[4]);
	exec_cmds(proc_list, 2, envp);
	return (wait_signals(proc_list, 2));
}
