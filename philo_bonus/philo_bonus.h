/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:38 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 01:10:35 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define RED     "\033[1;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define RESET   "\033[0m"

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_DEATH "/sem_death"
# define SEM_EAT "/sem_eat"

typedef struct s_rules
{
	int				count_philo;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			time_to_die;
	long			start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	sem_t			*eat;
	struct s_philo	*philos;
}	t_rules;

typedef struct s_philo
{
	int		id;
	pid_t	pid;
	long	last_meal;
	int		meals_eaten;
	t_rules	*rules;
}	t_philo;
int		init_all(t_rules *rules, int argc, char **argv);
long	get_time(void);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	print_log(t_philo *philo, char *msg);
void	routine(t_philo *philo);
int		ft_strcmp(char *str1, char *str2);
void	*supervise(void *arg);
#endif