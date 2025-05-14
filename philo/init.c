/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:55:40 by rgu               #+#    #+#             */
/*   Updated: 2025/05/14 18:19:34 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	rules->philos = malloc(sizeof(t_philo) * rules->count_philo);
	if (!rules->philos)
		return (1);
	i = 0;
	while (i < rules->count_philo)
	{
		philo = &rules->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->rules = rules;
		philo->left_fork = &rules->forks[i];
		philo->right_fork = &rules->forks[(i + 1) % rules->count_philo];
		philo->meal_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo->meal_mutex)
			return (1);
		pthread_mutex_init(philo->meal_mutex, NULL);
		i++;
	}
	return (0);
}

void	init_all_aux(t_rules *rules)
{
	int	i ;

	i = 0;
	while (i < rules->count_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print, NULL);
	pthread_mutex_init(&rules->death, NULL);
}

int	init_all(t_rules *rules, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	rules->count_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	rules->nb_meals = -1;
	rules->someone_died = 0;
	if (argc == 6)
		rules->nb_meals = ft_atoi(argv[5]);
	if (rules->count_philo <= 0 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->count_philo);
	if (!rules->forks)
		return (1);
	init_all_aux(rules);
	if (init_philo(rules) != 0)
		return (1);
	return (0);
}
