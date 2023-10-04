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
    args->l_philos[i - 1].last_meal = get_time() - args->start_time;
    args->l_philos[i - 1].time_ms = get_time() - args->start_time;
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
    args->l_philos = malloc(sizeof(t_philo) * (args->nbr_philo) + 1);
    if (!args->l_philos)
        error_msg("Error malloc\n");
    while (i <= args->nbr_philo)
    {
        create_tab_threads(args, i);
        printf("i : %d\n", i);
        i++;
    }
    //usleep(100000000);
}

void    error_args(t_args *args)
{
    if (args->nbr_philo == 1)
    {
        usleep(args->time_to_die * 1000); //attendre le time to die.
        args->end_time = get_time() - args->start_time;
        printf("%lld ms, n*1 died\n", args->end_time);
    }
}

//void    thread_check(t_args *args)
//{
//    args->id_t_check_death = pthread_create(&args->t_check_death, NULL, check_death, &args);
//    if (args->id_t_check_death != 0)
//        error_msg("Error thread\n");
//    
//}

int main(int argc, char **argv)
{
    t_args  args;

    if (argc < 5)
        exit(1);
    args.nbr_philo = ft_atoi(argv[1]);
    args.time_to_die = ft_atoi(argv[2]);
    printf("time to die ms : %d\n", args.time_to_die);
    args.time_to_eat = ft_atoi(argv[3]);
    args.time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args.nbr_meal = ft_atoi(argv[5]);
    else
        args.nbr_meal = 0; //revoir initialisation si pas cet argument.
    args.start_time = get_time();
    error_args(&args);
    create_threads(&args);
    printf("num philo %d\n", args.l_philos[2].num_philo);
    if (check_death(&args) == 1)
        exit(0);
    //usleep(10000);
    //check_death(&args); //free dedans.
    //gerer avec nombre de repas.
}
