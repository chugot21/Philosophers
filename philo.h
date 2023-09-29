/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:10:36 by chugot            #+#    #+#             */
/*   Updated: 2023/08/07 15:10:37 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int     num_philo;
    int     id_thread_philo;
    int     mutex_fork;
    int     nbr_meals;
    int     flag_death;
    pthread_t           thread_philo;
    unsigned long int   time_begin;
    unsigned long int   last_meal;
    pthread_mutex_t     m_fork;
    struct s_args       *args;
}   t_philo;

typedef struct  s_args
{
    int nbr_philo;
    t_philo *l_philos;
    //int *thread_philo;
    //int *num_philo;
    //int *num_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_meal;

    unsigned long int start_time;
    unsigned long int end_time;
    struct timeval tv;
}   t_args;

void    *routine(void *data);
int	    ft_atoi(const char *nptr);
void	error_msg(char *msg);
void    get_time(t_args *args);
void	event_msg(t_args *args, int i);
void    check_death(t_args *args);
void    ft_free(t_args *args);

#endif
