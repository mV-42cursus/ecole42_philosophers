/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:27:51 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 17:12:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->sync->data_ownership[IS_ALL_FULL]);
	pthread_mutex_lock(&philo->sync->data_ownership[DEAD]);
	if (philo->sync->dead || philo->sync->is_all_full)
	{
		pthread_mutex_unlock(&philo->sync->data_ownership[DEAD]);
		pthread_mutex_unlock(&philo->sync->data_ownership[IS_ALL_FULL]);
		return (true);
	}
	pthread_mutex_unlock(&philo->sync->data_ownership[DEAD]);
	pthread_mutex_unlock(&philo->sync->data_ownership[IS_ALL_FULL]);
	return (false);
}

void	thread_status(t_philo *philo, int status, char *msg)
{
	long long	current_time;

	if (block_printf(philo))
		return ;
	current_time = get_miliseconds();
	printf("%lld %d %s\n", current_time - philo->time.start_time, \
	philo->id, msg);
	pthread_mutex_unlock(&philo->sync->data_ownership[PRINT]);
	if (status == EATING)
	{
		pthread_mutex_lock(&philo->sync->data_ownership[LIFE]);
		philo->time.update_time = current_time;
		pthread_mutex_unlock(&philo->sync->data_ownership[LIFE]);
		scheduling(philo->data.meal, current_time);
	}
	if (philo->data.meal_max != -1 && status == EATING)
	{
		pthread_mutex_lock(&philo->sync->data_ownership[MEAL_CURRENT]);
		philo->meal_current += 1;
		pthread_mutex_unlock(&philo->sync->data_ownership[MEAL_CURRENT]);
	}
	if (status == SLEEPING)
		scheduling(philo->data.sleep, current_time);
}

void	take_forks(t_philo *philo)
{
	if (philo->data.philo_no == 1)
	{
		pthread_mutex_lock(&philo->sync->forks[philo->fork[LEFT]]);
		philo->sync->forks_status[philo->fork[LEFT]] = ON;
		thread_status(philo, TAKE_FORK, "has taken a fork");
		return ;
	}
	pthread_mutex_lock(&philo->sync->forks[philo->fork[LEFT]]);
	philo->sync->forks_status[philo->fork[LEFT]] = ON;
	thread_status(philo, TAKE_FORK, "has taken a fork");
	pthread_mutex_lock(&philo->sync->forks[philo->fork[RIGHT]]);
	philo->sync->forks_status[philo->fork[RIGHT]] = ON;
	thread_status(philo, TAKE_FORK, "has taken a fork");
	thread_status(philo, EATING, "\033[0;36mis eating\033[0;37m");
}

void	putdown_forks(t_philo *philo)
{
	if (philo->data.philo_no == 1)
	{
		usleep(philo->data.life * 1000 + 5 * 1000);
		philo->sync->forks_status[philo->fork[LEFT]] = OFF;
		pthread_mutex_unlock(&philo->sync->forks[philo->fork[LEFT]]);
		return ;
	}
	philo->sync->forks_status[philo->fork[RIGHT]] = OFF;
	pthread_mutex_unlock(&philo->sync->forks[philo->fork[RIGHT]]);
	philo->sync->forks_status[philo->fork[LEFT]] = OFF;
	pthread_mutex_unlock(&philo->sync->forks[philo->fork[LEFT]]);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	putdown_forks(philo);
}
