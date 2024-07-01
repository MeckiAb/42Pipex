/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:30:22 by labderra          #+#    #+#             */
/*   Updated: 2024/07/01 10:37:58 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_heredoc(t_proc *proc_list, char *outfile)
{
	int		pipe_fd[2];

	proc_list[0].std_in = -1;
	if (pipe(pipe_fd) == -1)
		error("Error1");
	proc_list[0].std_out = pipe_fd[1];
	proc_list[1].std_in = pipe_fd[0];
	proc_list[1].std_out = open(outfile, O_APPEND | O_CREAT , 0666);
	if (proc_list[1].std_out == -1)
		error("Error2.2");
}

static void	run_heredoc(char lmt)
{
	char	*aux_str;

	aux_str = get_next_line(0);
	while (aux_str)
	{
		if (ft_strchr(aux_str, lmt))
		{
			*ft_strchr(aux_str, lmt) = '\0';
			ft_printf("%s", aux_str);
			free(aux_str);
			break ;
		}
		ft_printf("%s", aux_str);
		free(aux_str);
		aux_str = get_next_line(0);
	}
}

void	exec_heredoc_cmds(t_proc *proc_list, char lmt)
{
	int	cpid;
	int	process;

	process = 0;
	while (process < 2)
	{
		cpid = fork();
		if (cpid == 0 && process == 0)
		{
			dup2(proc_list[process].std_in, 0);
			dup2(proc_list[process].std_out, 1);
			close_pipes(proc_list, 2);
			run_heredoc(lmt);
			if (execve(proc_list[process].cmd_path, proc_list[process].cmd_args,
					proc_list[process].envp) == -1)
				error ("execve");
		}
		else if (cpid == 0 && process == 1)
		{
			dup2(proc_list[process].std_in, 0);
			dup2(proc_list[process].std_out, 1);
			close_pipes(proc_list, 2);
			if (execve(proc_list[process].cmd_path, proc_list[process].cmd_args,
					proc_list[process].envp) == -1)
				error ("execve");
		}
		else
		{
			proc_list[process].pid = cpid;
		}
		process++;
	}
}