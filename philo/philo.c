/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:52:17 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/15 03:02:54 by fstitou          ###   ########.fr       */
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

void	start(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = init_philos(info);
	philo->info->start_time = get_time();
	while (i < info->nb_philo)
	{
		philo[i].finished = 0;
		philo[i].dead = 0;
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) != 0)
			ft_error(3);
		pthread_detach(philo[i].th);
		i++;
		usleep(40);
	}
	while (!is_dead(philo) && !check_meals(philo))
		;
	return ;
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = NULL;
	if (ac == 5 || ac == 6)
	{
		info = malloc(sizeof(t_info));
		if (!init_args(ac, av, info))
		{
			free(info);
			ft_error(1);
		}
		else
		{
			start(info);
		}	
	}
	else
		ft_error(2);
}
