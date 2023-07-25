/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/24 13:17:44 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_structure_shared(t_data *shared);
static int	create_philo(t_data *shared);

int	main(int ac, char **av)
{
	t_data	shared;

	init_structure_shared(&shared);
	if (parse_arg(ac, av, &shared) == false)
		return (FAILURE);
	if (create_philo(&shared) == FAILURE)
		return (FAILURE);
	free(shared.philo);
}

static void	init_structure_shared(t_data *shared)
{
	shared->nbr_philo = 0;
	shared->t_to_die = 0;
	shared->t_to_eat = 0;
	shared->nbr_t_must_eat = -1;
}

static int	create_philo(t_data *shared)
{
	int	index;

	index = 0;
	shared->philo = ft_calloc(shared->nbr_philo, sizeof(t_philo));
	if (!(shared->philo))
		return (print_error(MALLOC_FAIL), FAILURE);
	while (index < shared->nbr_philo)
	{
		shared->philo[index].id_philo = index + 1;
		index++;
	}
	return (SUCCESS);
}
