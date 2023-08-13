/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:05:07 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/07 15:19:49 by cllovio          ###   ########.fr       */
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

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	tab = malloc(count * size);
	if (!(tab))
		return (NULL);
	memset(tab, 0, count * size);
	return (tab);
}

void	init_structure_shared(t_data *shared)
{
	shared->nbr_philo = 0;
	shared->nbr_philo_finished_eating = 0;
	shared->time_to_die = 0;
	shared->time_to_eat = 0;
	shared->nbr_t_must_eat = -1;
	shared->this_is_the_end = false;
}

long int	get_time(struct timeval start_time)
{
	struct timeval	tv;
	int				time;
	
	if (gettimeofday(&tv, NULL) == -1)
		return (print_error(GET_TIME_FAIL), FAILURE);
	time = (tv.tv_sec - start_time.tv_sec) * 1000 + (tv.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

int	kill_the_philosophers(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->nbr_philo - 1)
	{
		if (pthread_mutex_destroy(&(shared->philo[i].left_fork_mutex)) != 0)
			return (print_error(DEST_MUTEX_FAIL), FAILURE);
		i++;
	}
	free(shared->philo);
	return (SUCCESS);
}
