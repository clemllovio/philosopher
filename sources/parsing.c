/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:49:52 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/21 14:12:20 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_number(char **tab);
static void	get_value(char **av, t_data *shared);

bool	parse_arg(int ac, char **av, t_data *shared)
{
	if (ac != 5 && ac != 6)
		return (print_error_parsing(NB_ARG), false);
	if (check_number(av) == false)
		return (false);
	get_value(av, shared);
	if (shared->t_to_die == 0 || shared->t_to_eat == 0 || shared->t_to_sleep == 0 \
	|| shared->nbr_t_must_eat == 0 || shared->nbr_philo == 0)
		return (print_error_parsing(ZERO), false);
	if (shared->t_to_die < 60 || shared->t_to_eat < 60 || shared->t_to_sleep < 60)
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

// securiser
static void	get_value(char **av, t_data *shared)
{
	shared->nbr_philo = ft_atoi(av[1]);
	shared->t_to_die = ft_atoi(av[2]);
	shared->t_to_eat = ft_atoi(av[3]);
	shared->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		shared->nbr_t_must_eat = ft_atoi(av[5]);
}
