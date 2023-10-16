/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:28:30 by chugot            #+#    #+#             */
/*   Updated: 2023/10/14 00:28:31 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nbr_meals(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		if (args->l_philos[i].nbr_meals >= args->nbr_meal)
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_death_max_meals(t_args *args, int i, int j)
{
	if (args->l_philos[i].nbr_meals == args->nbr_meal)
	{
		if (check_nbr_meals(args) == 1)
		{
			args->l_philos[i].time_ms = get_time() - args->start_time;
			while (j < args->nbr_philo)
			{
				args->l_philos[j].args->if_dead = 1;
				j++;
			}
			usleep(1000);
			printf("%lld ms - All philosophers are full\n",
				args->l_philos[i].time_ms);
			return (1);
		}
	}
	return (0);
}

void	init_gap_meal(t_args *args, int i)
{
	args->l_philos[i].gap_meal = 0;
	args->l_philos[i].gap_meal = get_time() - args->l_philos[i].last_meal;
}

int	check_death(t_args *args)
{
	int	i;
	int	j;

	j = 0;
	while (21)
	{
		i = 0;
		init_gap_meal(args, i);
		while (i < args->nbr_philo)
		{
			if (args->l_philos[i].gap_meal > args->time_to_die)
			{
				args->l_philos[i].time_ms = get_time() - args->start_time;
				usleep(1000);
				printf("%lld ms - %d died\n", args->l_philos[i].time_ms,
					args->l_philos[i].num_philo);
				while (j < args->nbr_philo)
					args->l_philos[j++].args->if_dead = 1;
				return (1);
			}
			if (check_death_max_meals(args, i, j) == 1)
				return (1);
			i++;
		}
	}
}
