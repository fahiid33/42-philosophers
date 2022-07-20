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

void	start(t_info *info)
{
	
}

int main(int ac, char **av)
{
    t_info	*info;
	info = NULL;
	if (ac == 5 || ac == 6)
	{
		info = malloc(sizeof(t_info));
		if (!all_good(ac, av, info))
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