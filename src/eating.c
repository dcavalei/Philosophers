/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:31:44 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/26 15:51:59 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_handler(t_data *data, int philo_index)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (0);
	}
	else
	{
		data->someone_died = 1;
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i"NC" has "RED"died"NC"...\n", timer(), philo_index + 1);
		pthread_mutex_unlock(&data->dead_mutex);
	}
	return (0);
}

int	is_dead(void *content)
{
	t_data		*data;
	long		last_meal;

	data = ((t_content *)content)->data;
	last_meal = ((t_content *)content)->last_meal;
	if (timer() - last_meal > data->time_to_die)
		return (1);
	else
		return (0);
}

int	wait_for_fork(void *content, t_data *data, int index)
{
	while (!data->someone_died)
	{
		pthread_mutex_lock(&(data->fork[index]));
		if(data->lock[index] == 0)
		{
			data->lock[index] = 1;
			pthread_mutex_unlock(&(data->fork[index]));
			return (!(data->someone_died));
		}
		else
		{
			pthread_mutex_unlock(&(data->fork[index]));
			while (1)
			{
				if (is_dead(content))
					return (death_handler(data, ((t_content *)content)->philo_id));
				else if (data->lock[index] == 0)
					break ;
				usleep(1);
			}
		}
	}
	return (0);
}
