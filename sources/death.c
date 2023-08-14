/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:04:25 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/14 11:13:52 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_it_over(t_philo	*philo)
{
	pthread_mutex_lock(&(philo->shared->talk));
	if (philo->shared->this_is_the_end == true)
		return (pthread_mutex_unlock(&(philo->shared->talk)), true);
	pthread_mutex_unlock(&(philo->shared->talk));
	return (false);
}

int	still_alive_or_not(int current_time, t_philo *philo)
{
	if (current_time > philo->lifetime)
	{
		pthread_mutex_lock(&(philo->shared->talk));
		if (philo->shared->this_is_the_end != true)
			philo->shared->this_is_the_end = true;
		else
			return (pthread_mutex_unlock(&(philo->shared->talk)), DEAD);
		pthread_mutex_unlock(&(philo->shared->talk));
		philo->am_i_dead = true;
		print_routine(philo, DEAD);
		return (DEAD);
	}
	return (ALIVE);
}
