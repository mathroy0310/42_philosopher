/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:09:22 by maroy             #+#    #+#             */
/*   Updated: 2023/07/21 21:15:48 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int8_t	is_dead(t_sim *sim, t_philo *philo, t_timeval current)
{
	if (time_in_ms(current)
		- time_in_ms(philo->last_eaten) > (unsigned long)sim->time_to_die)
	{
		pthread_mutex_lock(&sim->done);
		sim->is_done = true;
		pthread_mutex_unlock(&sim->done);
		return (OK);
	}
	return (KO);
}

static int8_t	is_fed_up(t_sim *sim)
{
	if (sim->fed_up == sim->nb_philo)
	{
		pthread_mutex_lock(&sim->done);
		sim->is_done = true;
		pthread_mutex_unlock(&sim->done);
		pthread_mutex_lock(&sim->speaker);
		printf("%ld %s", get_cur_time(sim), "All philosophers are fed up\n");
		pthread_mutex_unlock(&sim->speaker);
		return (OK);
	}
	return (KO);
}

static int8_t	is_done(t_sim *sim, t_philo *philo)
{
	t_timeval	current;

	pthread_mutex_lock(&sim->breaker);
	gettimeofday(&current, NULL);
	if (is_dead(sim, philo, current) == OK)
	{
		pthread_mutex_lock(&sim->speaker);
		printf("%lu %d has died\n", get_cur_time(sim), philo->id + 1);
		pthread_mutex_unlock(&sim->speaker);
		return (OK);
	}
	if (is_fed_up(sim) == OK)
		return (OK);
	pthread_mutex_unlock(&sim->breaker);
	return (KO);
}

void	observer(t_sim *sim, t_philo *philo)
{
	int			i;

	i = 0;
	usleep(200);
	while (1)
	{
		if (i == sim->nb_philo)
			i = 0;
		if (is_done(sim, philo) == OK)
			break ;
		i++;
	}
}
