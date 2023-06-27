/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:09:22 by maroy             #+#    #+#             */
/*   Updated: 2023/06/27 16:39:26 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_dead(t_sim *sim, t_philo *philo, t_timeval current)
{
	if (time_in_ms(current)
		- time_in_ms(philo->last_eaten) > (unsigned long)sim->time_to_die)
	{
		pthread_mutex_lock(&sim->speaker);
		printf("%ld %d %s", get_cur_time(sim), philo->id + 1, "died\n");
		return (OK);
	}
	return (KO);
}

void	observer(t_sim *sim, t_philo *philo)
{
	int i;
	t_timeval current;

	i = 0;
	usleep(200);
	while (1)
	{
		if (i == sim->nb_philo)
			i = 0;
		pthread_mutex_lock(&sim->breaker);
		gettimeofday(&current, NULL);
		if (check_dead(sim, &philo[i], current) == OK)
			break ;
		pthread_mutex_unlock(&sim->breaker);
		if (sim->fed_up == sim->nb_philo)
		{
			pthread_mutex_lock(&sim->speaker);
			printf("%ld %s", get_cur_time(sim),
					"All philosophers are fed up\n");
			break ;
		}
		i++;
	}
}