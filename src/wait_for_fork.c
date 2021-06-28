/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:02:30 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/28 20:45:52 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philosopher_edge_case(void *content, t_data *data, int index);
static void	lock_from_right_to_left(t_data *data, int index);
static void	lock_from_left_to_right(t_data *data, int index);

int	wait_for_fork(void *content, t_data *data, int index)
{
	if (data->num_of_philo == 1)
		return (one_philosopher_edge_case(content, data, index));
	while (!data->someone_died)
	{
		if (index % 2)
			lock_from_right_to_left(data, index);
		else
			lock_from_left_to_right(data, index);

		//printf("philo %i, timer%li last meal%li\n", index, timer(), ((t_content *)content)->last_meal);
		if (timer() >= 450)
		// if (timer() >= 313)
		{
			printf("philo %i, timer %li, last meal-> %li\n", index + 1, timer(), ((t_content *)content)->last_meal);
			while (1)
			{
			}
		}
		
		if (is_dead(content))
			return (death_handler(data, ((t_content *)content)->philo_id));
		if (data->lock[index] == index
			&& data->lock[(index + 1) % data->num_of_philo] == index)
			return (!(data->someone_died));
		usleep(1);
	}
	return (0);
}

int	unlock_forks(void *content, t_data *data, int index)
{
	data->lock[index] = -1;
	data->lock[(index + 1) % data->num_of_philo] = -1;
	if (data->someone_died)
		return (0);
	((t_content *)content)->last_meal = timer();
	return (1);
}

static int	one_philosopher_edge_case(void *content, t_data *data, int index)
{
	while (1)
	{
		if (data->lock[index] == -1)
		{
			data->lock[index] = index;
			output_action(data, index, FORK_TAKEN);
		}
		if (is_dead(content))
			return (death_handler(data, index));
		usleep(1);
	}
}

static void	lock_from_right_to_left(t_data *data, int index)
{
	pthread_mutex_lock(&(data->fork[(index + 1) % data->num_of_philo]));
	pthread_mutex_lock(&(data->fork[index]));
	if (data->lock[(index + 1) % data->num_of_philo] == -1)
	{
		data->lock[(index + 1) % data->num_of_philo] = index;
		output_action(data, index, FORK_TAKEN);
	}
	if (data->lock[index] == -1)
	{
		data->lock[index] = index;
		output_action(data, index, FORK_TAKEN);
	}
	pthread_mutex_unlock(&(data->fork[(index + 1) % data->num_of_philo]));
	pthread_mutex_unlock(&(data->fork[index]));
}

static void	lock_from_left_to_right(t_data *data, int index)
{
	pthread_mutex_lock(&(data->fork[index]));
	pthread_mutex_lock(&(data->fork[(index + 1) % data->num_of_philo]));
	if (data->lock[index] == -1)
	{
		data->lock[index] = index;
		output_action(data, index, FORK_TAKEN);
	}
	if (data->lock[(index + 1) % data->num_of_philo] == -1)
	{
		data->lock[(index + 1) % data->num_of_philo] = index;
		output_action(data, index, FORK_TAKEN);
	}
	pthread_mutex_unlock(&(data->fork[index]));
	pthread_mutex_unlock(&(data->fork[(index + 1) % data->num_of_philo]));
}
