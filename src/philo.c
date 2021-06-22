/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:59:26 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/22 18:54:01 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!((argc == 5 || argc == 6) && validate_user_input(argv)))
		return (error_handler(INVALID_INPUT, NULL));
	if(!(init_data(&data, argc, argv) && create_and_join_threads(&data)))
		return (error_handler(errno, &data));
	i = -1;
	while (++i < data.num_of_philo)
		pthread_mutex_destroy(&(data.fork[i]));
	printf("No more threads AKA all finished :C\n");
	free(data.thread);
	free(data.fork);
	return(0);
}

/*
**	fix errno code 0  
*/

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_of_eat = ft_atoi(argv[5]);
	data->thread = NULL;
	data->fork = NULL;
	if (data->num_of_philo > HARD_CAP)
		return (0);
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
	(void)content;
	sleep(1);
	printf("Hello! I am a thread :D\n");
	return NULL;
}

int	create_and_join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&(data->thread[i]), NULL, &routine, NULL) != 0)
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
