/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:53:16 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 19:56:03 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				n_died;
	struct timeval	t_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg;
	pthread_mutex_t	death;
	pthread_mutex_t	new;
	pthread_mutex_t	ate;
	pthread_mutex_t	meal;

	t_philo			*philo;
}					t_data;

typedef struct s_philo
{
	int			id;
	int			ate_meals;
	long long	last_meal;
	pthread_t	th;

	t_data		*data;
}				t_philo;

long long		ft_ll_atoi(const char *str);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);

int				argv_checker(int argc, char **argv);
void			print_message(char *str, t_philo **philo);
void			ft_usleep(unsigned long delay, struct timeval since);
unsigned long	get_normal_time(struct timeval since);

t_data			*create_data(int argc, char **argv);
int				initialize_data(t_data **data);

void			*philo_life(void *philo);
int				monitoring(t_data **data);
int				free_heap(t_data **data);
int				destroyer(t_data **data, int i);

#endif
