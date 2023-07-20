/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:49:52 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/20 15:34:09 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_number(char **tab);
static void	get_value(char **av, t_shared *shared);
static int	ft_atoi(const char *str);

bool	parse_arg(int ac, char **av, t_shared *shared)
{
	if (ac != 5 && ac != 6)
		return (print_error_parsing(NB_ARG), false);
	if (check_number(av) == false)
		return (false);
	get_value(av, shared);
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

static void	get_value(char **av, t_shared *shared)
{
	shared->nbr_philo = ft_atoi(av[1]);
	shared->t_to_die = ft_atoi(av[2]);
	shared->t_to_eat = ft_atoi(av[3]);
	shared->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		shared->nbr_t_must_eat = ft_atoi(av[5]);
}

static int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (result != (result * 10 + (str[i] - 48)) / 10)
			return (-1);
		i++;
	}
	return ((int)(result));
}