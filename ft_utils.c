/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:51:16 by chugot            #+#    #+#             */
/*   Updated: 2023/04/17 13:51:18 by chugot           ###   ########.fr       */
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

void	error_msg(char *msg)
{
	perror(msg);
	exit(1);
}

void    get_time(t_args *args)
{
    gettimeofday(&args->tv, NULL);
    args->end_time = (args->tv.tv_sec * 1000 + (args->tv.tv_usec / 1000)) - args->start_time;
}

void    ft_free(t_args *args)
{
    int i;

    i = 0;
    while (i < args->nbr_philo)
    {
        pthread_mutex_unlock(&args->l_philos[i].m_fork);
        pthread_mutex_destroy(&args->l_philos[i].m_fork);
    }
    free(args->l_philos);
}

void    check_death(t_args *args)
{
    int i;

    i = 0;
    while (i < args->nbr_philo)
    {
        gettimeofday(&args->tv, NULL);
		if (args->l_philos[i].last_meal == 0)
		{
			args->l_philos[i].last_meal = (args->tv.tv_sec * 1000 + (args->tv.tv_usec / 1000)) - args->start_time;
		}
		else
        	args->l_philos[i].last_meal = (args->tv.tv_sec * 1000 + (args->tv.tv_usec / 1000)) - args->l_philos[i].last_meal;
        if (args->l_philos[i].last_meal > args->time_to_die)
        {
			args->l_philos[i].flag_death = 1;
			event_msg(args, i);
            ft_free(args);
        }
        i++;
    }
}

void	event_msg(t_args *args, int i)
{
	if (args->l_philos[i].flag_death == 1)
	{
		gettimeofday(&args->tv, NULL);
		args->l_philos[i].time_begin = (args->tv.tv_sec * 1000 + (args->tv.tv_usec / 1000)) - args->start_time;
		printf("%ld ms, n*%d is died\n", args->l_philos[i].time_begin, args->l_philos[i].num_philo);
		if (i == args->nbr_philo)
			exit(0);
	}
	//if fork
	//if eating
	//if sleeping
	//if thinking
}
