/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:47:35 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:54:35 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_all(t_data **data)
{
	free((*data)->philo);
	free(*data);
}

void	kill_all(t_data **data)
{
	int	i;

	i = -1;
	while (++i < (*data)->n_philo)
	{
		kill((*data)->philo[i].pid, SIGQUIT);
	}
}

static void	handler(t_philo *tmp)
{
	sem_wait(tmp->data->msg);
	printf("%lu %d died\n", get_normal_time(tmp->data->t_start),
		tmp->id + 1);
	sem_post(tmp->data->sem);
	sem_post(tmp->data->meal);
	exit(EXIT_FAILURE);
}

void	*monitoring(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		usleep(50);
		sem_wait(tmp->data->sem);
		sem_wait(tmp->data->meal);
		if (get_normal_time(tmp->data->t_start) - tmp->last_meal
			>= (unsigned long)tmp->data->t_death)
			handler(tmp);
		if (tmp->data->n_meals > 0 && tmp->ate_meals == tmp->data->n_meals)
		{
			sem_post(tmp->data->sem);
			sem_post(tmp->data->meal);
			exit(EXIT_SUCCESS);
		}
		sem_post(tmp->data->sem);
		sem_post(tmp->data->meal);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;
	pid_t	p;

	if (!argv_checker(argc, argv))
		return (-1);
	data = create_data(argc, argv);
	if (data == NULL)
		return (-1);
	if (!initialize_data(&data))
		return (-1);
	i = -1;
	while (++i < data->n_philo)
	{
		waitpid(-1, &p, EXIT_SUCCESS);
		if (p != 0)
			break ;
	}
	kill_all(&data);
	free_all(&data);
}
