/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:25:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/11 12:19:33 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*======================= LIBRAIRIES =======================*/

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include "../ft_dprintf/ft_dprintf.h"

/*======================= COULEUR =======================*/

# define END "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"

/*======================= ENUMERATION =======================*/

enum {
	NB_ARG,
	WRONG_ARG,
	EMPTY_ARG,
	ZERO,
	MALLOC_FAIL,
	INIT_MUTEX_FAIL,
	DEST_MUTEX_FAIL,
	THREAD_CREATION_FAIL,
	GET_TIME_FAIL,
};

enum {
	SUCCESS = 0,
	FAILURE = -1,
};

enum {
	FREE,
	TAKEN,
};

enum {
	TAKE_FORK,
	THINK,
	EAT,
	SLEEP,
	ALIVE,
	DEAD,
};

/*======================= STRUCTURES =======================*/

typedef struct s_philo		t_philo;
typedef struct s_data		t_data;

struct s_philo {
	int				id_philo;
	int				left_fork;
	int				*right_fork;
	int				nbr_meal;
	int				nbr_fork;
	long int		lifetime;
	long int		start_to_eat;
	long int		end_to_eat;
	long int		start_to_sleep;
	bool			am_i_dead;
	pthread_t		id_thread;
	pthread_mutex_t	left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	t_data			*shared;
};

struct s_data {
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_philo_finished_eating;
	int					nbr_t_must_eat;
	struct timeval		start_time;
	bool				this_is_the_end;
	pthread_mutex_t		launcher;
	pthread_mutex_t		talk;
	t_philo				*philo;
};

/*======================= PROTOTYPES =======================*/

/* ---- death.c ----*/
bool	is_it_over(t_philo	*philo);
int	still_alive_or_not(int current_time, t_philo *philo);

/* ---- fork.c ----*/
int			take_forks(t_philo *philo);
void		leave_forks(t_philo *philo);

/* ---- init_philo.c ----*/
int			create_philosophers(t_data *shared);

/* ---- launch_philo.c ----*/
int			launch_philo(t_data *shared);

/* ---- parsing.c ----*/
bool		parse_arg(int ac, char **av, t_data *data);

/* ---- print_messages.c ----*/
void		print_error(int error_code);
void		print_error_parsing(int error_code);
void		print_warning(void);
void		print_routine(int action, long int timestamp, int philo_id);
/* ---- routine.c ----*/
void		routine(t_philo *philo);

/* ---- utils.c ----*/
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		init_structure_shared(t_data *shared);
long int	get_time(struct timeval start_time);
int			kill_the_philosophers(t_data *shared);

#endif