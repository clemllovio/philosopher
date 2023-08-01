/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/01 16:47:20 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	kill_the_philosophers(t_data *shared);
void	routine(t_philo *philo);
int		launch_philo(t_data *shared);
int	wait_the_philo(t_data *shared);

int	main(int ac, char **av)
{
	t_data	shared;

	init_structure_shared(&shared);
	if (parse_arg(ac, av, &shared) == false)
		return (FAILURE);
	if (create_philosophers(&shared) == FAILURE)
		return (FAILURE);
	if (launch_philo(&shared) == FAILURE)
		return (FAILURE);
	if (kill_the_philosophers(&shared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	launch_philo(t_data *shared)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(shared->launcher));
	while (i < shared->nbr_philo)
	{
		if (pthread_create(&(shared->philo[i].id_thread), NULL, (void *)routine, &(shared->philo[i])) \
		!= 0)
			return (print_error(THREAD_CREATION_FAIL), FAILURE);//destroy les mutex
		i++;
	}
	pthread_mutex_unlock(&(shared->launcher));
	if (shared->nbr_philo == 0)
		return (SUCCESS);
	if (wait_the_philo(shared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	wait_the_philo(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->nbr_philo)
	{
		if (pthread_join(shared->philo[i].id_thread, NULL) != 0)
			return (FAILURE); // destroy les mutex
		i++;
	}
	return (SUCCESS);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	pthread_mutex_unlock(&(philo->shared->launcher));
	pthread_mutex_lock(&(philo->shared->talk));
	ft_dprintf(1, "Je suis le philospher numero %d\n", philo->id_philo);
	philo->shared->nbr_philo--;
	pthread_mutex_unlock(&(philo->shared->talk));
}

int	kill_the_philosophers(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->nbr_philo - 1)
	{
		if (pthread_mutex_destroy(&(shared->philo[i].left_fork_mutex)) != 0)
			return (print_error(DEST_MUTEX_FAIL), FAILURE);
	}
	free(shared->philo);
	return (SUCCESS);
}
