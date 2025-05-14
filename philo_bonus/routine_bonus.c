/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:43 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 01:10:18 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	precise_sleep(long duration)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
		usleep(100);
}

void	print_log(t_philo *philo, char *msg)
{
	long	timestamp;
	char	*color;

	sem_wait(philo->rules->print);
	if (ft_strcmp(msg, "is eating") == 0)
		color = GREEN;
	else if (ft_strcmp(msg, "is sleeping") == 0)
		color = YELLOW;
	else if (ft_strcmp(msg, "is thinking") == 0)
		color = BLUE;
	else if (ft_strcmp(msg, "has taken a fork") == 0)
		color = CYAN;
	else if (ft_strcmp(msg, "died") == 0)
		color = RED;
	else
		color = RESET;
	timestamp = get_time() - philo->rules->start_time;
	printf("%s%ld %d %s%s\n", color, timestamp, philo->id, msg, RESET);
	sem_post(philo->rules->print);
}

void	routine_aux(t_philo *philo)
{
	sem_wait(philo->rules->eat);
	sem_wait(philo->rules->forks);
	print_log(philo, "has taken a fork");
	sem_wait(philo->rules->forks);
	print_log(philo, "has taken a fork");
	sem_post(philo->rules->eat);
	print_log(philo, "is eating");
	sem_wait(philo->rules->death);
	philo->last_meal = get_time();
	sem_post(philo->rules->death);
	precise_sleep(philo->rules->time_to_eat);
	philo->meals_eaten++;
	if (philo->rules->nb_meals > 0
		&& philo->meals_eaten >= philo->rules->nb_meals)
	{
		sem_post(philo->rules->forks);
		sem_post(philo->rules->forks);
		exit (0);
	}
	sem_post(philo->rules->forks);
	sem_post(philo->rules->forks);
	print_log(philo, "is sleeping");
	precise_sleep(philo->rules->time_to_sleep);
	print_log(philo, "is thinking");
}

void	routine(t_philo *philo)
{
	pthread_t	supervise_thread;

	if (pthread_create(&supervise_thread, NULL, supervise, philo) != 0)
		exit (1);
	pthread_detach(supervise_thread);
	philo->last_meal = get_time();
	if (philo->rules->count_philo == 1)
	{
		sem_wait(philo->rules->forks);
		print_log(&philo[0], "has taken a fork");
		usleep(philo->rules->time_to_die * 1000);
		print_log(&philo[0], "died");
		exit(0);
	}
	while (1)
	{
		routine_aux(philo);
	}
	return ;
}
