/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:23:52 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/20 12:38:24 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bphilo.h"

int	chk_atecnt(t_pth *pth)
{
	if (pth->info->args->must_eat_times == -1)
		return (EXIT_SUCCESS);
	if (pth->atecnt >= pth->info->args->must_eat_times)
	{
		pthread_mutex_lock(&(pth->info->lock));
		pth->info->enough++;
		pthread_mutex_unlock(&(pth->info->lock));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	chk_eat(t_pth *pth, int left, int right)
{
	long	tprev;
	long	tnext;
	long	tcur;

	if (pth->info->fork_tab[left] == ON | pth->info->fork_tab[right] == ON)
		return (EXIT_FAILURE);
	if (pth->name == 1)
	{
		tprev = pth->info->pth_tab[pth->info->args->number - 1].atetime;
	}
	else
		tprev = pth->info->pth_tab[pth->name - 2].atetime;
	tcur = (pth->info->pth_tab[pth->name - 1]).atetime;
	if (pth->name == pth->info->args->number)
		tnext = (pth->info->pth_tab[0]).atetime;
	else
		tnext = (pth->info->pth_tab[pth->name]).atetime;
	if (tcur > tprev || tcur > tnext)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	chk_dead(t_pth *pth)
{
	long	curtime;
	long	dietime;

	if (pth->dead == ON)
		return (TRUE);
	pthread_mutex_lock(&(pth->info->lock));
	if (pth->info->end == ON)
	{
		pthread_mutex_unlock(&(pth->info->lock));
		return (TRUE);
	}
	pthread_mutex_unlock(&(pth->info->lock));
	curtime = get_time(pth);
	dietime = pth->info->args->time_to_die;
	if (curtime - pth->atetime >= dietime)
	{
		printf("%ld %d died\n", get_time(pth), pth->name);
		pth->dead = ON;
		return (TRUE);
	}
	return (FALSE);
}
