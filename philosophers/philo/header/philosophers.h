/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:56:15 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 17:13:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define LEFT 0
# define RIGHT 1
# define ON 1
# define OFF 0

# define ODD 1
# define EVEN 0

typedef struct s_time {
	long long	start_time;
	long long	update_time;
}	t_time;

typedef struct s_sync {
	pthread_mutex_t	*forks;
	int				*forks_status;
	pthread_mutex_t	data_ownership[8];
	bool			dead;
	bool			is_all_full;
}	t_sync;

typedef struct s_parse {
	int				philo_no;
	long long		life;
	int				meal;
	int				sleep;
	int				meal_max;
}	t_parse;

typedef struct s_philo {
	pthread_t	thread;
	t_parse		data;
	t_sync		*sync;
	t_time		time;
	int			id;
	int			meal_current;
	int			meal_max;
	int			fork[2];
	bool		is_full;
	int			starvation;
}	t_philo;

enum e_status {
	TAKE_FORK=0,
	EATING,
	SLEEPING,
	THINKING,
};

enum e_ownership {
	DEAD=0,
	PRINT,
	LIFE,
	MEAL_CURRENT,
	MEAL_MAX,
	IS_FULL,
	FULL_CNT,
	IS_ALL_FULL,
};

/* main.c */
int			main(int ac, char *av[]);
void		solve(t_philo *philo, t_parse data, t_sync sync);
void		id_forks(t_philo **philo, t_parse data);
void		*thread_routine(void *arg);

/* parsing.c */
bool		sync_init(t_parse data, t_sync *sync);
void		place_forks(t_sync *sync, t_philo *philo);
bool		create_philosophers(t_philo **philo, t_parse data);
bool		parsing(int ac, char *av[], t_parse *data);

/* thread_monitor.c */
bool		full_mark(t_philo *philo);
bool		no_death(t_philo *philo);
void		monitor(t_philo *philo);

/* thread_status.c */
bool		should_stop(t_philo *philo);
void		thread_status(t_philo *philo, int status, char *msg);
void		take_forks(t_philo *philo);
void		putdown_forks(t_philo *philo);
void		eat(t_philo *philo);

/* utils.c */
long long	get_microseconds(void);
long long	get_miliseconds(void);
void		scheduling(long long task, long long start_time);
bool		block_printf(t_philo *philo);
int			ft_atoi_overflow(const char *nptr, int *overflow);

#endif