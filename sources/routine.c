/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:02:23 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/14 11:11:36 by cllovio          ###   ########.fr       */
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
			usleep(philo->shared->nbr_philo * 10);
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
	pthread_mutex_unlock(&(philo->shared->talk));
	print_routine(philo, THINK);
}

static void	eat(t_philo *philo)
{
	long int	current_time;
	long int	copy_time_to_eat;

	current_time = 0;
	if (is_it_over(philo) == true)
		return ;
	pthread_mutex_lock(&(philo->shared->talk));
	philo->start_to_eat = get_time(philo->shared->start_time);
	philo->lifetime = philo->shared->time_to_die + philo->start_to_eat;
	pthread_mutex_unlock(&(philo->shared->talk));
	if (still_alive_or_not(philo->start_to_eat, philo) == DEAD)
		return ;
	philo->nbr_meal ++;
	print_routine(philo, EAT);
	pthread_mutex_lock(&(philo->shared->talk));
	copy_time_to_eat = philo->shared->time_to_eat;
	pthread_mutex_unlock(&(philo->shared->talk));
	if (do_the_action(philo, philo->start_to_eat, \
	philo->shared->time_to_eat) == DEAD)
		return ;
	philo->nbr_fork = 0;
	did_i_eat_enough(philo);
}

static void	sleeping(t_philo *philo)
{
	long int	copy_time_to_sleep;

	copy_time_to_sleep = 0;
	if (is_it_over(philo) == true)
		return ;
	pthread_mutex_lock(&(philo->shared->talk));
	philo->start_to_sleep = get_time(philo->shared->start_time);
	if (still_alive_or_not(philo->start_to_sleep, philo) == DEAD)
		return ;
	copy_time_to_sleep = philo->shared->time_to_sleep;
	pthread_mutex_unlock(&(philo->shared->talk));
	print_routine(philo, SLEEP);
	if (do_the_action(philo, philo->start_to_sleep, \
	philo->shared->time_to_sleep) == DEAD)
		return ;
}
