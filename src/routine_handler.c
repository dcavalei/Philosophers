/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:27:41 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/26 15:39:44 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks(void *content);
static int	unlock_forks(void *content);
static int	start_eating(void *content);
static int	start_sleeping(void *content);



void	*routine(void *content)
{
	// suseconds_t	time_start;
	// suseconds_t	time_last_meal;
	t_data		*data;
	int			philo_id;
	int			times_to_eat;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	times_to_eat = data->num_of_eat;
	while (times_to_eat--)
	{
		if (((t_content *)content)->last_meal == 0)
			((t_content *)content)->last_meal = timer();
		if (!lock_forks(content))
			break ;
		if (!start_eating(content))
			break ;
		if (!unlock_forks(content))
			break ;
		if(!start_sleeping(content))
			break ;
		//usleep(data->time_to_eat);
		//usleep(500000);
		//time_last_meal = timer();
		// sleep(1);
		output_action(data, philo_id, THINKING);
	}
	output_action(data, philo_id, SATISFIED);
	free(content);
	return (NULL);
}

static int	start_eating(void *content)
{
	t_data		*data;
	int			philo_id;
	long		time_start;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	time_start = timer();
	output_action(data, philo_id, EATING);
	while (timer() - time_start < data->time_to_eat)
	{
		if (data->someone_died)
			return (0);
		usleep(1);
	}
	((t_content *)content)->last_meal = timer();
	return (1);
}

static int	start_sleeping(void *content)
{
	t_data		*data;
	int			philo_id;
	long		time_start;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	time_start = timer();
	output_action(data, philo_id, SLEEPING);
	while (timer() - time_start < data->time_to_sleep)
	{
		if (data->someone_died || is_dead(content))
			return (death_handler(data, philo_id + 1));
		usleep(1);
	}
	return (1);
}

static int	lock_forks(void *content)
{
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	if (philo_id % 2)
	{
		if (!wait_for_fork(content, data, philo_id))
			return (0);
		output_action(data, philo_id, FORK_TAKEN);
		if (!wait_for_fork(content, data, (philo_id + 1) % data->num_of_philo))
			return (0);
		output_action(data, philo_id, FORK_TAKEN);
	}
	else
	{
		if (!wait_for_fork(content, data, (philo_id + 1) % data->num_of_philo))
			return (0);
		output_action(data, philo_id, FORK_TAKEN);
		if (!wait_for_fork(content, data, philo_id))
			return (0);
		output_action(data, philo_id, FORK_TAKEN);
	}
	return (1);
}

static int	unlock_forks(void *content)
{
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	if (philo_id % 2)
	{
		data->lock[philo_id] = 0;
		data->lock[(philo_id + 1) % data->num_of_philo] = 0;
	}
	else
	{
		data->lock[(philo_id + 1) % data->num_of_philo] = 0;
		data->lock[philo_id] = 0;
	}
	if (data->someone_died)
		return (0);
	((t_content *)content)->last_meal = timer();
	return (1);
}

void	output_action(t_data *data, int philo_id, char *defined_message)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->someone_died)
	{
		if (!ft_strncmp(defined_message, FORK_TAKEN, 20))
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" has taken a "YEL"fork"NC".\n", timer(), philo_id + 1);
		else if (!ft_strncmp(defined_message, SLEEPING, 20))
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "YEL"sleeping"NC"!\n", timer(), philo_id + 1);
		else if (!ft_strncmp(defined_message, THINKING, 20))
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "YEL"thinking"NC"!\n", timer(), philo_id + 1);
		else if (!ft_strncmp(defined_message, EATING, 20))
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "YEL"eating"NC"!\n", timer(), philo_id + 1);
		else if (!ft_strncmp(defined_message, SATISFIED, 20))
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "GRN"satisfied"NC"!\n", timer(), philo_id + 1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
}