/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:26:05 by maroy             #+#    #+#             */
/*   Updated: 2023/07/21 20:38:15 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutex(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philo)
		pthread_mutex_destroy(&sim->forks[i]);
	pthread_mutex_destroy(&sim->speaker);
	pthread_mutex_destroy(&sim->breaker);
	pthread_mutex_destroy(&sim->done);
}

int	main(int argc, char *argv[])
{
	t_sim	sim;
	t_philo	philo[255];

	if (argc < 5 || argc > 6)
		return (error_print(ERROR_ARGC));
	if (init_options(&sim, argv, argc) == KO)
		return (EXIT_FAILURE);
	if (init_philos(&sim, philo) == KO || init_mutex(&sim) == KO)
		return (EXIT_FAILURE);
	if (philo_run(&sim, philo) == KO)
		return (EXIT_FAILURE);
	observer(&sim, philo);
	usleep(sim.time_to_die * 1000);
	destroy_mutex(&sim);
	return (EXIT_SUCCESS);
}
