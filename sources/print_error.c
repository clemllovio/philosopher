/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:15:27 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/20 15:39:11 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error_parsing(int error_code)
{
	if (error_code == NB_ARG)
	{
		printf(RED"ERROR: Wrong number of arguments\n"END);
		printf("The program must be launch with the following arguments: \n");
		printf("   - number of philosophers\n   - time to die\n   - time to sleep\n");
		printf("   - [optional] number of time each philosopher must eat\n");
	}
	if (error_code == WRONG_ARG || error_code == EMPTY_ARG) 
		printf(RED"ERROR : non-valid argument\n"END);
	if (error_code == WRONG_ARG)
		printf("Only number without sign are accepted\n");
	else if (error_code == EMPTY_ARG)
		printf("Empty argument\n");
}

//checker que c vraiment ca
void	print_warning(void)
{
	printf(YELLOW"WARNING: Times under 60ms will lead to the death of the philosophers\n"END);
}
