/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:52:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/09 04:38:44 by fstitou          ###   ########.fr       */
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
	if (err == 3)
	{
		write(1, "cannot create a thread :(", 26);
		exit(1);
	}
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	dormir(unsigned int end_time)
{
	unsigned int sleep_time;
	
	sleep_time = end_time * 1000;
	usleep(sleep_time);
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
	while (!philo->dead || !philo->finished)
	{
		pthread_mutex_lock(&(philo->left_fork));
		print_status(philo, philo->id, "has taken fork");
		pthread_mutex_lock((philo->right_fork));
		print_status(philo, philo->id, "has taken fork");
		print_status(philo, philo->id, "is eating");
		philo->last_eat = get_time();
		dormir(philo->info->time_to_eat);
		philo->nb_eat++;
		pthread_mutex_unlock(&(philo->left_fork));
		pthread_mutex_unlock((philo->right_fork));
		print_status(philo, philo->id, "is sleeping");
		dormir(philo->info->time_to_sleep);
		print_status(philo, philo->id, "is thinking");
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo)
	{
		if (philo[i].last_eat != 0 && get_time() - philo[i].last_eat >= philo->info->time_to_die)
		{
			print_status(philo, philo[i].id, "died");
			philo->dead = 1;
			return 1;
		}
		i++;
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo && philo->info->nb_must_eat != -1)
	{
		if (philo[i].nb_eat >= philo->info->nb_must_eat)
		{
			philo->finished = 1;
			return (1);
		}
		i++;
	}
	return (0);
}


void	start(t_info *info)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = init_philos(info);
	pthread_mutex_init(&philo->print, NULL);
	philo->dead = 0;
	philo->finished = 0;
	while (i < info->nb_philo)
	{
		philo[i].start_time = get_time();
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) != 0)
			ft_error(3);
		i++;
		usleep(40);
	}
	while (!is_dead(philo) && !check_meals(philo))
		;
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
			ft_error(1);
			free(info);
		}
		else
			start(info);
	}
	else
		ft_error(2);
}