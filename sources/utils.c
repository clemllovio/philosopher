/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:05:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/24 12:54:12 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (result != (result * 10 + (str[i] - 48)) / 10)
			return (FAILURE);
		i++;
	}
	return ((int)(result));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	// if (size != 0 && count > SIZE_MAX / size)
	// 	return (NULL);
	tab = malloc(count * size);
	if (!(tab))
		return (NULL);
	memset(tab, 0, count * size);
	return (tab);
}
