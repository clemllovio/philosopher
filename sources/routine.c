/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:02:23 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/03 16:27:07 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleeping(t_philo *philo);

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	pthread_mutex_unlock(&(philo->shared->launcher));
	if (philo->id_philo % 2 == 1)
		usleep(20000);
	while (philo->am_i_dead == false)
	{
		think(philo);
		while (take_a_fork(philo) == FAILURE)
			;
		eat(philo);
		leave_fork(philo);
		sleeping(philo);
	}
}

static void	think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->talk));
	if (philo->shared->this_is_the_end == true)
		return ;
	philo_says(THINK, get_time(philo->shared->start_time), philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->talk));
}

static void	eat(t_philo *philo)
{
	long int	current_time;
	long int	copy_time_to_eat;
	
	current_time = 0;
	pthread_mutex_lock(&(philo->shared->talk));
	if (philo->shared->this_is_the_end == true)
		return ;
	philo->start_to_eat = get_time(philo->shared->start_time);
	if (philo->start_to_at > philo->lifetime)
	{
		philo->am_i_dead = true
		philo->shared->
	}
	copy_time_to_eat = philo->shared->time_to_eat;
	philo_says(EAT, philo->start_to_eat, philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->talk));
	current_time = (get_time(philo->shared->start_time) - philo->start_to_eat);
	while ( current_time < copy_time_to_eat)
		current_time = (get_time(philo->shared->start_time) - philo->start_to_eat);
	philo->end_to_eat = current_time;
	philo->lifetime += copy_time_to_eat;
	philo->nbr_fork = 0;
	philo->nbr_meal ++;
}

static void	sleeping(t_philo *philo)
{
	long int	copy_time_to_sleep;
	long int	current_time;
	
	copy_time_to_sleep = 0;
	pthread_mutex_lock(&(philo->shared->talk));
	if (philo->shared->this_is_the_end == true)
		return ;
	philo->start_to_sleep = get_time(philo->shared->start_time);
	copy_time_to_sleep = philo->shared->time_to_sleep;
	philo_says(SLEEP, philo->start_to_sleep, philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->talk));
	current_time = (get_time(philo->shared->start_time) - philo->start_to_sleep);
	while (current_time < copy_time_to_sleep)
		current_time = (get_time(philo->shared->start_time) - philo->start_to_sleep);
	philo->lifetime += copy_time_to_sleep;
}