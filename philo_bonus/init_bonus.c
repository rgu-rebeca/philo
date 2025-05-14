/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:22 by rgu               #+#    #+#             */
/*   Updated: 2025/05/13 23:51:48 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_rules *rules)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_EAT);
	rules->forks = sem_open(SEM_FORKS, O_CREAT, 0644, rules->count_philo);
	rules->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	rules->death = sem_open(SEM_DEATH, O_CREAT, 0644, 1);
	rules->eat = sem_open(SEM_EAT, O_CREAT, 0644, rules->count_philo - 1);
	if (rules->forks == SEM_FAILED || rules->death == SEM_FAILED
		|| rules->print == SEM_FAILED)
		return (1);
	return (0);
}

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
		i++;
	}
	return (0);
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
	if (argc == 6)
		rules->nb_meals = ft_atoi(argv[5]);
	if (rules->count_philo <= 0 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (1);
	if (init_semaphores(rules) != 0)
		return (1);
	if (init_philo(rules) != 0)
		return (1);
	return (0);
}
