/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:44:15 by labderra          #+#    #+#             */
/*   Updated: 2024/06/21 11:28:43 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_proc
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

#endif
