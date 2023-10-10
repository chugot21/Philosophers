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
	//while (i < args->nbr_philo)
	//{
	//	pthread_join(args->l_philos[i].thread_philo, 0);
	//	i++;
	//}
	//i = 0;
    while (i < args->nbr_philo)
    {
        pthread_mutex_unlock(&args->forks[i]); //Revoir car fork dejà unlock.
        pthread_mutex_destroy(&args->forks[i]);
		i++;
    }
	pthread_mutex_unlock(&args->mutex_death);
	pthread_mutex_destroy(&args->mutex_death);
	free(args->forks);
    free(args->l_philos);
}

int	check_nbr_meals(t_args *args)
{
	int i;

	i = 0;
	while (i < args->nbr_philo)
	{
		if (args->nbr_meal == args->l_philos[i].nbr_meals)
			i++;
		else
			return (0);
	}
	return (1);
}

int    check_death(t_args *args) 
{
    int i;

	while (21)
	{
		//usleep(100);
		i = 0;
		pthread_mutex_lock(&args->mutex_death);
    	while (i < args->nbr_philo)
    	{
			args->l_philos[i].gap_meal = 0;
    	    args->l_philos[i].gap_meal = get_time() - args->l_philos[i].last_meal;
    	    if (args->l_philos[i].gap_meal > args->time_to_die)
    	    {
				args->l_philos[i].time_ms = get_time() - args->start_time;
				usleep(1000);
				printf("%lld ms - %d is died\n", args->l_philos[i].time_ms, args->l_philos[i].num_philo);
				return (1);
    	    }
			if (args->nbr_meal == args->l_philos[i].nbr_meals)
			{
				if (check_nbr_meals(args) == 1)
				{
					args->l_philos[i].time_ms = get_time() - args->start_time;
					usleep(1000);
					printf("%lld ms - All philosophers are full\n", args->l_philos[i].time_ms);
					return (1);
				}
			}
    	    i++;
    	}
		pthread_mutex_unlock(&args->mutex_death);
	}
}

// Test 4 310 200 100. One philosopher should die.
// Voir pour rajouter un mutex pour empecher que les philos volent des forks s'ils meurent -> voir si ok ? juste fork a free si pendant repas d'un autre. ./philo 4 310 200 100
//-> verif si un meurt et qu'un autre a les fork -> Revoir les free/unlock des fork  car peuvent etre lock.
// Voir pour attendre les autres threads avant d'exit ?