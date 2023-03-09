/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creators.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:50:29 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:47:16 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	fill_data(t_data **data, char **argv)
{
	(*data)->n_philo = ft_atoi(argv[1]);
	(*data)->t_death = ft_atoi(argv[2]);
	(*data)->t_eat = ft_atoi(argv[3]);
	(*data)->t_sleep = ft_atoi(argv[4]);
}

t_data	*create_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	fill_data(&data, argv);
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	else
		data->n_meals = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (data->philo == NULL)
	{
		free(data);
		return (NULL);
	}
	data->forks = (pthread_mutex_t *)malloc(data->n_philo
			* sizeof(pthread_mutex_t));
	if (data->forks == NULL)
	{
		free(data->philo);
		free(data);
		return (NULL);
	}
	return (data);
}

void	fill_philo(t_data **data, int i)
{
	(*data)->philo[i].data = *data;
	(*data)->philo[i].id = i;
	(*data)->philo[i].ate_meals = 0;
	(*data)->philo[i].last_meal = 0;
}

void	mutex_init(t_data **data)
{
	pthread_mutex_lock(&(*data)->death);
	(*data)->n_died = 0;
	pthread_mutex_unlock(&(*data)->death);
	pthread_mutex_init(&(*data)->new, NULL);
	pthread_mutex_init(&(*data)->ate, NULL);
	pthread_mutex_init(&(*data)->meal, NULL);
	gettimeofday(&(*data)->t_start, NULL);
}

int	initialize_data(t_data **data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(*data)->msg, NULL))
		return (free_heap(data));
	if (pthread_mutex_init(&(*data)->death, NULL))
	{
		pthread_mutex_unlock(&(*data)->msg);
		pthread_mutex_destroy(&(*data)->msg);
		return (free_heap(data));
	}
	mutex_init(data);
	while (++i < (*data)->n_philo)
	{
		fill_philo(data, i);
		if (pthread_mutex_init(&(*data)->forks[i], NULL))
			return (destroyer(data, i));
		if (pthread_create(&(*data)->philo[i].th, NULL,
				&philo_life, &(*data)->philo[i]))
			return (destroyer(data, i));
		if (pthread_detach((*data)->philo[i].th))
			return (destroyer(data, i));
	}
	return (1);
}
