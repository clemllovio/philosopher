/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:02:23 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/11 12:37:26 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo);
static int	eat(t_philo *philo);
static int	sleeping(t_philo *philo);
void	did_i_eat_enough(t_philo *philo);

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	pthread_mutex_unlock(&(philo->shared->launcher));
	if (philo->id_philo % 2 == 1)
		usleep(40000);
	while (philo->am_i_dead == false)
	{
		pthread_mutex_lock(&(philo->shared->talk));
		if (philo->shared->this_is_the_end == true)
		{
			pthread_mutex_unlock(&(philo->shared->talk));
			return ;
		}
		pthread_mutex_unlock(&(philo->shared->talk));
		think(philo);
		while (take_forks(philo) == FAILURE)
			;
		eat(philo);
		leave_forks(philo);
		sleeping(philo);
	}
}

static void	think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->talk));
	if (philo->shared->this_is_the_end == true)
	{
		pthread_mutex_unlock(&(philo->shared->talk));
		return ;
	}
	print_routine(THINK, get_time(philo->shared->start_time), philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->talk));
}

static int	eat(t_philo *philo)
{
	long int	current_time;
	long int	copy_time_to_eat;
	
	current_time = 0;
	if (is_it_over(philo) == true)
		return (DEAD);
	pthread_mutex_lock(&(philo->shared->talk));
	philo->start_to_eat = get_time(philo->shared->start_time);
	if (still_alive_or_not(philo->start_to_eat, philo) == DEAD)
		return (pthread_mutex_unlock(&(philo->shared->talk)), DEAD);
	copy_time_to_eat = philo->shared->time_to_eat;
	print_routine(EAT, philo->start_to_eat, philo->id_philo);
	philo->nbr_meal ++;
	did_i_eat_enough(philo);
	pthread_mutex_unlock(&(philo->shared->talk));
	current_time = (get_time(philo->shared->start_time) - philo->start_to_eat);
	while ( current_time < copy_time_to_eat)
	{
		current_time = (get_time(philo->shared->start_time) - philo->start_to_eat);
		usleep(philo->shared->nbr_philo * 10);
		if (still_alive_or_not(philo->start_to_eat, philo) == DEAD)
			return (DEAD);
	}
	philo->lifetime += copy_time_to_eat;
	philo->nbr_fork = 0;
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

static int	sleeping(t_philo *philo)
{
	long int	copy_time_to_sleep;
	long int	current_time;

	copy_time_to_sleep = 0;
	if (is_it_over(philo) == true)
		return (DEAD);
	pthread_mutex_lock(&(philo->shared->talk));
	philo->start_to_sleep = get_time(philo->shared->start_time);
	if (still_alive_or_not(philo->start_to_sleep, philo) == DEAD)
		return (pthread_mutex_unlock(&(philo->shared->talk)), DEAD);
	copy_time_to_sleep = philo->shared->time_to_sleep;
	print_routine(SLEEP, philo->start_to_sleep, philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->talk));
	current_time = (get_time(philo->shared->start_time) \
	- philo->start_to_sleep);
	while (current_time < copy_time_to_sleep)
	{
		current_time = (get_time(philo->shared->start_time) \
		- philo->start_to_sleep);
		usleep(philo->shared->nbr_philo * 10);
	}
	philo->lifetime += copy_time_to_sleep;
	return (ALIVE);
}
