/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:19:09 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 17:10:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_char(char *av[])
{
	int	i;
	int	k;

	i = 0;
	while (av[++i])
	{
		k = -1;
		while (av[i] && av[i][++k])
		{
			if ((av[i][k] >= 'a' && av[i][k] <= 'z' ) ||
				(av[i][k] >= 'A' && av[i][k] <= 'Z' ))
				return (true);
		}
	}
	return (false);
}

bool	parsing(int ac, char *av[], t_parse *data)
{
	int	overflow;

	overflow = 0;
	data->philo_no = ft_atoi_overflow(av[1], &overflow);
	data->life = ft_atoi_overflow(av[2], &overflow);
	data->meal = ft_atoi_overflow(av[3], &overflow);
	data->sleep = ft_atoi_overflow(av[4], &overflow);
	data->meal_max = -1;
	if (data->philo_no <= 0 || data->life <= 0 || data->meal <= 0
		|| data->sleep <= 0 || overflow || is_char(av))
	{
		printf("Error: Invalid parsing\n");
		return (false);
	}
	if (ac == 6)
	{
		data->meal_max = ft_atoi_overflow(av[5], &overflow);
		if (data->meal_max <= 0 || overflow)
		{
			printf("Error: Invalid parsing\n");
			return (false);
		}
	}
	return (true);
}

bool	create_philosophers(t_philo **philo, t_parse data)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data.philo_no);
	if (!(*philo))
		return (false);
	i = -1;
	while (++i < data.philo_no)
		memset(&philo[0][i], 0, sizeof(philo[0][i]));
	i = -1;
	while (++i < data.philo_no)
	{
		philo[0][i].data = data;
		philo[0][i].meal_current = 0;
		philo[0][i].meal_max = data.meal_max;
		philo[0][i].id = i + 1;
	}
	return (true);
}

void	place_forks(t_sync *sync, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data.philo_no)
		philo[i].sync = sync;
}

bool	sync_init(t_parse data, t_sync *sync)
{
	int	i;

	sync->forks = malloc(sizeof(pthread_mutex_t) * data.philo_no);
	if (!(sync->forks))
		return (false);
	sync->forks_status = malloc(sizeof(int) * data.philo_no);
	if (!(sync->forks_status))
	{
		free(sync->forks);
		return (false);
	}
	i = -1;
	while (++i < data.philo_no)
		sync->forks_status[i] = OFF;
	i = -1;
	while (++i < data.philo_no)
		pthread_mutex_init(&sync->forks[i], NULL);
	i = -1;
	while (++i < 8)
		pthread_mutex_init(&sync->data_ownership[i], NULL);
	sync->dead = false;
	sync->is_all_full = false;
	return (true);
}
