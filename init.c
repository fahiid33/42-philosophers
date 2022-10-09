/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:55:59 by fahd              #+#    #+#             */
/*   Updated: 2022/10/09 02:07:52 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (info->nb_philo < 2 || info->nb_philo > 200 || info->time_to_die < 60
			|| info->time_to_eat < 60 || info->time_to_sleep < 60
			|| info->nb_must_eat < -1)
			return (0);
		return (1);
	}
	return (0);
}

t_philo	*init_philos(t_info *info)
{
	t_philo	*philo;
	int		i;
	philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = info;
		philo[i].last_eat = 0;
		philo[i].nb_eat = 0;
		philo[i].is_eating = 0;
		pthread_mutex_init(&philo[i].left_fork, NULL);
		if (i == info->nb_philo - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
		i++;
	}
	return (philo);
}