/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:56:24 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/31 11:59:22 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int init_struct_philo(t_data *shared, int i);
static int	init_mutex_philo(t_data *shared, int i);
static int	init_mutex_shared(t_data *shared);

int	create_philosophers(t_data *shared)
{
	int	i;

	i = 0;
	shared->philo = ft_calloc(shared->nbr_philo, sizeof(t_philo));
	if (!(shared->philo))
		return (print_error(MALLOC_FAIL), FAILURE);
	if (init_mutex_shared(shared) == FAILURE)
		return (FAILURE);
	while (i < shared->nbr_philo)
	{
		if (init_struct_philo(shared, i) == FAILURE)
		{
			pthread_mutex_destroy(&(shared->launcher));
			pthread_mutex_destroy(&(shared->talk));
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_mutex_shared(t_data *shared)
{
	if (pthread_mutex_init(&(shared->launcher), NULL) != 0)
		return (print_error(INIT_MUTEX_FAIL), FAILURE);
	if (pthread_mutex_init(&(shared->talk), NULL) != 0)
	{
		pthread_mutex_destroy(&(shared->launcher));
		return (print_error(INIT_MUTEX_FAIL), FAILURE);
	}
	return (SUCCESS);
}

static int init_struct_philo(t_data *shared, int i)
{
	shared->philo[i].id_philo = i + 1;
	shared->philo[i].shared = shared;
	shared->philo[i].nbr_meal = 0;
	shared->philo[i].am_i_dead = false;
	if (i == shared->nbr_philo - 1)
	{
		shared->philo[i].right_fork_mutex = 
			&(shared->philo[0].left_fork_mutex);
		shared->philo[i].right_fork = 
			&(shared->philo[0].left_fork);
	}
	else
	{
		shared->philo[i].right_fork_mutex = 
			&(shared->philo[i + 1].left_fork_mutex);
		shared->philo[i].right_fork = &(shared->philo[i + 1].left_fork);
	}
	if (init_mutex_philo(shared, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_mutex_philo(t_data *shared, int i)
{
	if (pthread_mutex_init(&(shared->philo[i].left_fork_mutex), NULL) != 0)
	{
		print_error(INIT_MUTEX_FAIL);
		while (--i > -1)
		{
			if (pthread_mutex_destroy(&(shared->philo[i].left_fork_mutex)) != 0)
				print_error(DEST_MUTEX_FAIL);
		}
		return (FAILURE);
	}
	return (SUCCESS);
}
