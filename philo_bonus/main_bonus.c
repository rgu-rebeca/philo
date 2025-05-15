/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:56:31 by rgu               #+#    #+#             */
/*   Updated: 2025/05/15 12:17:32 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	launch_philo(t_rules *rules)
{
	int	i;

	rules->start_time = get_time();
	i = 0;
	while (i < rules->count_philo)
	{
		rules->philos[i].pid = fork();
		if (rules->philos[i].pid < 0)
			return (1);
		if (rules->philos[i].pid == 0)
			routine(&rules->philos[i]);
		i++;
	}
	return (0);
}

void	wait_for_philos(t_rules *rules)
{
	int		status;
	int		i;
	int		n;

	n = 0;
	while (n < rules->count_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < rules->count_philo)
					kill(rules->philos[i++].pid, SIGKILL);
			}
		}
		n++;
	}
}

void	clean(t_rules *rules)
{
	sem_close(rules->forks);
	sem_close(rules->print);
	sem_close(rules->death);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEATH);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (init_all(&rules, argc, argv) != 0)
		return (1);
	if (launch_philo(&rules) != 0)
		return (1);
	wait_for_philos(&rules);
	clean(&rules);
	free(rules.philos);
	return (0);
}
