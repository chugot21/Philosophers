/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <clara@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:51:16 by chugot            #+#    #+#             */
/*   Updated: 2023/10/08 13:51:18 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	num;

	num = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * sign);
}

long long int	get_time(void)
{
	struct timeval	clock;

	gettimeofday (&clock, NULL);
	return (clock.tv_sec * 1000 + (clock.tv_usec / 1000));
}

void	ft_free(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_join(args->l_philos[i].thread_philo, NULL);
		i++;
	}
	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->forks);
	free(args->l_philos);
}
