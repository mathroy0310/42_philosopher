/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:41:39 by maroy             #+#    #+#             */
/*   Updated: 2023/06/27 17:24:51 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_speak(t_sim *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->speaker);
	printf("%lu %d %s\n", get_cur_time(sim), id + 1, msg);
	pthread_mutex_unlock(&sim->speaker);
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

static void	philo_eat(t_sim *sim, t_philo *philo)
{
	pthread_mutex_lock(&sim->forks[philo->right_fork]);
	philo_speak(sim, philo->id, "has taken a fork");
	pthread_mutex_lock(&sim->forks[philo->left_fork]);
	philo_speak(sim, philo->id, "has taken a fork");
	pthread_mutex_lock(&sim->breaker);
	philo_speak(sim, philo->id, "is eating");
	philo->eat_count++;
	gettimeofday(&philo->last_eaten, NULL);
	if (philo->eat_count == sim->must_eat)
		sim->fed_up++;
	pthread_mutex_unlock(&sim->breaker);
	philo_do(sim->time_to_eat);
	pthread_mutex_unlock(&sim->forks[philo->right_fork]);
	pthread_mutex_unlock(&sim->forks[philo->left_fork]);
}

void	*routine(void *arg)
{
	t_sim	*sim;
	t_philo	*philo;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		philo_eat(sim, philo);
		philo_speak(sim, philo->id, "is sleeping");
		philo_do(sim->time_to_sleep);
		philo_speak(sim, philo->id, "is thinking");
	}
	return (NULL);
}

int	philo_run(t_sim *sim, t_philo *philo)
{
	int i;

	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine,
				(void *)(&philo[i])) != 0)
			return (error_print(ERROR_MUTEX));
		if (pthread_detach(philo[i].thread) != 0)
			return (error_print(ERROR_DETACH));
		i++;
	}
	return (OK);
}