/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:15:27 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/01 14:00:36 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int error_code)
{
	if (error_code == MALLOC_FAIL)
		ft_dprintf(2, RED"ERROR: Malloc failed\n"END);
	else if (error_code == INIT_MUTEX_FAIL)
		ft_dprintf(2, RED"ERROR: Mutex initialisation failed\n"END);
	else if (error_code == DEST_MUTEX_FAIL)
		ft_dprintf(2, RED"ERROR: Mutex destruction failed\n"END);
	else if (error_code == THREAD_CREATION_FAIL)
		ft_dprintf(2, RED"ERROR: Thread creation failed\n"END);
}

void	print_error_parsing(int error_code)
{
	if (error_code == NB_ARG)
	{
		ft_dprintf(2, RED"ERROR: Wrong number of arguments\n"END);
		ft_dprintf(2, "The program must be launch with the following argument");
		ft_dprintf(2, "s:\n   - number of philosophers\n   - time to die\n   ");
		ft_dprintf(2, "-time to eat\n   - time to sleep\n   - [optional]");
		ft_dprintf(2, "- [optional] number of time each philosopher must eat\n");
	}
	if (error_code == WRONG_ARG || error_code == EMPTY_ARG \
	|| error_code == ZERO)
		ft_dprintf(2, RED"ERROR : non-valid argument\n"END);
	if (error_code == WRONG_ARG)
		ft_dprintf(2, "Only number without sign are accepted\n");
	else if (error_code == EMPTY_ARG)
		ft_dprintf(2, "Empty argument\n");
	else if (error_code == ZERO)
		ft_dprintf(2, "Times or number of philosphers must superior to 0\n");
}

//checker que c vraiment ca
void	print_warning(void)
{
	ft_dprintf(2, YELLOW"WARNING: Times under 60ms will lead ");
	ft_dprintf(2, "to the death of the philosophers\n"END);
}
