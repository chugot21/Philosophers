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

long long int    get_time()
{
	struct timeval clock;

    if (gettimeofday(&clock, NULL) != 0)
        error_msg("Error gettimeofday start\n");
    return (clock.tv_sec * 1000 + (clock.tv_usec / 1000));
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

int    check_death(t_args *args)
{
    int i;

	while (21)
	{
		printf("\ncheck death\n");
		usleep(10000);
		i = 0;
    	while (i < args->nbr_philo)
    	{
			if (args->l_philos[i].nbr_meals == 0)
			{
				printf("test\n");
    	    	args->l_philos[i].last_meal = get_time() - args->start_time;
				//printf("test last meal : %lld\n", args->l_philos[i].last_meal);
			}
			else
			{
				printf("test2\n");
				args->l_philos[i].last_meal = get_time() - args->l_philos[i].last_meal - args->start_time;
			}
    	    if (args->l_philos[i].last_meal > args->time_to_die)
    	    {
				args->l_philos[i].flag_death = 1;
				args->l_philos[i].time_ms = get_time() - args->start_time;
				printf("%lld ms, n*%d is died\n", args->l_philos[i].time_ms, args->l_philos[i].num_philo);
				//event_msg(args, i);
    	        //ft_free(args);
				return (1);
    	    }
    	    i++;
    	}
	}
}

/*void	event_msg(t_args *args, int i)
{
	if (args->l_philos[i].flag_death == 1)
	{
		args->l_philos[i].time_ms = get_time() - args->start_time;
		printf("%lld ms, n*%d is died\n", args->l_philos[i].time_ms, args->l_philos[i].num_philo);
		//if (i == (philo->args->nbr_philo - 1))
		//{
		ft_free(args);
		exit(0);
		//}
	}
	//if fork
	//if eating
	//if sleeping
	//if thinking
}*/
