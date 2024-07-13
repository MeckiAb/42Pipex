/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:17:01 by labderra          #+#    #+#             */
/*   Updated: 2024/07/01 10:38:30 by labderra         ###   ########.fr       */
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

	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc != 6)
			error("Incorrect usage with heredoc");
		proc_list = process_init(2, argv + 1, envp);
		setup_heredoc(proc_list, argv[5]);
		exec_heredoc_cmds(proc_list, *argv[2]);
	}
	else
	{
		proc_list = process_init(argc - 3, argv, envp);
		setup_pipes(proc_list, argc - 3, argv[1], argv[argc - 1]);
		exec_cmds(proc_list, argc - 3);
	}
	return (wait_signals(proc_list, argc - 3));
}
