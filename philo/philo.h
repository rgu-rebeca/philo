/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:55:55 by rgu               #+#    #+#             */
/*   Updated: 2025/05/11 22:57:49 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define RED     "\033[1;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define RESET   "\033[0m"

typedef struct s_rules
{
	int				count_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	struct s_philo	*philos;
}	t_rules;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_mutex;
}	t_philo;

int		init_all(t_rules *rules, int argc, char **argv);
int		init_philo(t_rules *rules);
void	*routine(void *arg);
void	*supervise(void *arg);
long	get_time(void);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	print_log(t_philo *philo, char *msg);
int		all_philos_eaten_enough(t_rules *rules);
int		ft_strcmp(char *str1, char *str2);
#endif