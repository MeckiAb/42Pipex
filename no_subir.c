/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_subir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:34:24 by labderra          #+#    #+#             */
/*   Updated: 2024/07/11 09:33:17 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_proces_list(t_proc *proc_list, int len)
{
	int	i;

	i = 0;
	ft_printf("----------------------\n");
	while (i < len)
	{
		ft_printf("Command : %s\n", proc_list[i].cmd_path);
		ft_printf("PID     : %i\n", proc_list[i].pid);
		ft_printf("fd-in   : %i\n", proc_list[i].std_in);
		ft_printf("fd-out  : %i\n", proc_list[i].std_out);
		ft_printf("----------------------\n");
		i++;
	}
}
