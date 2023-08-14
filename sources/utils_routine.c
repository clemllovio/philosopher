/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:26:26 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/14 09:49:23 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_the_action(t_philo *philo, long int action_start_time, \
	long int action_duration)
{
	long int	current_time;

	current_time = (get_time(philo->shared->start_time) - action_start_time);
	while (current_time < action_duration)
	{
		current_time = (get_time(philo->shared->start_time) - \
		action_start_time);
		usleep(philo->shared->nbr_philo * 10);
		if (still_alive_or_not(action_start_time, philo) == DEAD)
			return (DEAD);
	}
	return (ALIVE);
}

void	did_i_eat_enough(t_philo *philo)
{
	if (philo->shared->nbr_t_must_eat > 0 && \
	philo->nbr_meal == philo->shared->nbr_t_must_eat)
		philo->shared->nbr_philo_finished_eating++;
	if (philo->shared->nbr_t_must_eat > 0 && \
	philo->shared->nbr_philo_finished_eating == philo->shared->nbr_philo)
		philo->shared->this_is_the_end = true;
}
