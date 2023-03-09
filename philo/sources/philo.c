/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:21:39 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:43:34 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	destroyer(t_data **data, int i)
{
	pthread_mutex_unlock(&(*data)->msg);
	pthread_mutex_destroy(&(*data)->msg);
	pthread_mutex_unlock(&(*data)->death);
	pthread_mutex_destroy(&(*data)->death);
	while (i-- > 0)
	{
		pthread_mutex_unlock(&(*data)->forks[i]);
		pthread_mutex_destroy(&(*data)->forks[i]);
	}
	return (free_heap(data));
}

void	death_handler(t_data **data)
{
	pthread_mutex_lock(&((*data)->death));
	if ((*data)->n_died != 0)
	{
		printf("%lu %d died\n", get_normal_time((*data)->t_start),
			(*data)->n_died);
	}
	pthread_mutex_unlock(&((*data)->death));
}

void	free_all(t_data **data)
{
	int	i;

	pthread_mutex_unlock(&(*data)->death);
	pthread_mutex_destroy(&(*data)->death);
	pthread_mutex_unlock(&(*data)->msg);
	pthread_mutex_destroy(&(*data)->msg);
	i = -1;
	while (++i < (*data)->n_philo)
	{
		pthread_mutex_unlock(&(*data)->forks[i]);
		pthread_mutex_destroy(&(*data)->forks[i]);
	}
	free((*data)->forks);
	free((*data)->philo);
	free(*data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!argv_checker(argc, argv))
		return (-1);
	data = create_data(argc, argv);
	if (data == NULL)
		return (-1);
	if (!initialize_data(&data))
		return (-1);
	if (monitoring(&data) == 1)
	{
		death_handler(&data);
		free_all(&data);
	}
	else
		free_all(&data);
}
