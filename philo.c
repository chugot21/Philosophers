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

int    create_tab_threads(t_args *args, int i)
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
    {
        printf("Error thread\n");
        return (1);
    }
    return (0);
}

int create_threads(t_args *args)
{
    int i;

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
        return(1);
    }
    while (i <= args->nbr_philo)
    {
        if (create_tab_threads(args, i) == 1)
            return(1);
        i++;
    }
    return(0);
}

int    only_one_fork(t_args *args)
{
    if (args->nbr_philo == 1)
    {
        usleep(args->time_to_die * 1000);
        args->end_time = get_time() - args->start_time;
        printf("%lld ms - 1 died\n", args->end_time);
        return(1);
    }
    return(0);
}

int    check_errors(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (argc < 5 || argc > 6)
    {
        printf("Error number of arguments\n");
        return(1);
    }
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
            {
                printf("Error arguments are not numbers.\n");
                return(1);
            }
            j++;
        }
        i++;
    }
    return(0);
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

int init_struct(int argc, char **argv, t_args *args)
{
    args->nbr_philo = ft_atoi(argv[1]);
    if (args->nbr_philo > 200)
    {
        printf("Error too many philosophers\n");
        return(1);
    }
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args->nbr_meal = ft_atoi(argv[5]);
    else
        args->nbr_meal = -1;
    args->start_time = get_time();
    args->if_dead = -1;
    return(0);
}

int main(int argc, char **argv)
{
    t_args  args;

    if (check_errors(argc, argv) == 1)
        return(1);
    if (init_struct(argc, argv, &args) == 1)
        return(1);
    if (only_one_fork(&args) == 1)
        return(1);
    if (create_threads(&args) == 1)
        return(1);
    unlock_mutex(&args);
    if (check_death(&args) == 1)
    {
        ft_free(&args);
        return(0);
    }
}
