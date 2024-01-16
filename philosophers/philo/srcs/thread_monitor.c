/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:26:57 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 17:12:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	full_mark(t_philo *philo)
{
	int	i;
	int	ret;

	i = -1;
	ret = 1;
	while (++i < philo->data.philo_no)
	{
		pthread_mutex_lock(&philo->sync->data_ownership[MEAL_CURRENT]);
		pthread_mutex_lock(&philo->sync->data_ownership[IS_FULL]);
		if (philo[i].meal_current >= philo[i].meal_max)
			philo[i].is_full = true;
		pthread_mutex_unlock(&philo->sync->data_ownership[IS_FULL]);
		pthread_mutex_unlock(&philo->sync->data_ownership[MEAL_CURRENT]);
	}
	i = -1;
	while (++i < philo->data.philo_no)
		ret *= philo[i].is_full;
	pthread_mutex_lock(&philo->sync->data_ownership[IS_ALL_FULL]);
	if (ret)
	{
		philo[0].sync->is_all_full = true;
		printf("\033[0;33m******** ENDING SIMULATION ********\n");
	}
	pthread_mutex_unlock(&philo->sync->data_ownership[IS_ALL_FULL]);
	return (ret);
}

bool	no_death(t_philo *philo)
{
	long long	current_time;
	int			i;

	i = -1;
	while (++i < philo->data.philo_no)
	{
		pthread_mutex_lock(&philo->sync->data_ownership[LIFE]);
		current_time = get_miliseconds();
		if (current_time - philo[i].time.update_time > philo->data.life)
		{
			pthread_mutex_unlock(&philo->sync->data_ownership[LIFE]);
			pthread_mutex_lock(&philo->sync->data_ownership[DEAD]);
			philo[i].sync->dead = true;
			printf("\033[0;31m%lld %d died\n", \
			current_time - philo[i].time.start_time, philo[i].id);
			pthread_mutex_unlock(&philo->sync->data_ownership[DEAD]);
			return (false);
		}
		pthread_mutex_unlock(&philo->sync->data_ownership[LIFE]);
	}
	return (true);
}

void	monitor(t_philo *philo)
{
	if (philo->data.philo_no != 1)
		usleep(philo->data.meal * 500);
	while (no_death(philo))
	{
		if (philo->data.meal_max != -1)
			if (full_mark(philo))
				return ;
		usleep(300);
	}
}
