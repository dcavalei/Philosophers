/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:30:02 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/25 23:35:06 by dcavalei         ###   ########.fr       */
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
# include "ft_colors.h"

# define INVALID_INPUT -1
# define TOO_MANY_THREADS -2
# define HARD_CAP 4096

typedef struct s_data
{
	pthread_mutex_t		dead_mutex;
	int				someone_died;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	int				*lock;

}				t_data;

typedef struct s_content
{
	t_data	*data;
	int		philo_id;
	long	last_meal;
}				t_content;

void		init_data(t_data *data);
t_content	*content_handler(t_data *data, int index);
long	timer(void);
void	free_data(t_data *data);
int			error_handler(int error, t_data *data);
int			validate_user_input(char **argv);

int	is_dead(void *content);

int	wait_for_fork(void *content, t_data *data, int index);
int	death_handler(t_data *data, int philo_index);

int			ft_isnbr(char *number);
int			ft_atoi(const char *str);
void		ft_putnbr_fd(int n, int fd);
int			data_setup(t_data *data, int argc, char **argv);
void		*routine(void *content);
int			create_and_join_threads(t_data *data);

/*
**	OK
*/

#endif
