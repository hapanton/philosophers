/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifestyle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:48:25 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:35:27 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_heap(t_data **data)
{
	printf("Error\n");
	free((*data)->forks);
	free((*data)->philo);
	free(*data);
	return (0);
}

static void	philo_eat_one(t_philo **philo, int r)
{
	pthread_mutex_lock(&(*philo)->data->death);
	(*philo)->data->n_died = (*philo)->id + 1;
	pthread_mutex_unlock(&(*philo)->data->death);
	pthread_mutex_lock(&(*philo)->data->forks[r]);
}

static void	philo_eat_two(t_philo **philo, int r, int l)
{
	pthread_mutex_lock(&(*philo)->data->meal);
	(*philo)->last_meal = get_normal_time((*philo)->data->t_start);
	pthread_mutex_unlock(&(*philo)->data->meal);
	print_message("is eating", philo);
	ft_usleep((*philo)->data->t_eat, (*philo)->data->t_start);
	pthread_mutex_unlock(&(*philo)->data->forks[l]);
	pthread_mutex_unlock(&(*philo)->data->forks[r]);
	pthread_mutex_lock(&(*philo)->data->ate);
	(*philo)->ate_meals += 1;
	pthread_mutex_unlock(&(*philo)->data->ate);
}

static void	philo_eat(t_philo **philo)
{
	int			l;
	int			r;

	r = (*philo)->id;
	l = (*philo)->id - 1;
	if ((*philo)->id == 0)
		l = (*philo)->data->n_philo - 1;
	if ((*philo)->id % 2 != 1)
	{
		usleep(500);
		pthread_mutex_lock(&(*philo)->data->forks[l]);
		print_message("has taken a fork", philo);
	}
	pthread_mutex_lock(&(*philo)->data->forks[r]);
	print_message("has taken a fork", philo);
	if ((*philo)->id % 2)
	{
		pthread_mutex_lock(&(*philo)->data->forks[l]);
		print_message("has taken a fork", philo);
	}
	if (l == r)
		philo_eat_one(philo, r);
	philo_eat_two(philo, r, l);
}

void	*philo_life(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (tmp->ate_meals < tmp->data->n_meals
		|| tmp->data->n_meals == -1)
	{
		philo_eat(&tmp);
		print_message("is sleeping", &tmp);
		ft_usleep(tmp->data->t_sleep, tmp->data->t_start);
		print_message("is thinking", &tmp);
	}
	return (0);
}
