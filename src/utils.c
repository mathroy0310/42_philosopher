/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:21:09 by maroy             #+#    #+#             */
/*   Updated: 2023/06/21 18:55:17 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo.h"

static int	number(long x, int sign)
{
	if (sign > 0 && x <= 2147483647)
		return (sign * x);
	if (sign < 0 && x <= 2147483648)
		return (sign * x);
	return (0);
}

int	ft_atoi(const char *s)
{
	int			sign;
	long long	x;

	x = 0;
	sign = 1;
	while ((*s > 8 && *s < 14) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -sign;
		s++;
	}
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			x = x * 10 + *s - '0';
			s++;
		}
		else
			return (-1);
	}
	return (number(x, sign));
}

int error_print(char *error_message)
{
    printf("%s", error_message);
    return(EXIT_FAILURE);
}


unsigned long	time_in_ms(t_timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long	get_cur_time(t_sim *sim)
{
	t_timeval	current;
	t_timeval	start;

	start = sim->time_start;
	gettimeofday(&current, NULL);
	return (time_in_ms(current) - time_in_ms(start));
}