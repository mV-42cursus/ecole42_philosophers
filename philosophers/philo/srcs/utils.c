/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 00:00:23 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 16:53:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_miliseconds(void)
{
	struct timeval	tv;
	long long		res;

	gettimeofday(&tv, NULL);
	res = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (res);
}

void	scheduling(long long task, long long start_time)
{
	while (1)
	{
		if (get_miliseconds() - start_time >= task)
			break ;
		else
			usleep(250);
	}
}

bool	block_printf(t_philo *philo)
{
	pthread_mutex_lock(&philo->sync->data_ownership[PRINT]);
	pthread_mutex_lock(&philo->sync->data_ownership[IS_ALL_FULL]);
	pthread_mutex_lock(&philo->sync->data_ownership[DEAD]);
	if (philo->sync->dead || philo->sync->is_all_full)
	{
		pthread_mutex_unlock(&philo->sync->data_ownership[PRINT]);
		pthread_mutex_unlock(&philo->sync->data_ownership[IS_ALL_FULL]);
		pthread_mutex_unlock(&philo->sync->data_ownership[DEAD]);
		return (true);
	}
	pthread_mutex_unlock(&philo->sync->data_ownership[DEAD]);
	pthread_mutex_unlock(&philo->sync->data_ownership[IS_ALL_FULL]);
	return (false);
}

int	ft_atoi_overflow(const char *nptr, int *overflow)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = sign * (-1);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = (10 * res) + (*nptr - '0');
		if (res < -2147483648 || res > 2147483647)
		{
			*overflow = 1;
			return (1);
		}
		nptr++;
	}
	return ((sign) * res);
}
