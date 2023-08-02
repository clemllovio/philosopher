/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:04:32 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/02 20:05:25 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_a_fork(t_philo *philo)
{
	int	nbr_fork;

	nbr_fork = 0;
	pthread_mutex_lock(&(philo->left_fork_mutex));
	if (philo->left_fork == FREE)
	{
		philo->left_fork = TAKEN;
		nbr_fork++;
	}
	pthread_mutex_unlock(&(philo->left_fork_mutex));
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*(philo->right_fork) == FREE)
	{
		*(philo->right_fork) = TAKEN;
		nbr_fork++;
	}
	pthread_mutex_unlock(philo->right_fork_mutex);
	if (nbr_fork == 2)
	{
		pthread_mutex_lock(&(philo->shared->launcher));
		philo_says(TAKE_FORK, (get_time() - philo->shared->start_time), philo->id_philo);
		pthread_mutex_unlock(&(philo->shared->launcher));
		return (SUCCESS);
	}
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
}
