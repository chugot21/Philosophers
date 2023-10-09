/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:09:06 by chugot            #+#    #+#             */
/*   Updated: 2023/10/09 18:07:39 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    create_tab_threads(t_args *args, int i)
{
    t_philo     philo;
    pthread_mutex_t m_fork;

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
    args->l_philos[i - 1].id_thread_philo = pthread_create(&args->l_philos[i - 1].thread_philo, NULL, routine, &args->l_philos[i - 1]);
    if (args->l_philos[i - 1].id_thread_philo != 0)
        error_msg("Error thread\n");
}

void create_threads(t_args *args)
{
    int i;

    i = 1;
    args->forks = malloc(sizeof(pthread_mutex_t) * (args->nbr_philo) + 1);
    if (!args->forks)
        error_msg("Error malloc\n");
    args->l_philos = malloc(sizeof(t_philo) * (args->nbr_philo) + 1);
    if (!args->l_philos)
        error_msg("Error malloc\n");
    while (i <= args->nbr_philo)
    {
        create_tab_threads(args, i);
        i++;
    }  
}

void    only_one_fork(t_args *args)
{
    if (args->nbr_philo == 1)
    {
        usleep(args->time_to_die * 1000);
        args->end_time = get_time() - args->start_time;
        printf("%lld ms - 1 died\n", args->end_time);
        exit(0);
    }
}

void    check_errors(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (argc < 5 || argc > 6)
    {
        printf("Error number of arguments\n");
        exit(1);
    }
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
            {
                printf("Error arguments are not numbers.\n");
                exit(0);
            }
            j++;
        }
        i++;
    }
}

void    unlock_mutex(t_args *args)
{
    int i;

    i = 0;
    while (i < args->nbr_philo)
    {
        pthread_mutex_unlock(&args->forks[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_args  args;

    check_errors(argc, argv);
    args.nbr_philo = ft_atoi(argv[1]);
    args.time_to_die = ft_atoi(argv[2]);
    args.time_to_eat = ft_atoi(argv[3]);
    args.time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args.nbr_meal = ft_atoi(argv[5]);
    else
        args.nbr_meal = -1;
    args.start_time = get_time();
    only_one_fork(&args);
    create_threads(&args);
    unlock_mutex(&args);
    if (check_death(&args) == 1)
    {
        ft_free(&args);
        exit(0);
    }
}
