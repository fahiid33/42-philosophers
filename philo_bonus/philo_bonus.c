/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:59:36 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/15 03:57:58 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (err == 4)
	{
		write(1, "semaphore failed :(", 20);
		exit(1);
	}
}

void	*kill_childs(void *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)data;
	sem_wait(philo->info->is_dead);
	while (i < philo->info->nb_philo)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	return (NULL);
}

void	wait_and_kill(t_philo *philo)
{
	int				i;
	int				status;
	pthread_t		d_th;

	i = 0;
	pthread_create(&d_th, NULL, &kill_childs, philo);
	pthread_detach(d_th);
	while (waitpid(philo[i++].pid, &status, 0) > 0)
		;
}

void	start(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = init_philos(info);
	philo->info->start_time = get_time();
	while (i < info->nb_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo[i].last_eat = get_time();
			if (pthread_create(&philo[i].th, NULL,
					&check_death, &philo[i]) != 0)
				ft_error(3);
			routine(&philo[i]);
		}
		i++;
		usleep(40);
	}
	i = 0;
	while (i++ < info->nb_philo)
		pthread_detach(philo[i].th);
	wait_and_kill(philo);
	return ;
}

int	main(int ac, char **av)
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
