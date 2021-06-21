/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:07:58 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/21 17:30:05 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(int error, t_data *data)
{
	write(2 ,"Error\n", 6);
	if (error == INVALID_INPUT_ERROR)
		write(2, "Invalid input!\n", 15);
	else if (error == THREAD_CREATE_ERROR)
		write(2, "Thread creation error\n", 22);
	else if (error == THREAD_JOIN_ERROR)
		write(2, "Thread join error\n", 18);
	else if (error == errno)
	{
		write(2, "errno code: ", 12);
		ft_putnbr_fd(errno, 2);
		write(2, "\n", 1);
	}
	else
		write(2, "Unknown!\n", 9);
	if (data)
		free(data->thread);
	return (1);
}

int	validate_user_input(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_isnbr(argv[i]) && ft_atoi(argv[i]) > 0)
			return (0);
	}
	return (1);
}