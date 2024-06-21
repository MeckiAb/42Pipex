/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:17:22 by labderra          #+#    #+#             */
/*   Updated: 2024/06/21 11:00:22 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_bar_cmd(char *str, char c)
{
	char	**aux;
	char	*word;
	int		i;

	aux = ft_split(str, c);
	if (!aux)
		error("Error");
	word = (char *)ft_calloc(ft_strlen(aux[0]) + 1, sizeof(char));
	if (!word)
		error("Error");
	ft_strlcpy(word, aux[0], ft_strlen(aux[0]) + 1);
	i = 0;
	while (aux[i])
		free(aux[i++]);
	free(aux);
	*aux = word;
	word = ft_strjoin("/", *aux);
	free(*aux);
	if (!word)
		error("Error");
	return (word);
}

static char	**get_path_env(char **envp)
{
	int		i;
	char	**full_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		error("Unable to find PATH variable");
	full_path = ft_split(&envp[i][5], ':');
	if (!full_path)
		error("Error");
	return (full_path);
}

static char	*get_cmd_path(char *cmd, char **full_path)
{
	char	*bar_cmd;
	char	*full_cmd;
	int		i;

	bar_cmd = get_bar_cmd(cmd, ' ');
	i = 0;
	while (full_path[i])
	{
		full_cmd = ft_strjoin(full_path[i], bar_cmd);
		if (!full_cmd)
		{
			free(bar_cmd);
			error("Error");
		}
		if (access(full_cmd, (F_OK | X_OK)) == 0)
			return (free(bar_cmd), full_cmd);
		free(full_cmd);
		i++;
	}
	free(bar_cmd);
	error("Command not found");
	return (NULL);
}

t_proc	*process_init(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;
	int		i;
	char	**full_path;

	proc_list = (t_proc *)malloc((argc - 3) * sizeof(t_proc));
	if (!proc_list)
		error("Error");
	i = 0;
	full_path = get_path_env(envp);
	while (i < argc - 3)
	{
		proc_list[i].cmd_path = get_cmd_path(argv[i + 2], full_path);
		proc_list[i].cmd_args = ft_split(argv[i + 2], ' ');
		if (!proc_list[i].cmd_args)
		{
			free(proc_list);
			error("Error");
		}
		proc_list[i++].envp = envp;
	}
	return (proc_list);
}
