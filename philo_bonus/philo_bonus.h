#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdatomic.h>
# include <semaphore.h>

typedef struct s_info
{
    int	nb_philo;
    unsigned int	time_to_die;
    unsigned int	time_to_eat;
    unsigned int	time_to_sleep;
    int	nb_must_eat;
	unsigned int  	start_time;
	sem_t   print;
    sem_t	is_eating;
    pthread_mutex_t dead_flag;
    pthread_mutex_t finish_flag;
}   t_info;

typedef struct s_philo
{
    int					id;
    pid_t				pid;
    int			nb_eat;
   	int 			last_eat;
    atomic_int             dead;
    atomic_int             finished;
    pthread_t				th;
    sem_t	*forks;
    t_info *info;
}   t_philo;

//init

int	check_args(int ac, char **av, t_info *info);
t_philo	*init_philos(t_info *info);



#endif