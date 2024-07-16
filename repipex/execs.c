/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 00:22:53 by labderra          #+#    #+#             */
/*   Updated: 2024/07/16 00:44:13 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*triple_strjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	while (*s2)
		p[i++] = *s2++;
	while (*s3)
		p[i++] = *s3++;
	p[i] = '\0';
	return (p);
}

static char	**get_full_path(char **envp)
{
	while (envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!envp)
		return (NULL);
	return (ft_split(*envp + 5, ':'));
}

static void	run_cmd(char **envp, char **cmd_args)
{
	char	**full_path;
	char	*full_cmd;

	full_path = get_full_path(envp);
	if (!full_path)
	{
		perror("path");
		return ;
	}
	while (full_path)
	{
		full_cmd = triple_strjoin(*full_path, "/", cmd_args[0]);
		if (full_cmd && access(full_cmd, X_OK) == 0)
		{
			execve(full_cmd, cmd_args, envp);
			perror("execve");
			return ;
		}
		free(full_cmd);
		full_path++;
	}
}

void	exec_cmds(t_proc *pipe_list, int len, char **envp)
{
	int		cpid;
	int		i;

	i = 0;
	while (i < len)
	{
		cpid = fork();
		if (cpid == 0)
		{
			dup2(pipe_list[i].std_in, 0);
			dup2(pipe_list[i].std_out, 1);
			while (len--)
			{
				close(pipe_list[len].std_in);
				close(pipe_list[len].std_out);
			}
			run_cmd(envp, ft_split(pipe_list[i].cmd, ' '));
		}
		else
			pipe_list[i].pid = cpid;
		i++;
	}
}
