/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:09:06 by chugot            #+#    #+#             */
/*   Updated: 2023/08/07 15:09:08 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    create_tab_threads(t_args *args, int i)
{
    t_philo     philo;

    philo.args = args;
    args->l_philos[i - 1].num_philo = i;
    args->l_philos[i - 1].last_meal = 0;
    args->l_philos[i - 1].time_begin = 0;
    args->l_philos[i - 1].nbr_meals = 0;
    args->l_philos[i - 1].mutex_fork = pthread_mutex_init(&philo.m_fork, NULL);
    args->l_philos[i - 1].id_thread_philo = pthread_create(&args->l_philos[i - 1].thread_philo, NULL, routine, &args->l_philos[i - 1]);
    if (args->l_philos[i - 1].id_thread_philo != 0)
        error_msg("Error thread\n");
}

void create_threads(t_args *args)
{
    int i;

    i = 1;
    args->l_philos = malloc(sizeof(t_philo *) * (args->nbr_philo + 1));
    if (!args->l_philos)
        error_msg("Error malloc\n");
    while (i <= args->nbr_philo)
    {
        create_tab_threads(args, i);
        i++;
    }
    usleep(10000);
}

void    error_args(t_args *args)
{
    if (args->nbr_philo == 1)
    {
        usleep(args->time_to_die * 1000); //attendre le time to die.
        get_time(args);
        printf("%ld ms, n*1 died\n", args->end_time);
    }
}

int main(int argc, char **argv)
{
    t_args  args;

    if (argc < 5)
        exit(1);
    args.nbr_philo = ft_atoi(argv[1]);
    args.time_to_die = ft_atoi(argv[2]);
    args.time_to_eat = ft_atoi(argv[3]);
    args.time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args.nbr_meal = ft_atoi(argv[5]);
    else
        args.nbr_meal = 0; //revoir initialisation si pas cet argument.
    if (gettimeofday(&args.tv, NULL) != 0)
        error_msg("Error gettimeofday start\n");
    args.start_time = args.tv.tv_sec * 1000 + (args.tv.tv_usec / 1000);
    error_args(&args);
    create_threads(&args);
    //usleep(10000);
    check_death(&args); //free dedans.
    //gerer avec nombre de repas.
}
