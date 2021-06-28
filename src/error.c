/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:07:58 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/28 18:24:53 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(int error, t_data *data)
{
	output_error(error);
	free_data(data);
	return (1);
}

void	output_error(int error)
{
	write(2, "Error\n", 6);
	if (error == INVALID_INPUT)
		write(2, "Invalid input!\n", 15);
	else if (error == TOO_MANY_THREADS)
		write(2, "Too many threads!\n", 18);
	else if (error == errno)
	{
		write(2, "errno code: ", 12);
		ft_putnbr_fd(errno, 2);
		write(2, "\n", 1);
	}
	else if (error == THREAD_CREATE_ERROR)
		write(2, "pthread_create error!\n", 22);
	else if (error == THREAD_JOIN_ERROR)
		write(2, "pthread_join error!\n", 20);
	else
		write(2, "Unknown!\n", 9);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->thread)
		free(data->thread);
	if (data->fork)
		free(data->fork);
	if (data->lock)
		free(data->lock);
}
