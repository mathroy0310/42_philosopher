/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:04:57 by maroy             #+#    #+#             */
/*   Updated: 2023/07/21 20:54:15 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int8_t	check_options(t_sim *sim)
{
	if (sim->nb_philo < 1 || sim->time_to_die < 1 || sim->time_to_eat < 1
		|| sim->time_to_sleep < 1)
		return (error_print(ERROR_ARGV));
	if (sim->nb_philo > 255)
		return (error_print(ERROR_PHILO));
	return (OK);
}

int8_t	init_options(t_sim *sim, char *argv[], int argc)
{
	sim->is_done = KO;
	sim->nb_philo = ft_atol(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		sim->must_eat = ft_atol(argv[5]);
		if (sim->must_eat < 1)
			return (error_print(ERROR_MUST_EAT));
	}
	else
		sim->must_eat = -1;
	sim->fed_up = 0;
	return (check_options(sim));
}

int8_t	init_mutex(t_sim *sim)
{
	int	i;

	if (pthread_mutex_init(&(sim->breaker), NULL) != 0)
		return (error_print(ERROR_MUTEX_BREAKER));
	if (pthread_mutex_init(&(sim->done), NULL) != 0)
		return (error_print(ERROR_MUTEX_DONE));
	if (pthread_mutex_init(&(sim->speaker), NULL) != 0)
		return (error_print(ERROR_MUTEX_SPEAKER));
	i = -1;
	while (++i < sim->nb_philo)
		if (pthread_mutex_init(&(sim->forks[i]), NULL) != 0)
			return (error_print(ERROR_MUTEX));
	return (OK);
}

int8_t	init_philos(t_sim *sim, t_philo *philo)
{
	int	i;

	if (gettimeofday(&sim->time_start, NULL) != 0)
		return (KO);
	i = 0;
	while (i < sim->nb_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = (i + 1) % sim->nb_philo;
		philo[i].right_fork = i;
		philo[i].eat_count = 0;
		philo[i].sim = sim;
		philo[i].last_eaten = sim->time_start;
		i++;
	}
	return (OK);
}
