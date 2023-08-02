/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:21:52 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/02 20:22:31 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	shared->start_time = get_time();
	if (shared->start_time == -1)
		return (FAILURE);
	pthread_mutex_unlock(&(shared->launcher));
	if (wait_the_philo(shared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	wait_the_philo(t_data *shared)
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
