/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:48 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/25 15:41:53 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

static void	chk_arguments(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		exit(EXIT_FAILURE);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				exit(EXIT_FAILURE);
		}
	}
}

static void	init_arguments(char **av, t_info *info)
{
	info->number = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->must_eat_times = -1;
	if (av[5] != NULL)
	{
		info->must_eat_times = ft_atoi(av[5]);
		if (info->must_eat_times == 0)
			exit(EXIT_FAILURE);
	}
}

static void	init_sem(t_info *info)
{
	sem_unlink("/fork");
	sem_unlink("/end");
	sem_unlink("/prt");
	sem_unlink("/enough");
	info->fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, info->number);
	if (info->fork == SEM_FAILED)
		handle_error("sem open: ");
	info->end = sem_open("/end", O_CREAT | O_EXCL, 0644, 0);
	if (info->end == SEM_FAILED)
		handle_error("sem open: ");
	info->enough = sem_open("/enough", O_CREAT | O_EXCL, 0644, 0);
	if (info->enough == SEM_FAILED)
		handle_error("sem open: ");
	info->prt = sem_open("/prt", O_CREAT | O_EXCL, 0644, 1);
	if (info->end == SEM_FAILED)
		handle_error("sem open: ");
}

static void	init_philos(t_info *info)
{
	info->ptab = (t_philo *)malloc(sizeof(t_philo) * info->number);
	if (info->ptab == 0)
		handle_error("malloc: ");
	memset(info->ptab, 0, sizeof(t_philo) * info->number);
}

int	init_info(int ac, char **av, t_info *info)
{
	chk_arguments(ac, av);
	init_arguments(av, info);
	init_sem(info);
	init_philos(info);
	info->nenough = 0;
	gettimeofday(&(info->starttime), NULL);
	return (EXIT_SUCCESS);
}
