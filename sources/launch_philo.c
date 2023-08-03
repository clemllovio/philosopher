/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:21:52 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/03 15:47:03 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_the_philo(t_data *shared);

int	launch_philo(t_data *shared)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&(shared->launcher));
	while (i < shared->nbr_philo)
	{
		if (pthread_create(&(shared->philo[i].id_thread), NULL, (void *)routine, &(shared->philo[i])) \
		!= 0)
			return (print_error(THREAD_CREATION_FAIL), FAILURE);//destroy les mutex
		i++;
	}
	if (gettimeofday(&(shared->start_time), NULL) == -1)
		return (print_error(GET_TIME_FAIL), FAILURE);
	
	pthread_mutex_unlock(&(shared->launcher));
	if (wait_the_philo(shared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	wait_the_philo(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->nbr_philo)
	{
		if (pthread_join(shared->philo[i].id_thread, NULL) != 0)
			return (FAILURE); // destroy les mutex
		i++;
	}
	return (SUCCESS);
}
