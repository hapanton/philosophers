/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:05:36 by qsergean          #+#    #+#             */
/*   Updated: 2022/06/30 20:16:58 by qsergean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static const char	*ft_isspace(const char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r')
		{
			str++;
			continue ;
		}
		break ;
	}
	return (str);
}

static long long	ft_isnum(const char *str, long long new)
{
	while (*str)
	{
		if ((*str >= '0') && (*str <= '9'))
		{
			new *= 10;
			new += *str - '0';
			str++;
		}
		else
			break ;
	}
	return (new);
}

long long	ft_ll_atoi(const char *str)
{
	long long	neg;
	long long	new;

	neg = 0;
	new = 0;
	str = ft_isspace(str);
	if (*str == '-')
	{
		neg++;
		str++;
	}
	else if (*str == '+')
		str++;
	new = ft_isnum(str, new);
	if (neg % 2 == 1)
		new = -new;
	return (new);
}
