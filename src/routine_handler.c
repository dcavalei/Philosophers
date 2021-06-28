/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:27:41 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/28 20:46:52 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_remaining_actions(int index, char *message);

void	*routine(void *content)
{
	t_data		*data;
	int			index;
	int			times_to_eat;

	data = ((t_content *)content)->data;
	index = ((t_content *)content)->philo_id;
	times_to_eat = data->num_of_eat;
	while (times_to_eat--)
	{
		if (!wait_for_fork(content, data, index))
			break ;
		if (!start_eating(content, data, index))
			break ;
		if (!unlock_forks(content, data, index))
			break ;
		if (!start_sleeping(content, data, index))
			break ;
		output_action(data, index, THINKING);
	}
	output_action(data, index, SATISFIED);
	free(content);
	return (NULL);
}

int	start_eating(void *content, t_data *data, int index)
{
	long		time_start;

	time_start = timer();
	((t_content *)content)->last_meal = timer();
	printf("TIMMERMEMRMRMERMEMR %li\n", ((t_content *)content)->last_meal);
	output_action(data, index, EATING);
	while (timer() - time_start < data->time_to_eat)
	{
		// if (is_dead(content))
			// return (death_handler(data, index));
		if (data->someone_died)
			return (0);
		usleep(1);
	}
	// printf("[%li] Philo %i LAST MEAL-> %li\n", timer(), ((t_content *)content)->philo_id + 1, time_start);
	// ((t_content *)content)->last_meal = timer();

	return (1);
}

int	start_sleeping(void *content, t_data *data, int index)
{
	long	time_start;

	time_start = timer();
	output_action(data, index, SLEEPING);
	while (timer() - time_start < data->time_to_sleep)
	{
		if (data->someone_died || is_dead(content))
			return (death_handler(data, index + 1));
		usleep(1);
	}
	return (1);
}

void	output_action(t_data *data, int index, char *message)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->someone_died)
	{
		if (!ft_strncmp(message, FORK_TAKEN, 20))
		{
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i "NC, timer(), index + 1);
			printf("has taken a "YEL"fork"NC".\n");
		}
		else if (!ft_strncmp(message, SLEEPING, 20))
		{
			printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i "NC, timer(), index + 1);
			printf("is "YEL"sleeping"NC"!\n");
		}
		else
			output_remaining_actions(index, message);
	}
	pthread_mutex_unlock(&data->dead_mutex);
}

void	output_remaining_actions(int index, char *message)
{
	if (!ft_strncmp(message, THINKING, 20))
	{
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i "NC, timer(), index + 1);
		printf("is "YEL"thinking"NC"!\n");
	}
	else if (!ft_strncmp(message, EATING, 20))
	{
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i "NC, timer(), index + 1);
		printf("is "YEL"eating"NC"!\n");
	}
	else if (!ft_strncmp(message, SATISFIED, 20))
	{
		printf(CYN"[%.4li]\t"NC"Philosopher "GRN"%i "NC, timer(), index + 1);
		printf("is "GRN"satisfied"NC"!\n");
	}
}
