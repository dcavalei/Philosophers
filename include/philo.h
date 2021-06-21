/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:30:02 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/21 18:16:44 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# define INVALID_INPUT_ERROR -1
# define THREAD_CREATE_ERROR -2
# define THREAD_JOIN_ERROR -3

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
}				t_data;



int	error_handler(int error, t_data *data);
int	validate_user_input(char **argv);

int	ft_isnbr(char *number);
int	ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
int	init_data(t_data *data, int argc, char **argv);
void	*routine(void *content);
int	create_and_join_threads(t_data *data);
/*
**	OK
*/

#endif
