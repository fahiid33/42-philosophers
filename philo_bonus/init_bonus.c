#include "philo_bonus.h"

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0' || strlen(av[i]) > 10)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av, t_info *info)
{
	if (check_arg(av))
	{
		info->nb_philo = atoi(av[1]);
		info->time_to_die = atoi(av[2]);
		info->time_to_eat = atoi(av[3]);
		info->time_to_sleep = atoi(av[4]);
		if (ac == 6)
			info->nb_must_eat = atoi(av[5]);
		else
			info->nb_must_eat = -1;
		if ( info->nb_philo > 200 || info->time_to_die < 60
			|| info->time_to_eat < 60 || info->time_to_sleep < 60
			|| info->nb_must_eat < -1)
			return (0);
		return (1);
	}
	return (0);
}

t_philo *init_philos(t_info *info)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = malloc(sizeof(t_philo) * info->nb_philo);
    if (!philo)
        return (NULL);
    while (i < info->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = info;
		philo[i].last_eat = 0;
		philo[i].nb_eat = 0;
        sem_unlink("forks");
        sem_open("forks", O_CREAT, 0644, info->nb_philo);
        sem_unlink("print");
        sem_open("print", O_CREAT, 0644, 1);
        sem_unlink("eating");
        sem_open("eating", O_CREAT, 0644, 1);
        i++;
    }
    return (philo);
}