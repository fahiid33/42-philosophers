/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:52:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/07/20 01:09:12 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long end_time)
{
	long long	start;	

	start = get_time();
	while (get_time() - start < end_time)
		usleep(end_time - (get_time() - start));
}

void	print_status(t_philo *philo, int id, char *state)
{
	pthread_mutex_lock(&philo->print);
	printf("%lld %d %s\n", get_time() - philo->start_time, id, state);
	if (state[0] == 'd')
		return ;
	pthread_mutex_unlock(&philo->print);
}

void	*routine(void *philstruct)
{
	t_philo	*philo;

	philo = (t_philo *)philstruct;
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_status(philo, philo->id, "has taken a fork");
		print_status(philo, philo->id, "is eating");
		philo->last_eat = get_time();
		// ft_usleep(philo->info->time_to_eat);
		usleep(philo->info->time_to_eat);
		philo->nb_eat++;
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		print_status(philo, philo->id, "is sleeping");
		// ft_usleep(philo->info->time_to_sleep);
		usleep(philo->info->time_to_sleep);
		print_status(philo, philo->id, "is thinking");
	}
	return ((char *)strdup("WAA"));
}

// void	print_philos(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->info->nb_philo)
// 	{
// 		printf("philo %d: %d\n", i, philo[i].id);
// 		i++;
// 	}
// }

void	start(t_info *info)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = init_philos(info);
	pthread_mutex_init(&philo->print, NULL);
	philo->start_time = get_time();
	while (i < info->nb_philo)
	{
		pthread_create(&philo[i].th, NULL, &routine, &philo[i]);
		// pthread_detach(philo[i].th);
		usleep(200);
		i++;
	}
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
			ft_error(1);
			free(info);
		}
		else
			start(info);
	}
	else
		ft_error(2);
}