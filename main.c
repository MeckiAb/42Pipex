/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:17:01 by labderra          #+#    #+#             */
/*   Updated: 2024/06/25 13:06:59 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	close_pipes(t_proc *proc_list, int len)
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
ft_printf("cpid %i process %i %s\n", cpid, process, proc_list[process].cmd_path);
		if (cpid == 0)
		{
			dup2(proc_list[process].std_in, STDIN_FILENO);
			dup2(proc_list[process].std_out, STDOUT_FILENO);
//			close_pipes(proc_list, process);
//			close_pipes(&proc_list[process + 1], len - process - 1);

			close_pipes(proc_list, len);
ft_printf("cpid %i process %i %s\n", cpid, process, proc_list[process].cmd_path);
			if (execve(proc_list[process].cmd_path, proc_list[process].cmd_args,
				proc_list[process].envp) == -1)
				error ("execve");
		}
		else
		{
			proc_list[process].pid = cpid;
ft_printf("cpid %i process %i %s\n", cpid, process, proc_list[process].cmd_path);

			close_pipes(proc_list, len);
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
	while (i < len)
	{
		w_error = waitpid(proc_list[i].pid, &status, 0);
		if (w_error == -1)
			error("waitpid");
		i++;
	}
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;

	proc_list = process_init(argc - 3, argv, envp);
	setup_pipes(proc_list, argc - 3, argv[1], argv[argc - 1]);
	exec_cmds(proc_list, argc - 3);
	return (wait_signals(proc_list, argc - 3));	
}
