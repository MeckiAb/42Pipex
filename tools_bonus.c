/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:29:12 by labderra          #+#    #+#             */
/*   Updated: 2024/07/18 21:21:54 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
}

char	*triple_strjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	while (*s2)
		p[i++] = *s2++;
	while (*s3)
		p[i++] = *s3++;
	p[i] = '\0';
	return (p);
}
