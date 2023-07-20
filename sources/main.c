/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/20 15:51:32 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_structure_shared(t_shared *shared);

int	main(int ac, char **av)
{
	t_shared	shared;

	init_structure_shared(&shared);
	parse_arg(ac, av, &shared);
	create_philo(&shared);
}

static void	init_structure_shared(t_shared *shared)
{
	shared->nbr_philo = 0;
	shared->t_to_die = 0;
	shared->t_to_eat = 0;
	shared->nbr_t_must_eat = -1;
}

//T'es sure de toi la ????
// void	create_philo(t_shared *shared)
// {
// 	t_philo	philo;
// 	int		i;
//
// 	i = 1;
// 	while (i <= shared->nbr_philo)
// 	{
// 		philo = (t_philo)malloc(sizeof(t_philo))
// 		if (!philo)
// 			return ;
// 		philo.id = i;
// 		i++;
// 	}
// }