/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:17:22 by labderra          #+#    #+#             */
/*   Updated: 2024/07/13 12:58:43 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_pipes(t_proc *proc_list, int len, char *infile, char *outfile)
{
	int	pipe_fd[2];
	int	i;

	i = 0;
	proc_list[0].std_in = open(infile, O_RDONLY);
	if (proc_list[0].std_in == -1)
		error(infile);
	while (i < len - 1)
	{
		if (pipe(pipe_fd) == -1)
			error("");
		proc_list[i].std_out = pipe_fd[1];
		proc_list[i + 1].std_in = pipe_fd[0];
		i++;
	}
	proc_list[i].std_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (proc_list[i].std_out == -1)
		error(outfile);
}

static char	**get_path_env(char **envp)
{
	int		i;
	char	**full_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	full_path = ft_split(&envp[i][5], ':');
	return (full_path);
}

static char	*get_bar_cmd(char *str)
{
	char	**aux;
	char	*word;
	char	*bar_command;
	int		i;

	aux = ft_split(str, ' ');
	if (!aux)
		return (NULL);
	word = (char *)ft_calloc(ft_strlen(aux[0]) + 1, sizeof(char));
	if (word)
		ft_strlcpy(word, aux[0], ft_strlen(aux[0]) + 1);
	i = 0;
	while (aux[i])
		free(aux[i++]);
	free(aux);
	if (!word)
		return (NULL);
	bar_command = ft_strjoin("/", word);
	return (free(word), bar_command);
}

static char	*get_cmd_path(char *cmd, char **full_path)
{
	char	*bar_cmd;
	char	*full_cmd;
	int		i;

	bar_cmd = get_bar_cmd(cmd);
	i = 0;
	while (full_path[i] && bar_cmd)
	{
		full_cmd = ft_strjoin(full_path[i], bar_cmd);
		if (!full_cmd)
			return (free(bar_cmd), NULL);
		if (access(full_cmd, (F_OK | X_OK)) == 0)
			return (free(bar_cmd), full_cmd);
		free(full_cmd);
		i++;
	}
	free(bar_cmd);
	return (NULL);
}

t_proc	*process_init(int len, char **argv, char **envp)
{
	t_proc	*proc_list;
	int		i;
	char	**full_path;

	proc_list = (t_proc *)ft_calloc(len, sizeof(t_proc));
	full_path = get_path_env(envp);
	i = 0;
	if (!proc_list || !full_path)
	{
		while (full_path[i])
			free(full_path[i++]);
		return (free_proc_lst(proc_list, 2), free(full_path), NULL);
	}
	while (i < len)
	{
		proc_list[i].cmd_path = get_cmd_path(argv[i + 2], full_path);
		proc_list[i].cmd_args = ft_split(argv[i + 2], ' ');
		if (!proc_list[i].cmd_args || !proc_list[i].cmd_path)
			break ;
		i++;
	}
	i = 0;
	while (full_path[i])
		free(full_path[i++]);
	return (free(full_path), proc_list);
}
