/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:34:00 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 17:14:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data.philo_no % 2 == ODD && philo->data.philo_no != 1)
		if (philo->data.life - (philo->data.meal * 2) <= philo->data.meal + 10)
			if (philo->id == 1)
				usleep(philo->data.meal * 1000 * 3);
	if (philo->id % 2 == EVEN)
		usleep(philo->data.meal * 300);
	if (philo->data.philo_no == 1)
	{
		take_forks(philo);
		putdown_forks(philo);
		return (NULL);
	}
	while (1)
	{
		if (should_stop(philo))
			return (NULL);
		eat(philo);
		thread_status(philo, SLEEPING, "is sleeping");
		thread_status(philo, THINKING, "is thinking");
	}
	return (NULL);
}

void	id_forks(t_philo **philo, t_parse data)
{
	long long	start_time;
	int			i;

	start_time = get_miliseconds();
	i = -1;
	while (++i < data.philo_no)
	{
		philo[0][i].time.start_time = start_time;
		philo[0][i].time.update_time = start_time;
		if (philo[0][i].id == 1)
		{
			philo[0][i].fork[LEFT] = philo[0][i].data.philo_no - 1;
			if (philo[0]->data.philo_no != 1)
				philo[0][i].fork[RIGHT] = philo[0][i].id - 1;
		}
		else
		{
			philo[0][i].fork[LEFT] = philo[0][i].id - 2;
			philo[0][i].fork[RIGHT] = philo[0][i].id - 1;
		}
	}
}

void	solve(t_philo *philo, t_parse data, t_sync sync)
{
	int	i;

	i = -1;
	id_forks(&philo, data);
	while (++i < data.philo_no)
	{
		pthread_create(&philo[i].thread, NULL, thread_routine, \
		(void *)&philo[i]);
	}
	monitor(philo);
	i = -1;
	while (++i < data.philo_no)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < 8)
		pthread_mutex_destroy(&sync.data_ownership[i]);
	i = -1;
	while (++i < data.philo_no)
		pthread_mutex_destroy(&sync.forks[i]);
	free(sync.forks);
	free(sync.forks_status);
	sync.forks = NULL;
	sync.forks_status = NULL;
	free(philo);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;
	t_parse	data;
	t_sync	sync;

	if (ac < 5 || ac > 6)
		return (1);
	memset((void *)&philo, 0, sizeof(philo));
	memset((void *)&data, 0, sizeof(data));
	memset((void *)&sync, 0, sizeof(sync));
	if (!parsing(ac, av, &data))
		return (1);
	if (!create_philosophers(&philo, data))
		return (1);
	if (!sync_init(data, &sync))
	{
		free(philo);
		return (1);
	}
	place_forks(&sync, philo);
	solve(philo, data, sync);
	return (0);
}
