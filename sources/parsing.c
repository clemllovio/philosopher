/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:49:52 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/01 12:06:12 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_number(char **tab);
static int	get_value(char **av, t_data *shared);

bool	parse_arg(int ac, char **av, t_data *shared)
{
	if (ac != 5 && ac != 6)
		return (print_error_parsing(NB_ARG), false);
	if (check_number(av) == false)
		return (false);
	if (get_value(av, shared) == FAILURE)
		return (false);
	if (shared->time_to_die == 0 || shared->time_to_eat == 0 || \
	shared->time_to_sleep == 0 \
	|| shared->nbr_t_must_eat == 0 || shared->nbr_philo == 0)
		return (print_error_parsing(ZERO), false);
	if (shared->time_to_die < 60 || shared->time_to_eat < 60 || \
	shared->time_to_sleep < 60)
		print_warning();
	return (true);
}

static bool	check_number(char **tab)
{
	int	row;
	int	col;

	row = 1;
	while (tab[row])
	{
		col = 0;
		if (tab[row][0] == '\0')
			return (print_error_parsing(EMPTY_ARG), false);
		while (tab[row][col])
		{
			if (tab[row][col] >= '0' && tab[row][col] <= '9')
				col++;
			else
				return (print_error_parsing(WRONG_ARG), false);
		}
		row++;
	}
	return (true);
}

static int	get_value(char **av, t_data *shared)
{
	shared->nbr_philo = ft_atoi(av[1]);
	if (shared->nbr_philo == FAILURE)
		return (FAILURE);
	shared->time_to_die = ft_atoi(av[2]);
	if (shared->time_to_die == FAILURE)
		return (FAILURE);
	shared->time_to_eat = ft_atoi(av[3]);
	if (shared->time_to_eat == FAILURE)
		return (FAILURE);
	shared->time_to_sleep = ft_atoi(av[4]);
	if (shared->time_to_sleep == FAILURE)
		return (FAILURE);
	if (av[5])
	{
		shared->nbr_t_must_eat = ft_atoi(av[5]);
		if (shared->nbr_t_must_eat == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
