/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creators_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:48:36 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/07 21:49:18 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

t_data	*create_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->n_philo = ft_atoi(argv[1]);
	data->t_death = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
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
	return (data);
}

static void	fill_parent(t_data **data, int i, int id)
{
	(*data)->philo[i].pid = id;
	(*data)->philo[i].data = *data;
	(*data)->philo[i].id = i;
	(*data)->philo[i].ate_meals = 0;
	(*data)->philo[i].last_meal = 0;
}

static void	fill_child(t_data **data, int i)
{
	(*data)->philo[i].pid = getpid();
	(*data)->philo[i].data = *data;
	(*data)->philo[i].id = i;
	(*data)->philo[i].ate_meals = 0;
	(*data)->philo[i].last_meal = 0;
	if (pthread_create(&(*data)->philo[i].monitor, NULL,
			&monitoring, &(*data)->philo[i]))
		exit(EXIT_FAILURE);
	if (pthread_detach((*data)->philo[i].monitor))
		exit(EXIT_FAILURE);
	philo_life(&(*data)->philo[i]);
	exit(EXIT_SUCCESS);
}

static void	unlinker(void)
{
	sem_unlink("msg");
	sem_unlink("forks");
	sem_unlink("sem");
	sem_unlink("meal");
}

int	initialize_data(t_data **data)
{
	int				i;
	int				id;

	i = -1;
	gettimeofday(&(*data)->t_start, NULL);
	unlinker();
	(*data)->msg = sem_open("msg", O_CREAT | O_EXCL, 0644, 1);
	(*data)->forks = sem_open("forks", O_CREAT | O_EXCL,
			0644, (*data)->n_philo);
	(*data)->sem = sem_open("sem", O_CREAT | O_EXCL, 0644, 1);
	(*data)->meal = sem_open("meal", O_CREAT | O_EXCL, 0644, 1);
	if ((*data)->msg == SEM_FAILED || (*data)->forks == SEM_FAILED
		|| (*data)->sem == SEM_FAILED || (*data)->meal == SEM_FAILED)
		exit(EXIT_FAILURE);
	while (++i < (*data)->n_philo)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		else if (id != 0)
			fill_parent(data, i, id);
		else if (id == 0)
			fill_child(data, i);
	}
	return (1);
}
