/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:55:59 by fahd              #+#    #+#             */
/*   Updated: 2022/07/20 00:57:50 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

int	all_good(int ac, char **av, t_info *info)
{
	if (check_arg(av))
	{
		info->nb_philo = atoi(av[1]);
		if (info->nb_philo == 0)
			return (0);
		info->time_to_die = atoi(av[2]);
		info->time_to_eat = atoi(av[3]);
		info->time_to_sleep = atoi(av[4]);
		if (ac == 6)
			info->nb_must_eat = atoi(av[5]);
		else
			info->nb_must_eat = -1;
		return (1);
	}
	return (0);
}
