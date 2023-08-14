/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:32 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/14 11:11:51 by cllovio          ###   ########.fr       */
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
	if (still_alive_or_not(get_time(philo->shared->start_time), philo) == DEAD)
		return (SUCCESS);
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
		print_routine(philo, TAKE_FORK);
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
		print_routine(philo, TAKE_FORK);
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
}
