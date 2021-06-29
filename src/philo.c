/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:59:26 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/29 11:50:14 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create(t_data *data);
static int	join(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!((argc == 5 || argc == 6) && validate_user_input(argv)))
		return (error_handler(INVALID_INPUT, NULL));
	if (ft_atoi(argv[1]) > HARD_CAP)
		return (error_handler(TOO_MANY_THREADS, NULL));
	init_data(&data);
	if (!(data_setup(&data, argc, argv) && create_and_join_threads(&data)))
		return (error_handler(errno, &data));
	i = -1;
	while (++i < data.num_of_philo)
		pthread_mutex_destroy(&(data.fork[i]));
	pthread_mutex_destroy(&(data.dead_mutex));
	free_data(&data);
	return (0);
}

int	create_and_join_threads(t_data *data)
{
	int			ret;

	ret = create(data);
	ret = join(data);
	return (ret);
}

static int	create(t_data *data)
{
	t_content	*content;
	int			i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		content = content_handler(data, i);
		if (!content)
			return (0);
		if (pthread_create(&(data->thread[i]), NULL,
				&routine, (void *)content) != 0)
		{
			output_error(THREAD_CREATE_ERROR);
			return (0);
		}
		usleep(100);
	}
	return (1);
}

static int	join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
		{
			output_error(THREAD_JOIN_ERROR);
			return (0);
		}
	}
	return (1);
}
