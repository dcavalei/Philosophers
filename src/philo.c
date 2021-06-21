/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:59:26 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/21 17:31:18 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!(argc == 5 || argc == 6) || !validate_user_input(argv))
		return (error_handler(INVALID_INPUT_ERROR, NULL));
	if(!init_data(&data, argc, argv))
		return (error_handler(errno, &data));
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_create(&(data.thread[i]), NULL, &routine, NULL) != 0)
			return(error_handler(THREAD_CREATE_ERROR, &data));
	}
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_join(data.thread[i], NULL) != 0)
			return(error_handler(THREAD_JOIN_ERROR, &data));
	}
	printf("No more threads :C\n");
	free(data.thread);
	return(0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_of_eat = ft_atoi(argv[5]);
	data->thread = malloc(sizeof(pthread_t) * (data->num_of_philo));
	if (!(data->thread))
		return (0);
	return (1);
}

void	*routine(void *content)
{
	(void)content;
	printf("Hello! I am a thread :D\n");
	sleep(2);
	return NULL;
}
