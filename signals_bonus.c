/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:37:39 by labderra          #+#    #+#             */
/*   Updated: 2024/07/18 21:21:48 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	wait_signals(t_proc *pipe_list, int len)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < len)
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			if (waitpid(pipe_list[i].pid, &status, WNOHANG | WUNTRACED) == -1)
			{
				perror("waitpid");
				break ;
			}
		}
		i++;
	}
	close_pipes(pipe_list, len);
	free(pipe_list);
	return (status);
}
