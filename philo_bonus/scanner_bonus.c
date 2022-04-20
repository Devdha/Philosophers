/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:54:41 by dha               #+#    #+#             */
/*   Updated: 2022/04/20 20:26:58 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	int	is_dead;

	is_dead = 0;
	sem_wait(philo->sem_philo);
	if (philo->dead)
		is_dead = 1;
	sem_post(philo->sem_philo);
	return (is_dead);
}

static void	switch_to_dead(t_philo *philo, time_t cur)
{
	int	i;

	if (philo->dead == 0)
	{
		if (philo->root->limit_to_eat != 0)
		{
			i = 0;
			while (i++ < philo->root->num_of_philo)
				sem_post(philo->root->sem_done);
		}
		philo->dead = 1;
		print_each(philo, DIE_MSG, cur);
	}
	sem_post(philo->root->sem_end);
}

void	*done_scanner(void *ptr)
{
	int		i;
	t_root	*root;
	
	root = ptr;
	i = 0;
	while (i++ < root->num_of_philo)
		sem_wait(root->sem_done);
	sem_post(root->sem_end);
	return (NULL);
}

void	*scanner(void *ptr)
{
	time_t	cur;
	t_philo	*philo;

	philo = ptr;
	while (is_dead(philo) == 0)
	{
		cur = get_cur_time();
		sem_wait(philo->sem_philo);
		if (cur - philo->last >= philo->root->time_to_die)
			switch_to_dead(philo, cur);
		sem_post(philo->sem_philo);
	}
	return (NULL);
}
