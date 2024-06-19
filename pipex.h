/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:44:15 by labderra          #+#    #+#             */
/*   Updated: 2024/06/19 16:49:58 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef struct	s_proc
{
	char	**args;
	int		pid;
	char	**env;
	int		std_in;
	int		std_out;
}	t_proc;

#endif
