/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:25:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/20 15:41:00 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>

# define END "\033[0m"
# define GREY "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"

# define END "\033[0m"
# define BOLD "\033[1m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define DEL_LINE "\033[2K\r"

enum {
	NB_ARG,
	WRONG_ARG,
	EMPTY_ARG,
};

typedef struct s_shared {
	int	nbr_philo;
	int	t_to_die;
	int	t_to_eat;
	int	t_to_sleep;
	int	nbr_t_must_eat;
} t_shared;

typedef struct s_philo {
	int	id;
} t_philo

bool	parse_arg(int ac, char **av, t_shared *shared);
void	print_error_parsing(int error_code);
void	print_warning(void);

#endif