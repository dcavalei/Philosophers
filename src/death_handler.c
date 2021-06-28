/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 22:31:44 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/28 22:26:21 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_handler(t_data *data, int index)
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
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i "NC, timer(), index + 1);
		printf("has "RED"died"NC"...\n");
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
	{
		return (1);
	}
	return (0);
}
