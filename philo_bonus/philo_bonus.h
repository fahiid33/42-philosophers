/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:59:43 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/15 03:57:09 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdatomic.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_info
{
	int				nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_must_eat;
	unsigned int	start_time;
	sem_t			*print;
	sem_t			*is_eating;
	sem_t			*forks;
	sem_t			*is_dead;
}	t_info;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			nb_eat;
	atomic_int	last_eat;
	pthread_t	th;
	t_info		*info;
}	t_philo;

//init

int				check_args(int ac, char **av, t_info *info);
t_philo			*init_philos(t_info *info);

// tools

unsigned int	get_time(void);
void			dormir(unsigned int time);
void			print_status(t_philo *philo, int id, char *state);
void			ft_error(int err);

//routine

void			*check_death(void *philstruct);
void			*routine(t_philo *philo);
void			eat_times(t_philo *philo);

#endif
