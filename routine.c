/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:46:34 by chugot            #+#    #+#             */
/*   Updated: 2023/09/26 19:46:37 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void *routine(void *data)
{
    t_philo *philo;

    printf("test routine\n");
    philo = (t_philo *) data;
    //check_death(philo);

    while (42)
    {
        printf("I'm the philosopher number %d !\n", philo->num_philo);
        usleep(100000);
        //usleep(philo->args->time_to_eat * 1000);
        //usleep(philo->args->time_to_eat * 1000);
    }
    return (0);
}
