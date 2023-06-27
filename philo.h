/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:28:39 by maroy             #+#    #+#             */
/*   Updated: 2023/06/27 17:23:43 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define OK 1
# define KO 0
# define ERROR_ARGC "\033[1;31m ERROR 🛑 : ARG COUNT \n\033[0m"
# define ERROR_ARGV "\033[1;31m ERROR 🛑 : ARG FORMAT \n\033[0m"
# define ERROR_PHILO "\033[1;31m ERROR 🛑 : PHILO COUNT \n\033[0m"
# define ERROR_MUST_EAT "\033[1;31m ERROR 🛑 : LAST ARGV \n\033[0m"
# define ERROR_MUTEX "\033[1;31m ERROR 🛑 : INIT MUTEX FAILED \n\033[0m"
# define ERROR_MUTEX_BREAKER "\033[1;31m ERROR 🛑 : INIT MUTEX BREAKER FAILED \n\033[0m"
# define ERROR_MUTEX_SPEAKER "\033[1;31m ERROR 🛑 : INIT MUTEX SPEAKER FAILED \n\033[0m"
# define ERROR_DETACH "\033[1;31m ERROR 🛑 : DETACH FAILED \n\033[0m"

typedef struct timeval	t_timeval;

typedef struct s_sim
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					fed_up;
	pthread_mutex_t		forks[255];
	pthread_mutex_t		breaker;
	pthread_mutex_t		speaker;
	t_timeval			time_start;

}						t_sim;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	t_sim				*sim;
	t_timeval			last_eaten;
}						t_philo;

int						init_options(t_sim *sim, char *argv[], int argc);
int						init_philos(t_sim *sim, t_philo *philo);
int						init_mutex(t_sim *sim);

int						philo_run(t_sim *sim, t_philo *philo);

int						ft_atoi(const char *str);
int						error_print(char *error_message);
unsigned long			time_in_ms(t_timeval time);
unsigned long			get_cur_time(t_sim *sim);

void					observer(t_sim *sim, t_philo *philo);

#endif
