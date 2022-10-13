
#include "philo_bonus.h"

void	ft_error(int err)
{
	if (err == 1)
	{
		write(1, "arguments error\n", 17);
		exit(1);
	}
	if (err == 2)
	{
		write(1, "invalid number of arguments", 28);
		exit(1);
	}
	if (err == 3)
	{
		write(1, "cannot create a thread :(", 26);
		exit(1);
	}
}

unsigned int	get_time(void)
{
	struct timeval	tv;
	unsigned int time;
	
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time / 1000);
}

void	dormir(unsigned int time)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	print_status(t_philo *philo, int id, char *state)
{
	sem_wait(&philo->info->print);
	printf("%u %d %s\n", get_time() - philo->info->start_time, id, state);
	if (state[0] != 'd')
		sem_post(&philo->info->print);
}

void	eat_times(t_philo *philo)
{
	sem_wait(&(philo->info->is_eating));
	philo->last_eat = get_time();
	philo->nb_eat++;
	sem_post(&(philo->info->is_eating));
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->forks);
		print_status(philo, philo->id, "has taken fork");
		sem_wait(philo->forks);
		print_status(philo, philo->id, "has taken fork");
		print_status(philo, philo->id, "is eating");
		eat_times(philo);
        if (philo->nb_eat == philo->info->nb_must_eat)
            break ;
		dormir(philo->info->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		print_status(philo, philo->id, "is sleeping");
		dormir(philo->info->time_to_sleep);
		print_status(philo, philo->id, "is thinking");
	}
	return (NULL);
}

void    *check_death(void *philstruct)
{
    t_philo	*philo;

    philo = (t_philo *)philstruct;
    while (1)
    {
        sem_wait(&(philo->info->is_eating));
        if (get_time() - philo->last_eat > philo->info->time_to_die)
        {
            print_status(philo, philo->id, "died");
            sem_post(&(philo->info->is_eating));
            exit(1);
        }
        sem_post(&(philo->info->is_eating));
        dormir(1);
    }
    return (NULL);
}

void	start(t_info *info)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = init_philos(info);
	philo->info->start_time = get_time();
	while (i < info->nb_philo)
	{
        
        philo[i].pid = fork();
        if (philo[i].pid == 0)
        {
            // printf("kmdksck\n");
		    if (pthread_create(&philo[i].th, NULL, &check_death, &philo[i]) != 0)
			    ft_error(3);
		    routine(&philo[i]);
            // exit(1);
        }
        i++;
		usleep(40);
	}
	return ;
}


int main(int ac, char **av)
{
    t_info	*info; 

	info = NULL;
	if (ac == 5 || ac == 6)
	{
		info = malloc(sizeof(t_info));
		if (!check_args(ac, av, info))
		{
			free(info);
			ft_error(1);
		}
		else
			start(info);
	}
	else
		ft_error(2);
}