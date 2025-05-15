/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:55:48 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 11:49:43 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	main_aux(t_rules *rules, pthread_t supervise_thread)
{
	int	i;

	i = 0;
	while (i < rules->count_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	pthread_join(supervise_thread, NULL);
	i = 0;
	while (i < rules->count_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->death);
	free(rules->philos);
	free(rules->forks);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	int			i;
	pthread_t	supervise_thread;

	if (init_all(&rules, argc, argv) == 1)
		return (1);
	rules.start_time = get_time();
	i = 0;
	while (i < rules.count_philo)
	{
		rules.philos[i].last_meal = get_time();
		if (pthread_create(&rules.philos[i].thread, NULL,
				routine, &rules.philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&supervise_thread, NULL, supervise, &rules) != 0)
		return (1);
	main_aux(&rules, supervise_thread);
	return (0);
}
