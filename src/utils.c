/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:31:54 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/25 20:13:31 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	data->someone_died = 0;
	data->num_of_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_of_eat = -1;
	data->thread = NULL;
	data->fork = NULL;
	data->lock = NULL;
}

int	data_setup(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->num_of_eat = ft_atoi(argv[5]);
	data->thread = malloc(sizeof(pthread_t) * (data->num_of_philo));
	if (!(data->thread))
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * (data->num_of_philo));
	if (!(data->fork))
		return (0);
	data->lock = malloc(sizeof(int) * (data->num_of_philo));
	if (!(data->lock))
		return (0);
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL) != 0)
			return (0);
		data->lock[i] = 0;
	}
	if (pthread_mutex_init(&(data->dead_mutex), NULL) != 0)
		return (0);
	return (1);
}

t_content	*content_handler(t_data *data, int index)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->data = data;
	content->philo_id = index;
	return (content);
}

suseconds_t	timer(void)
{
	struct timeval 		time;
	static time_t		start_sec = 0;
	static suseconds_t	start_micro_sec = 0;

	gettimeofday(&time, NULL);
	if (!start_sec)
	{
		start_sec = time.tv_sec;
		start_micro_sec = time.tv_usec;
	}
	return (((time.tv_sec - start_sec) * 1000) + (time.tv_usec - start_micro_sec) / 1000);
}