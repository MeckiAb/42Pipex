/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:56 by labderra          #+#    #+#             */
/*   Updated: 2024/07/22 17:30:36 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_proc	*pipe_list;
	int		exit_code;

	if (argc < 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	else if (argc == 6 && !ft_strncmp(argv[1], "here_doc", 8))
	{
		argc = 5;
		run_heredoc(argv[2]);
		pipe_list = setup_heredoc(&argv[1], argc - 3);
	}
	else
		pipe_list = setup_pipes(argv, argc - 3);
	if (!pipe_list)
		return (-1);
	exec_cmds(pipe_list, argc - 3, envp);
	exit_code = WEXITSTATUS(wait_signals(pipe_list, argc - 3));
	if (argc == 5 && !ft_strncmp(argv[1], "here_doc", 8))
		unlink(".heredoctmp");
	return (exit_code);
}
