/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:20:18 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/02 16:48:51 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	kill_the_philosophers(t_data *shared);
void	routine(t_philo *philo);
int		launch_philo(t_data *shared);
int		wait_the_philo(t_data *shared);
long int	get_time(void);
void	think(t_philo *philo);
void	philo_says(int action, long int timestamp, int philo_id);
int		take_a_fork(t_philo *philo);
void	leave_fork(t_philo *philo);
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);

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
	// if (kill_the_philosophers(&shared) == FAILURE)
	// 	return (FAILURE);
	return (SUCCESS);
}

int	launch_philo(t_data *shared)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(shared->launcher));

	while (i < shared->nbr_philo)
	{
		if (pthread_create(&(shared->philo[i].id_thread), NULL, (void *)routine, &(shared->philo[i])) \
		!= 0)
			return (print_error(THREAD_CREATION_FAIL), FAILURE);//destroy les mutex
		i++;
	}
	shared->start_time = get_time();
	if (shared->start_time == -1)
		return (FAILURE);
	pthread_mutex_unlock(&(shared->launcher));
	if (wait_the_philo(shared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

long int	get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) == -1)
		return (print_error(GET_TIME_FAIL), FAILURE);
	return (((tv.tv_sec % 1000) * 1000) + (tv.tv_usec / 1000));
}

int	wait_the_philo(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->nbr_philo)
	{
		if (pthread_join(shared->philo[i].id_thread, NULL) != 0)
			return (FAILURE); // destroy les mutex
		i++;
	}
	return (SUCCESS);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	pthread_mutex_unlock(&(philo->shared->launcher));
	if (philo->id_philo % 2 == 1)
		usleep(20000);
	think(philo);
	while (take_a_fork(philo) == FAILURE)
		;
	eat(philo);
	leave_fork(philo);
	sleeping(philo);
}

void	think(t_philo *philo)
{
	long int	current_time;

	pthread_mutex_lock(&(philo->shared->launcher));
	current_time = get_time() - philo->shared->start_time;
	philo_says(THINK, current_time, philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->launcher));
}

int	take_a_fork(t_philo *philo)
{
	int	nbr_fork;

	nbr_fork = 0;
	pthread_mutex_lock(&(philo->left_fork_mutex));
	if (philo->left_fork == FREE)
	{
		philo->left_fork = TAKEN;
		nbr_fork++;
	}
	pthread_mutex_unlock(&(philo->left_fork_mutex));
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*(philo->right_fork) == FREE)
	{
		*(philo->right_fork) = TAKEN;
		nbr_fork++;
	}
	pthread_mutex_unlock(philo->right_fork_mutex);
	if (nbr_fork == 2)
	{
		pthread_mutex_lock(&(philo->shared->launcher));
		philo_says(TAKE_FORK, (get_time() - philo->shared->start_time), philo->id_philo);
		pthread_mutex_unlock(&(philo->shared->launcher));
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	philo->start_to_eat = get_time() - philo->shared->start_time;
	philo_says(EAT, philo->start_to_eat, philo->id_philo);
	philo->end_to_eat = get_time() - philo->start_to_eat;
	pthread_mutex_unlock(&(philo->shared->launcher));
}

void	leave_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork_mutex));
	if (philo->left_fork == TAKEN)
		philo->left_fork = FREE;
	pthread_mutex_unlock(&(philo->left_fork_mutex));
	pthread_mutex_lock(philo->right_fork_mutex);
	if (*(philo->right_fork) == TAKEN)
		*(philo->right_fork) = FREE;
	pthread_mutex_unlock(philo->right_fork_mutex);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->shared->launcher));
	philo_says(SLEEP, (get_time() - philo->shared->start_time), philo->id_philo);
	pthread_mutex_unlock(&(philo->shared->launcher));
}

void	philo_says(int action, long int timestamp, int philo_id)
{
	if (action == TAKE_FORK)
		ft_dprintf(1, BLUE"%d %d has taken a fork\n"END, timestamp, philo_id);
	else if (action == THINK)
		ft_dprintf(1, GREEN"%d %d is thinking\n"END, timestamp, philo_id);
	else if (action == EAT)
		ft_dprintf(1, PURPLE"%d %d is eating\n"END, timestamp, philo_id);
	else if (action == SLEEP)
		ft_dprintf(1, YELLOW"%d %d is sleeping\n"END, timestamp, philo_id);
	else if (action == DEAD)
		ft_dprintf(1, GREEN"%d %d died\n"END, timestamp, philo_id);
}

int	kill_the_philosophers(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->nbr_philo - 1)
	{
		if (pthread_mutex_destroy(&(shared->philo[i].left_fork_mutex)) != 0)
			return (print_error(DEST_MUTEX_FAIL), FAILURE);
	}
	free(shared->philo);
	return (SUCCESS);
}
