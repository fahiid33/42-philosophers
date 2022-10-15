/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 02:37:20 by fstitou           #+#    #+#             */
/*   Updated: 2022/10/15 03:03:50 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, int id, char *state)
{
	pthread_mutex_lock(&philo->info->print);
	printf("%u %d %s\n", get_time() - philo->info->start_time, id, state);
	if (state[0] != 'd')
		pthread_mutex_unlock(&philo->info->print);
}

unsigned int	get_time(void)
{
	struct timeval	tv;
	unsigned int	time;

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
