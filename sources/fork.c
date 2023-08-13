/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:32 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/11 12:39:40 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_left_fork(t_philo *philo);
static void	take_right_fork(t_philo *philo);

int	take_forks(t_philo *philo)
{
	if (is_it_over(philo) == true)
		return (SUCCESS);
	take_left_fork(philo);
	take_right_fork(philo);
	pthread_mutex_lock(&(philo->shared->talk));
	if (still_alive_or_not(get_time(philo->shared->start_time), philo) == DEAD)
		return (pthread_mutex_unlock(&(philo->shared->talk)), SUCCESS);
	pthread_mutex_unlock(&(philo->shared->talk));
	if (philo->nbr_fork == 2)
		return (SUCCESS);
	else
		return (FAILURE);
}

static void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork_mutex));
	if (philo->left_fork == FREE)
	{
		philo->left_fork = TAKEN;
		pthread_mutex_lock(&(philo->shared->launcher));
		print_routine(TAKE_FORK, get_time(philo->shared->start_time), philo->id_philo);
		pthread_mutex_unlock(&(philo->shared->launcher));
		philo->nbr_fork++;
	}
	pthread_mutex_unlock(&(philo->left_fork_mutex));
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*(philo->right_fork) == FREE)
	{
		*(philo->right_fork) = TAKEN;
		pthread_mutex_lock(&(philo->shared->launcher));
		print_routine(TAKE_FORK, get_time(philo->shared->start_time), philo->id_philo);
		pthread_mutex_unlock(&(philo->shared->launcher));
		philo->nbr_fork++;
	}
	pthread_mutex_unlock(philo->right_fork_mutex);
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork_mutex));
	if (philo->left_fork == TAKEN)
		philo->left_fork = FREE;
	pthread_mutex_unlock(&(philo->left_fork_mutex));
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*(philo->right_fork) == TAKEN)
		*(philo->right_fork) = FREE;
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_lock(&(philo->shared->launcher));
	pthread_mutex_unlock(&(philo->shared->launcher));
}
