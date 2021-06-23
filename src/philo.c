/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:59:26 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/23 20:37:02 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!((argc == 5 || argc == 6) && validate_user_input(argv)))
		return (error_handler(INVALID_INPUT, NULL));
	if (ft_atoi(argv[1]) > HARD_CAP)
		return (error_handler(TOO_MANY_THREADS, NULL));
	init_data(&data);
	timer();
	if(!(data_setup(&data, argc, argv) && create_and_join_threads(&data)))
		return (error_handler(errno, &data));
	i = -1;
	while (++i < data.num_of_philo)
		pthread_mutex_destroy(&(data.fork[i]));
	printf("No more threads AKA all finished :C\n");
	free(data.thread);
	free(data.fork);
	return(0);
}
void	init_data(t_data *data)
{
	data->num_of_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->num_of_eat = -1;
	data->thread = NULL;
	data->fork = NULL;
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
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL) != 0)
			return (0);
	}
	return (1);
}

void	*routine(void *content)
{
	suseconds_t	time_start;
	suseconds_t	time_last_meal;
	t_data		*data;
	int			philo_id;

	data = ((t_content *)content)->data;
	philo_id = ((t_content *)content)->philo_id;
	sleep(1);

	time_start = timer();
	time_last_meal = timer();
	printf("start[%li] last_meal[%li]\n", time_start, time_last_meal);
	pthread_mutex_lock(&(data->fork[philo_id - 1]));
	if (philo_id == data->num_of_philo)
		pthread_mutex_lock(&(data->fork[0]));
	else
		pthread_mutex_lock(&(data->fork[philo_id]));
	usleep(data->time_to_eat);



	printf("time[%li]/> Hello! I am a thread :D [%i]\n", timer(), philo_id);
	pthread_mutex_unlock(&(data->fork[philo_id - 1]));
	if (philo_id == data->num_of_philo)
		pthread_mutex_unlock(&(data->fork[0]));
	else
		pthread_mutex_unlock(&(data->fork[philo_id]));

	free(content);
	return (NULL);
}

int	create_and_join_threads(t_data *data)
{
	t_content	*content;
	int			i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		content = content_handler(data, i + 1);
		if (pthread_create(&(data->thread[i]), NULL,
			&routine, (void *)content) != 0)
		{
			printf("OUT_OF_MEMMORY");
			return(0);
		}
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return(0);
	}
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
	static suseconds_t	passed_time = 0;
	struct timeval 		time;

	gettimeofday(&time, NULL);
	if (!passed_time)
		passed_time = time.tv_usec;
	return (time.tv_usec - passed_time);
}
