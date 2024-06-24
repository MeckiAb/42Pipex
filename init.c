/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:17:22 by labderra          #+#    #+#             */
/*   Updated: 2024/06/24 14:15:20 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_pipes(t_proc *proc_list, int len, char *infile, char *outfile)
{
	int	pipe_fd[2];
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (pipe(pipe_fd) == -1)
			error("Error1");
		proc_list[i].std_out = pipe_fd[1];
		proc_list[i + 1].std_in = pipe_fd[0];
		i++;
	}
	proc_list[0].std_in = open(infile, O_RDONLY);
ft_printf("0 in = %i - %s", proc_list[0].std_in, infile);
	if (proc_list[0].std_in == -1)
		error("Error2.1");
	proc_list[i].std_out = open(infile, O_WRONLY);
ft_printf("%i out = %i - %s\n", i, proc_list[0].std_in, outfile);
	if (proc_list[i].std_out == -1)
		error("Error2.2");
}

static char	*get_bar_cmd(char *str, char c)
{
	char	**aux;
	char	*word;
	char	*bar_command;
	int		i;

	aux = ft_split(str, c);
	if (!aux)
		error("Error3");
	word = (char *)ft_calloc(ft_strlen(aux[0]) + 1, sizeof(char));
	if (!word)
		error("Error4");
	ft_strlcpy(word, aux[0], ft_strlen(aux[0]) + 1);
	i = 0;
	while (aux[i])
		free(aux[i++]);
	free(aux);
	bar_command = ft_strjoin("/", word);
	free(word);
	if (!bar_command)
		error("Error5");
	return (bar_command);
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
		error("Error6");
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
			error("Error7");
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

t_proc	*process_init(int len, char **argv, char **envp)
{
	t_proc	*proc_list;
	int		i;
	char	**full_path;

	proc_list = (t_proc *)malloc((len) * sizeof(t_proc));
	if (!proc_list)
		error("Error8");
	i = 0;
	full_path = get_path_env(envp);
	while (i < len)
	{
		proc_list[i].cmd_path = get_cmd_path(argv[i + 2], full_path);
		proc_list[i].cmd_args = ft_split(argv[i + 2], ' ');
		if (!proc_list[i].cmd_args)
		{
			free(proc_list);
			error("Error9");
		}
		proc_list[i].envp = envp;
		i++;
	}
	return (proc_list);
}
