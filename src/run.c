/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:41:39 by maroy             #+#    #+#             */
/*   Updated: 2023/07/21 21:03:44 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int8_t	philo_speak(t_sim *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->done);
	if (sim->is_done == true)
	{
		pthread_mutex_unlock(&sim->done);
		return (KO);
	}
	pthread_mutex_unlock(&sim->done);
	pthread_mutex_lock(&sim->speaker);
	printf("%lu %d %s\n", get_cur_time(sim), id + 1, msg);
	pthread_mutex_unlock(&sim->speaker);
	return (OK);
}

static void	philo_do(int time)
{
	t_timeval		current;
	unsigned long	do_before;

	gettimeofday(&current, NULL);
	do_before = time_in_ms(current) + time;
	while (time_in_ms(current) < do_before)
	{
		gettimeofday(&current, NULL);
		usleep(200);
	}
}

static int8_t	philo_eat(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->forks[philo->right_fork]);
	if (philo_speak(sim, philo->id, "has taken a fork") == KO)
		return (KO);
	pthread_mutex_lock(&sim->forks[philo->left_fork]);
	if (philo_speak(sim, philo->id, "has taken a fork") == KO)
		return (KO);
	pthread_mutex_lock(&sim->breaker);
	if (philo_speak(sim, philo->id, "is eating") == KO)
		return (KO);
	philo->eat_count++;
	gettimeofday(&philo->last_eaten, NULL);
	if (philo->eat_count == sim->must_eat)
		sim->fed_up++;
	pthread_mutex_unlock(&sim->breaker);
	philo_do(sim->time_to_eat);
	pthread_mutex_unlock(&sim->forks[philo->right_fork]);
	pthread_mutex_unlock(&sim->forks[philo->left_fork]);
	return (OK);
}

static void	*start_routine(void *arg)
{
	t_sim		*sim;
	t_philo		*philo;
	t_timeval	current;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		usleep(200);
	gettimeofday(&current, NULL);
	while (1)
	{
		if (philo_eat(sim, philo) == KO)
			break ;
		if (philo_speak(sim, philo->id, "is sleeping") == KO)
			break ;
		philo_do(sim->time_to_sleep);
		if (philo_speak(sim, philo->id, "is thinking") == KO)
			break ;
	}
	return (NULL);
}

int8_t	philo_run(t_sim *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, start_routine,
				(void *)(&philo[i])) != 0)
			return (error_print(ERROR_PTHREAD_CREATE));
		if (pthread_detach(philo[i].thread) != 0)
			return (error_print(ERROR_DETACH));
		i++;
	}
	return (OK);
}
