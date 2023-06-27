/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:26:05 by maroy             #+#    #+#             */
/*   Updated: 2023/06/27 17:33:02 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void destroy_mutex(t_sim *sim)
{
    int i;

    i = 0;
    while (i < sim->nb_philo)
    {
        pthread_mutex_destroy(&sim->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&sim->speaker);
    pthread_mutex_destroy(&sim->breaker);
}

void    destroy_pthread(t_sim *sim, t_philo *philo)
{
    int i;

    i = 0;
    while (i < sim->nb_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}

int main (int argc , char *avrg[])
{
    t_sim sim;
    t_philo philo[255];

    if ( argc < 5 ||  argc >  6)
        return(error_print(ERROR_ARGC)); 
    if (init_options(&sim, avrg, argc) == KO)
        return (EXIT_FAILURE);
    if (init_philos(&sim, philo) == KO || init_mutex(&sim) == KO)
        return (EXIT_FAILURE);
    if (philo_run(&sim, philo) == KO)
        return (EXIT_FAILURE);
    observer(&sim, philo);
    destroy_mutex(&sim);
    destroy_pthread(&sim, philo);
    return (EXIT_SUCCESS);
}