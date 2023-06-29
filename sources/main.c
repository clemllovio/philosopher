/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/06/29 14:52:52 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parse_arg(int ac, char **av);
void	print_error(int error_code);

int	main(int ac, char **av)
{
	parse_arg(ac, av);
}

bool	parse_arg(int ac, char **av)
{
	(void)av;
	
	if (ac != 5 && ac != 6)
		return (print_error(NB_ARG), false);
	return (true);
}

void	print_error(int error_code)
{
	if (error_code == NB_ARG)
	{
		printf(RED"error : wrong number of arguments\n"END);
		printf("the program must be launch with the following arguments: \n");
		printf("   number of philosophers\n   time to die\n   timeto sleep\n");
		printf("   [optional] number of time each philosopher must eat\n");
	}
}