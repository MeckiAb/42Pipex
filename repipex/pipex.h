/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:19:00 by labderra          #+#    #+#             */
/*   Updated: 2024/07/13 18:18:02 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_proc 
{
	char	*cmd;
	int		pid;
	int		std_in;
	int		std_out;
}	t_proc;

int		error(char *str);


#endif