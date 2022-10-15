/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 03:18:42 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/15 03:50:01 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_times(t_philo *philo)
{
	sem_wait((philo->info->is_eating));
	philo->last_eat = get_time();
	philo->nb_eat++;
	sem_post((philo->info->is_eating));
}

void	*routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->info->forks);
		print_status(philo, philo->id, "has taken fork");
		sem_wait(philo->info->forks);
		print_status(philo, philo->id, "has taken fork");
		print_status(philo, philo->id, "is eating");
		eat_times(philo);
		if (philo->nb_eat == philo->info->nb_must_eat)
		{
			sem_post(philo->info->forks);
			sem_post(philo->info->forks);
			exit(0);
		}
		dormir(philo->info->time_to_eat);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		print_status(philo, philo->id, "is sleeping");
		dormir(philo->info->time_to_sleep);
		print_status(philo, philo->id, "is thinking");
	}
	return (NULL);
}

void	*check_death(void *philstruct)
{
	t_philo	*philo;

	philo = (t_philo *)philstruct;
	while (1)
	{
		sem_wait((philo->info->is_eating));
		if (get_time() - philo->last_eat >= philo->info->time_to_die)
		{
			print_status(philo, philo->id, "died");
			sem_post(philo->info->is_dead);
			sem_post((philo->info->is_eating));
			exit(1);
		}
		sem_post((philo->info->is_eating));
		dormir(1);
	}
	return (NULL);
}
