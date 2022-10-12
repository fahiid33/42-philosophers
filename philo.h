/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:53:31 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/12 04:03:17 by fstitou          ###   ########.fr       */
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
# include <stdatomic.h>

typedef struct s_info
{
    int	nb_philo;
    unsigned int	time_to_die;
    unsigned int	time_to_eat;
    unsigned int	time_to_sleep;
    int	nb_must_eat;
	unsigned int  	start_time;
	pthread_mutex_t	print;
    pthread_mutex_t	is_eating;
    pthread_mutex_t dead_flag;
    pthread_mutex_t finish_flag;
}   t_info;

typedef struct s_philo
{
    int					id;
    int			nb_eat;
   	int 			last_eat;
    atomic_int             dead;
    atomic_int             finished;
    pthread_t				th;
    pthread_mutex_t	left_fork;
    pthread_mutex_t	*right_fork;
    t_info *info;
}   t_philo;

//init

int	check_args(int ac, char **av, t_info *info);
t_philo	*init_philos(t_info *info);



#endif