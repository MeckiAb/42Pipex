/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 00:22:53 by labderra          #+#    #+#             */
/*   Updated: 2024/07/18 21:21:21 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**get_full_path(char **envp)
{
	while (envp && *envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!envp || !*envp)
		return (NULL);
	return (ft_split(*envp + 5, ':'));
}

static void	run_cmd(char **envp, char **cmd_args, char **full_path)
{
	char	*full_cmd;
	int		i;

	i = 0;
	if (access(cmd_args[0], F_OK) == 0)
		execve(cmd_args[0], cmd_args, envp);
	else if (full_path != NULL)
	{
		while (full_path[i])
		{
			full_cmd = triple_strjoin(full_path[i], "/", cmd_args[0]);
			if (full_cmd && access(full_cmd, F_OK) == 0)
				execve(full_cmd, cmd_args, envp);
			free(full_cmd);
			i++;
		}
	}
	perror("command not found");
}

void	exec_cmds(t_proc *pipe_list, int len, char **envp)
{
	int		cpid;
	int		i;
	char	**full_path;
	char	**cmd_args;

	full_path = get_full_path(envp);
	i = 0;
	while (i < len)
	{
		cpid = fork();
		if (cpid == 0)
		{
			dup2(pipe_list[i].std_in, 0);
			dup2(pipe_list[i].std_out, 1);
			close_pipes(pipe_list, len);
			cmd_args = ft_split(pipe_list[i].cmd, ' ');
			run_cmd(envp, cmd_args, full_path);
			free_split(cmd_args);
			return ;
		}
		else
			pipe_list[i++].pid = cpid;
	}
	free_split(full_path);
}
