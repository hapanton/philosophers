/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifestyle_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:32:47 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:54:31 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	clean_exit(t_data **data, int errcode)
{
	sem_close((*data)->msg);
	sem_close((*data)->forks);
	sem_close((*data)->sem);
	free((*data)->philo);
	free(*data);
	exit(errcode);
}

static void	philo_eat(t_philo **philo)
{
	sem_wait((*philo)->data->forks);
	print_message("has taken a fork", philo);
	sem_wait((*philo)->data->forks);
	print_message("has taken a fork", philo);
	print_message("is eating", philo);
	sem_wait((*philo)->data->sem);
	sem_wait((*philo)->data->meal);
	(*philo)->last_meal = get_normal_time((*philo)->data->t_start);
	sem_post((*philo)->data->meal);
	sem_post((*philo)->data->sem);
	ft_usleep((*philo)->data->t_eat, (*philo)->data->t_start);
	sem_post((*philo)->data->forks);
	sem_post((*philo)->data->forks);
	sem_wait((*philo)->data->sem);
	(*philo)->ate_meals += 1;
	sem_post((*philo)->data->sem);
}

void	philo_life(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	if (tmp->id == 0)
		usleep(500);
	while (tmp->ate_meals < tmp->data->n_meals
		|| tmp->data->n_meals == -1)
	{
		philo_eat(&tmp);
		print_message("is sleeping", &tmp);
		ft_usleep(tmp->data->t_sleep, tmp->data->t_start);
		print_message("is thinking", &tmp);
	}
}
