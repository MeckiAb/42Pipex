/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:47:07 by labderra          #+#    #+#             */
/*   Updated: 2024/06/16 22:03:39 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/* 
Pipex con bonus: 
- llamo al proceso 
- proceso hace pipe y fork
- si es hijo 
 */
execve();

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		error("Unable to find PATH variable");
	paths = ft_split(&envp[i][5], ':');
	if (!paths)
		error("Error");
	return (paths);
}

char	*get_command(char *cmd, char **paths)
{
	int		i;
	char	*aux;
	char	*check_path;

	aux = ft_strjoin("/", cmd);
	if (!aux)
		error("Error");
	i = 0;
	while (paths[i])
	{
		check_path = ft_strjoin(paths[i], aux);
		if (!check_path)
			error("Error");
		if (!access(check_path, F_OK))
			return (check_path);
		free(check_path);
		i++;
	}
	error("Command error");
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	
	if (argc != 5)
		error("Error: Wrong number of arguments");
	if (access(argv[1], F_OK | R_OK) == -1 || access(argv[4], W_OK))
		error("Invalid Argument");
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	paths = get_paths(envp);
	
	cmd1 = get_command(argv[2], paths);
	cmd2 = get_command(argv[3], paths);
	execve(cmd1, ft_split(argv[2], ' '), envp);
	execve(cmd2, ft_split(argv[3], ' '), envp);
	
	return (0);
}
