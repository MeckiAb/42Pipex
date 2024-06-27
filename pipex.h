/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:44:15 by labderra          #+#    #+#             */
/*   Updated: 2024/06/27 19:33:13 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct s_proc
{
	char	*cmd_path;
	char	**cmd_args;
	int		pid;
	char	**envp;
	int		std_in;
	int		std_out;
}	t_proc;

void	error(char *str);
t_proc	*process_init(int argc, char **argv, char **envp);
void	setup_pipes(t_proc *proc_list, int len, char *infile, char *outfile);
void	exec_cmds(t_proc *proc_list, int len);
int		wait_signals(t_proc *proc_list, int len);

#endif
