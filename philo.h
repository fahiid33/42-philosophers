/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:53:31 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/09 02:18:31 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_info
{
    int	nb_philo;
    int	time_to_die;
    int	time_to_eat;
    int	time_to_sleep;
    int	nb_must_eat;
}   t_info;

typedef struct s_philo
{
    int					id;
    int				nb_eat;
    long long		last_eat;
    int				is_eating;
	long long		start_time;
    int             dead;
    int             finished;
    pthread_t				th;
    pthread_mutex_t	left_fork;
    pthread_mutex_t	*right_fork;
	pthread_mutex_t	print;
    t_info *info;
}   t_philo;

//init

int	check_args(int ac, char **av, t_info *info);
t_philo	*init_philos(t_info *info);



#endif