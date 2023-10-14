/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:43:01 by chugot            #+#    #+#             */
/*   Updated: 2023/10/14 00:43:07 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_tab_threads(t_args *args, int i)
{
	t_philo			philo;
	pthread_mutex_t	m_fork;

	args->forks[i - 1] = m_fork;
	pthread_mutex_init(&args->forks[i - 1], NULL);
	pthread_mutex_lock(&args->forks[i - 1]);
	philo.args = args;
	args->l_philos[i - 1].args = args;
	args->l_philos[i - 1].num_philo = i;
	args->l_philos[i - 1].last_meal = get_time();
	args->l_philos[i - 1].gap_meal = 0;
	args->l_philos[i - 1].time_ms = get_time() - args->start_time;
	args->l_philos[i - 1].nbr_meals = 0;
	args->l_philos[i - 1].id_thread_philo = pthread_create(
			&args->l_philos[i - 1].thread_philo,
			NULL, routine, &args->l_philos[i - 1]);
	if (args->l_philos[i - 1].id_thread_philo != 0)
	{
		printf("Error thread\n");
		return (1);
	}
	return (0);
}

int	create_threads(t_args *args)
{
	int	i;

	i = 1;
	pthread_mutex_init(&args->mutex_death, NULL);
	args->forks = malloc(sizeof(pthread_mutex_t) * (args->nbr_philo) + 1);
	if (!args->forks)
	{
		printf("Error malloc\n");
		return (1);
	}
	args->l_philos = malloc(sizeof(t_philo) * (args->nbr_philo) + 1);
	if (!args->l_philos)
	{
		printf("Error malloc\n");
		return (1);
	}
	while (i <= args->nbr_philo)
	{
		if (create_tab_threads(args, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
