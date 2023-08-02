/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:02:23 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/02 20:20:37 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	pthread_mutex_unlock(&(philo->shared->launcher));
	if (philo->id_philo % 2 == 1)
		usleep(20000);
	think(philo);
	while (take_a_fork(philo) == FAILURE)
		;
	eat(philo);
	leave_fork(philo);
	sleeping(philo);
}

void	think(t_philo *philo)
{
	long int	current_time;

	pthread_mutex_lock(&(philo->shared->launcher));
	current_time = get_time() - philo->shared->start_time;
	philo_says(THINK, current_time, philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->launcher));
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	philo->start_to_eat = get_time() - philo->shared->start_time;
	philo_says(EAT, philo->start_to_eat, philo->id_philo);
	philo->end_to_eat = get_time() - philo->start_to_eat;
	pthread_mutex_unlock(&(philo->shared->launcher));
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	philo_says(SLEEP, (get_time() - philo->shared->start_time), philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->launcher));
}
