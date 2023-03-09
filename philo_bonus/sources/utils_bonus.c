/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 00:21:02 by qsergean          #+#    #+#             */
/*   Updated: 2022/07/03 23:31:50 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

unsigned long	get_normal_time(struct timeval since)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (since.tv_sec * 1000 + since.tv_usec / 1000));
}

void	ft_usleep(unsigned long delay, struct timeval since)
{
	unsigned long	start;
	unsigned long	now;

	start = get_normal_time(since);
	now = start;
	while (now - start < delay)
	{
		usleep(100);
		now = get_normal_time(since);
	}
}

void	print_message(char *str, t_philo **philo)
{
	sem_wait((*philo)->data->msg);
	printf("%lu %d ", get_normal_time((*philo)->data->t_start),
		(*philo)->id + 1);
	printf("%s\n", str);
	sem_post((*philo)->data->msg);
}

static int	nums_checker(int argc, char **argv)
{
	int			i;
	long long	tmp;

	(void) argc;
	i = 1;
	while (argv[i])
	{
		tmp = ft_ll_atoi(argv[i]);
		if (tmp <= 0 || tmp > INT_MAX)
		{
			printf("All values have to be \
positive and must not exceed int range\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	argv_checker(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("\n*** Error: must be 4 or 5 parameters ***\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("\n*** Error: only digits are allowed ***\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (nums_checker(argc, argv));
}
