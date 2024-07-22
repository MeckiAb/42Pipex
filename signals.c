/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:37:39 by labderra          #+#    #+#             */
/*   Updated: 2024/07/22 18:20:48 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_signals(t_proc *pipe_list, int len)
{
	int	status;
	int	i;

	i = 0;
	while (i < len)
	{
		waitpid(pipe_list[i].pid, &status, WNOHANG | WUNTRACED);
		i++;
	}
	close_pipes(pipe_list, len);
	free(pipe_list);
	return (status);
}
