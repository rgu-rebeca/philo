/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:03 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 12:37:16 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	if (ft_strcmp(msg, "is eating") == 0)
		color = GREEN;
	else if (ft_strcmp(msg, "is sleeping") == 0)
		color = YELLOW;
	else if (ft_strcmp(msg, "is thinking") == 0)
		color = BLUE;
	else if (ft_strcmp(msg, "has taken a fork") == 0)
		color = MAGENTA;
	else if (ft_strcmp(msg, "died") == 0)
		color = RED;
	else
		color = RESET;
	pthread_mutex_lock(&philo->rules->print);
	pthread_mutex_lock(&philo->rules->death);
	if (!philo->rules->someone_died)
	{
		timestamp = get_time() - philo->rules->start_time;
		printf("%s%ld %d %s%s\n", color, timestamp, philo->id, msg, RESET);
	}
	pthread_mutex_unlock(&philo->rules->death);
	pthread_mutex_unlock(&philo->rules->print);
}

int	routine_aux_1(t_philo *philo)
{
	if (philo->rules->count_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		precise_sleep(philo->rules->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	routine_aux_2(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_log(philo, "is eating");
	precise_sleep(philo->rules->time_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	print_log(philo, "is sleeping");
	precise_sleep(philo->rules->time_to_sleep);
	print_log(philo, "is thinking");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (routine_aux_1(philo) == 1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->death);
		if (philo->rules->someone_died == 1)
			return (pthread_mutex_unlock(&philo->rules->death), NULL);
		pthread_mutex_unlock(&philo->rules->death);
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->left_fork);
		else
			pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->right_fork);
		else
			pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		routine_aux_2(philo);
	}
	return (NULL);
}
