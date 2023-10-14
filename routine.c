/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:46:34 by chugot            #+#    #+#             */
/*   Updated: 2023/10/09 19:34:29 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_eating_unlock_mutex(t_philo *philo)
{
	if (philo->num_philo == philo->args->nbr_philo)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->num_philo - 1]);
		pthread_mutex_unlock(&philo->args->forks[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->forks[philo->num_philo - 1]);
		pthread_mutex_unlock(&philo->args->forks[philo->num_philo]);
	}
}

void	routine_eating(t_philo *philo)
{
	if (philo->num_philo == philo->args->nbr_philo)
	{
		pthread_mutex_lock(&philo->args->forks[philo->num_philo - 1]);
		pthread_mutex_lock(&philo->args->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&philo->args->forks[philo->num_philo - 1]);
		pthread_mutex_lock(&philo->args->forks[philo->num_philo]);
	}
	philo->time_ms = get_time() - philo->args->start_time;
	if (philo->args->if_dead == -1)
		printf("%lld ms - %d has taken a fork\n%lld ms - %d has taken a fork\n",
			philo->time_ms, philo->num_philo, philo->time_ms, philo->num_philo);
	philo->time_ms = get_time() - philo->args->start_time;
	if (philo->args->if_dead == -1)
		printf("%lld ms - %d is eating\n", philo->time_ms, philo->num_philo);
	philo->last_meal = get_time();
	usleep(philo->args->time_to_eat * 1000);
	philo->nbr_meals++;
	routine_eating_unlock_mutex(philo);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (philo->num_philo % 2 == 0)
		usleep(philo->args->time_to_eat * 1000);
	while (7)
	{
		if (philo->args->if_dead == 1)
			break ;
		routine_eating(philo);
		if (philo->args->if_dead == 1)
			break ;
		philo->time_ms = get_time() - philo->args->start_time;
		printf("%lld ms - %d is sleeping\n", philo->time_ms, philo->num_philo);
		usleep(philo->args->time_to_sleep * 1000);
		if (philo->args->if_dead == 1)
			break ;
		philo->time_ms = get_time() - philo->args->start_time;
		printf("%lld ms - %d is thinking\n", philo->time_ms, philo->num_philo);
		if (philo->args->if_dead == 1)
			break ;
	}
	return (0);
}
