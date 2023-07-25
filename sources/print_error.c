/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:15:27 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/24 12:49:12 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int error_code)
{
	if (error_code == MALLOC_FAIL)
		ft_dprintf(2, RED"ERROR: A malloc failed"END);
}

void	print_error_parsing(int error_code)
{
	if (error_code == NB_ARG)
	{
		ft_dprintf(2, RED"ERROR: Wrong number of arguments\n"END);
		ft_dprintf(2, "The program must be launch with the following arguments: \n");
		ft_dprintf(2, "   - number of philosophers\n   - time to die\n   - time to sleep\n");
		ft_dprintf(2, "   - [optional] number of time each philosopher must eat\n");
	}
	if (error_code == WRONG_ARG || error_code == EMPTY_ARG ||error_code == ZERO) 
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
	ft_dprintf(2, YELLOW"WARNING: Times under 60ms will lead to the death of the philosophers\n"END);
}
