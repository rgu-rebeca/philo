/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:11 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 11:49:10 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	supervise_aux(t_rules *rules)
{
	int		i;
	long	time_since_last_meal;
	t_philo	*philo;

	i = 0;
	while (i < rules->count_philo)
	{
		philo = &rules->philos[i];
		pthread_mutex_lock(&philo->meal_mutex);
		time_since_last_meal = get_time() - philo->last_meal;
		if (time_since_last_meal > rules->time_to_die)
		{
			print_log(philo, "died");
			pthread_mutex_lock(&rules->death);
			rules->someone_died = 1;
			pthread_mutex_unlock(&rules->death);
			pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		i++;
	}
	return (0);
}

void	*supervise(void *arg)
{
	t_rules	*rules;
	int		result;

	rules = (t_rules *)arg;
	while (1)
	{
		pthread_mutex_lock(&rules->death);
		if (rules->someone_died == 1)
			return (pthread_mutex_unlock(&rules->death), NULL);
		pthread_mutex_unlock(&rules->death);
		if (supervise_aux(rules) == 1)
			return (NULL);
		result = all_philos_eaten_enough(rules);
		if (rules->nb_meals > 0 && result == 1)
		{
			pthread_mutex_lock(&rules->death);
			rules->someone_died = 1;
			pthread_mutex_unlock(&rules->death);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
