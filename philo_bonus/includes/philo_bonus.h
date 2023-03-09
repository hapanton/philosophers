/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:50:08 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 20:04:52 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <signal.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	struct timeval	t_start;
	sem_t			*forks;
	sem_t			*msg;
	sem_t			*sem;
	sem_t			*meal;

	t_philo			*philo;
}					t_data;

typedef struct s_philo
{
	int			id;
	int			pid;
	int			ate_meals;
	long long	last_meal;
	pthread_t	monitor;

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

void			philo_life(t_philo *philo);
void			*monitoring(void *philo);
void			clean_exit(t_data **data, int errcode);
void			free_all(t_data **data);

#endif