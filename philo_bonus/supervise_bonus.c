/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:48 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 01:10:26 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*supervise(void *arg)
{
	t_philo	*philo;
	long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->rules->death);
		time_since_last_meal = get_time() - philo->last_meal;
		sem_post(philo->rules->death);
		if (time_since_last_meal > philo->rules->time_to_die)
		{
			print_log(philo, "died");
			exit (1);
		}
		usleep(2000);
	}
	return (NULL);
}
