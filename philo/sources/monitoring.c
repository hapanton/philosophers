/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:44:50 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:43:39 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	all_finished_eating(t_data **data)
{
	int	i;

	i = -1;
	while (++i < (*data)->n_philo)
	{
		pthread_mutex_lock(&(*data)->ate);
		if ((*data)->philo[i].ate_meals < (*data)->n_meals)
		{
			pthread_mutex_unlock(&(*data)->ate);
			return (0);
		}
		pthread_mutex_unlock(&(*data)->ate);
	}
	return (1);
}

static void	lock_them(t_data **data)
{
	pthread_mutex_lock(&(*data)->death);
	pthread_mutex_lock(&(*data)->new);
	pthread_mutex_lock(&(*data)->meal);
}

static void	unlock_them(t_data **data)
{
	pthread_mutex_unlock(&(*data)->meal);
	pthread_mutex_unlock(&(*data)->new);
	pthread_mutex_unlock(&(*data)->death);
}

static void	unlock_and_lock(t_data **data)
{
	pthread_mutex_unlock(&((*data)->death));
	pthread_mutex_unlock(&(*data)->meal);
	pthread_mutex_lock(&(*data)->msg);
}

int	monitoring(t_data **data)
{
	int	i;

	i = 0;
	while (1)
	{
		lock_them(data);
		if (get_normal_time((*data)->t_start) - (*data)->philo[i].last_meal
			>= (unsigned long)(*data)->t_death)
		{
			(*data)->n_died = (*data)->philo[i].id + 1;
			unlock_and_lock(data);
			return (1);
		}
		unlock_them(data);
		if ((*data)->n_meals > 0 && all_finished_eating(data))
		{
			pthread_mutex_lock(&(*data)->msg);
			return (2);
		}
		i++;
		if (i == (*data)->n_philo)
			i = 0;
	}
	return (1);
}
