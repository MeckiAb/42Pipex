/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:47:07 by labderra          #+#    #+#             */
/*   Updated: 2024/06/13 20:42:02 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <errno.h>

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*parse_command(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*aux;
	char	*current_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		error("Unable to find PATH variable");
	paths = ft_split(&envp[i][5], ':');
	aux = ft_strjoin("/", cmd);
	if (!paths || !aux)
		error("Error");
	i = -1;
	while (paths[++i])
	{
		current_path = ft_strjoin(paths[i], aux);
		if (!current_path)
			break ;
		if (access(current_path, F_OK | X_OK))
			break ;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	free(aux);
	return (current_path);
}

int	main(int argc, char **argv, char **envp)
{
	/* char	*cmd1;
	char	*cmd2; */
	(void)envp;
	
	if (argc != 5)
		error("Error: Wrong number of arguments");
	if (access(argv[1], F_OK | R_OK) == -1 || access(argv[4], W_OK))
		error("Invalid Argument");
	//cmd1 = parse_command(argv[2], **envp);
	//cmd2 = parse_command(argv[3], **envp);

	
	return (0);
}