/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 02:34:07 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/15 03:02:35 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_times(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->is_eating));
	philo->last_eat = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&(philo->info->is_eating));
}

int	is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_lock(&(philo->info->is_eating));
		if (philo[i].last_eat != 0
			&& get_time() - philo[i].last_eat >= philo->info->time_to_die)
		{
			print_status(philo, philo[i].id, "died");
			philo->dead = 1;
			return (1);
		}
		i++;
		pthread_mutex_unlock(&(philo->info->is_eating));
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (philo->info->nb_must_eat != -1 && i < philo->info->nb_must_eat)
	{
		pthread_mutex_lock(&(philo->info->is_eating));
		if (philo[i].nb_eat >= philo->info->nb_must_eat)
		{
			philo->finished = 1;
			count++;
		}
		if (count == philo->info->nb_philo)
			return (1);
		i++;
		pthread_mutex_unlock(&(philo->info->is_eating));
	}
	return (0);
}

void	*routine(void *philstruct)
{
	t_philo	*philo;

	philo = (t_philo *)philstruct;
	while (!philo->dead && !philo->finished)
	{
		pthread_mutex_lock(&(philo->left_fork));
		print_status(philo, philo->id, "has taken fork");
		pthread_mutex_lock((philo->right_fork));
		print_status(philo, philo->id, "has taken fork");
		print_status(philo, philo->id, "is eating");
		eat_times(philo);
		dormir(philo->info->time_to_eat);
		pthread_mutex_unlock(&(philo->left_fork));
		pthread_mutex_unlock((philo->right_fork));
		print_status(philo, philo->id, "is sleeping");
		dormir(philo->info->time_to_sleep);
		print_status(philo, philo->id, "is thinking");
	}
	return (NULL);
}
