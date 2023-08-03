/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:32 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/03 13:58:46 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork_mutex));
	if (philo->left_fork == FREE)
	{
		philo->left_fork = TAKEN;
		pthread_mutex_lock(&(philo->shared->launcher));
		philo_says(TAKE_FORK, get_time(philo->shared->start_time), philo->id_philo);
		pthread_mutex_unlock(&(philo->shared->launcher));
		philo->nbr_fork++;
	}
	pthread_mutex_unlock(&(philo->left_fork_mutex));
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*(philo->right_fork) == FREE)
	{
		*(philo->right_fork) = TAKEN;
		pthread_mutex_lock(&(philo->shared->launcher));
		philo_says(TAKE_FORK, get_time(philo->shared->start_time), philo->id_philo);
		pthread_mutex_unlock(&(philo->shared->launcher));
		philo->nbr_fork++;
	}
	pthread_mutex_unlock(philo->right_fork_mutex);
	usleep(1000);
	if (philo->nbr_fork == 2)
		return (SUCCESS);
	else
		return (FAILURE);
}

void	leave_fork(t_philo *philo)
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
