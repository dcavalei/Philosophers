/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:59:26 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/26 15:42:47 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simple_debugs.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!((argc == 5 || argc == 6) && validate_user_input(argv)))
		return (error_handler(INVALID_INPUT, NULL));
	if (ft_atoi(argv[1]) > HARD_CAP)
		return (error_handler(TOO_MANY_THREADS, NULL));
	init_data(&data);
	if(!(data_setup(&data, argc, argv) && create_and_join_threads(&data)))
		return (error_handler(errno, &data));
	i = -1;
	while (++i < data.num_of_philo)
		pthread_mutex_destroy(&(data.fork[i]));
	pthread_mutex_destroy(&(data.dead_mutex));
	free(data.thread);
	free(data.fork);
	free(data.lock);
	//check_leaks();
	return(0);
}

int	create_and_join_threads(t_data *data)
{
	t_content	*content;
	int			i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		content = content_handler(data, i);
		if (pthread_create(&(data->thread[i]), NULL, &routine, (void *)content) != 0)
		{
			printf("OUT_OF_MEMMORY");
			return(0);
		}
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
		{
			printf("JOIN_ERROR");
			return(0);
		}
	}
	return (1);
}


