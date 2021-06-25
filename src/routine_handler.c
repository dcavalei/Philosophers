/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:27:41 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/25 19:52:55 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(void *content);
static void	unlock_forks(void *content);
static void	start_eating(void *content);
static void	start_sleeping(void *content);

void	*routine(void *content)
{
	suseconds_t	time_start;
	// suseconds_t	time_last_meal;
	t_data		*data;
	int			philo_id;
	int			times_to_eat;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	times_to_eat = data->num_of_eat;
	while (times_to_eat--)
	{
		time_start = timer();
		lock_forks(content);
		start_eating(content);
		//usleep(data->time_to_eat);
		unlock_forks(content);
		start_sleeping(content);
		//usleep(data->time_to_eat);
		//usleep(500000);
		//time_last_meal = timer();
		// sleep(1);
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "YEL"thinking"NC"\n", timer(), philo_id + 1);
	}

	free(content);
	return (NULL);
}

static void	start_eating(void *content)
{
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;

	printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "YEL"eating"NC"\n", timer(), philo_id + 1);
}

static void	start_sleeping(void *content)
{
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;

	printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" is "YEL"sleeping"NC"\n", timer(), philo_id + 1);
}

static void	lock_forks(void *content)
{
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	if (philo_id % 2)
	{
		pthread_mutex_lock(&(data->fork[philo_id]));
		if(data->lock[philo_id] == 0)
			data->lock[philo_id] = 1;
		else
		{
			int	start = timer();
			while (1)
			{
				if (is_dead())
				{
					
				}
			}
			usleep(data->)
		}
		


		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" has taken a "YEL"fork"NC"\n", timer(), philo_id + 1);
		pthread_mutex_lock(&(data->fork[(philo_id + 1) % data->num_of_philo]));
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" has taken a "YEL"fork"NC"\n", timer(), philo_id + 1);
	}
	else
	{
		pthread_mutex_lock(&(data->fork[(philo_id + 1) % data->num_of_philo]));
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" has taken a "YEL"fork"NC"\n", timer(), philo_id + 1);
		pthread_mutex_lock(&(data->fork[philo_id]));
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" has taken a "YEL"fork"NC"\n", timer(), philo_id + 1);
	}
}

static void	unlock_forks(void *content)
{
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	if (philo_id % 2)
	{
		pthread_mutex_unlock(&(data->fork[philo_id]));
		pthread_mutex_unlock(&(data->fork[(philo_id + 1) % data->num_of_philo]));
	}
	else
	{
		pthread_mutex_unlock(&(data->fork[(philo_id + 1) % data->num_of_philo]));
		pthread_mutex_unlock(&(data->fork[philo_id]));
	}}
