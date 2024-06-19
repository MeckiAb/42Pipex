/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:17:01 by labderra          #+#    #+#             */
/*   Updated: 2024/06/19 20:01:45 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_proc	*process_init(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;
	int		i;
	
	proc_list = (t_proc *)malloc((argc - 1) * sizeof(t_proc));
	if (!proc_list)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < argc - 1)
	{
		proc_list[i].args = argv;
		proc_list[i++].env = envp;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_proc	*proc_list;

	proc_list = process_init(argc, argv, envp);
	
}