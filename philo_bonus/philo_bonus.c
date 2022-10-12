
#include "philo_bonus.h"

void    *routine()

void    start(t_info *info)
{
  
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
			free(info);
			ft_error(1);
		}
		else
			start(info);
	}
	else
		ft_error(2);
}