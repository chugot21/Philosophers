/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:10:36 by chugot            #+#    #+#             */
/*   Updated: 2023/10/09 17:30:28 by clara            ###   ########.fr       */
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
    int     nbr_meals;
    pthread_t           thread_philo;
    long long int   time_ms;
    long long int   last_meal;
    long long int   gap_meal;
    struct s_args       *args;
}   t_philo;

typedef struct  s_args
{
    int nbr_philo;
    t_philo *l_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_meal;
    pthread_mutex_t *forks;
    long long int start_time;
    long long int end_time;
    pthread_mutex_t mutex_death;
}   t_args;

void    *routine(void *data);
int	    ft_atoi(const char *nptr);
void	error_msg(char *msg);
long long int    get_time();
void	event_msg(t_args *args, int i);
int    check_death(t_args *args);
void    ft_free(t_args *args);

#endif
