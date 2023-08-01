/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/31 11:59:34 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	kill_the_philosophers(t_data *shared);

int	main(int ac, char **av)
{
	t_data	shared;

	init_structure_shared(&shared);
	if (parse_arg(ac, av, &shared) == false)
		return (FAILURE);
	if (create_philosophers(&shared) == FAILURE)
		return (FAILURE);
	if (kill_the_philosophers(&shared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
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