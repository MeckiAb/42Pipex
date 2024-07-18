/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:19:00 by labderra          #+#    #+#             */
/*   Updated: 2024/07/18 13:38:28 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_proc
{
	char	*cmd;
	int		pid;
	int		std_in;
	int		std_out;
}	t_proc;

void	exec_cmds(t_proc *pipe_list, int len, char **envp);
int		wait_signals(t_proc *pipe_list, int len);
t_proc	*setup_pipes(char **arg, int len);
void	close_pipes(t_proc *pipe_list, int len);
void	free_split(char **str);
char	*triple_strjoin(char const *s1, char const *s2, char const *s3);

#endif