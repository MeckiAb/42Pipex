/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:29:06 by labderra          #+#    #+#             */
/*   Updated: 2024/07/01 10:07:53 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_proc *proc_list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close(proc_list[i].std_in);
		close(proc_list[i].std_out);
		i++;
	}
}

void	exec_cmds(t_proc *proc_list, int len)
{
	int	cpid;
	int	process;

	process = 0;
	while (process < len)
	{
		cpid = fork();
		if (cpid == 0)
		{
			dup2(proc_list[process].std_in, 0);
			dup2(proc_list[process].std_out, 1);
			close_pipes(proc_list, len);
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

int	wait_signals(t_proc *proc_list, int len)
{
	int	status;
	int	i;
	int	w_error;

	i = 0;
	status = 0;
	while (i < len)
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			w_error = waitpid(proc_list[i].pid, &status, 0);
			if (w_error == -1)
				error("waitpid");
		}
		i++;
	}
	close_pipes(proc_list, len);
	return (WEXITSTATUS(status));
}
