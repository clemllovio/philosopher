/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/07 15:57:48 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
