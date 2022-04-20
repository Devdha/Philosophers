/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:34:01 by dha               #+#    #+#             */
/*   Updated: 2022/04/20 19:46:19 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_eat(t_philo *philo)
{
	time_t	cur;

	sem_wait(philo->root->sem_fork);
	print_each(philo, 1, get_cur_time());
	if (philo->root->num_of_philo == 1)
	{
		wait_action(get_cur_time(), philo->root->time_to_die + 5);
		exit(0);
	}
	sem_wait(philo->root->sem_fork);
	print_each(philo, 1, get_cur_time());
	sem_wait(philo->sem_philo);
	philo->total_eat++;
	philo->last = get_cur_time();
	print_each(philo, 2, philo->last);
	cur = philo->last;
	sem_post(philo->sem_philo);
	if (!is_dead(philo))
		wait_action(cur, philo->root->time_to_eat);
	sem_post(philo->root->sem_fork);
	sem_post(philo->root->sem_fork);
	return (is_dead(philo));
}

static int	philo_sleep(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	print_each(philo, 3, cur);
	if (!is_dead(philo))
		wait_action(cur, philo->root->time_to_sleep);
	usleep(50);
	return (is_dead(philo));
}

static void	philo_think(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	print_each(philo, 4, cur);
}

int	is_done(t_philo *philo)
{
	int	is_done;

	is_done = 0;
	sem_wait(philo->sem_philo);
	if (philo->root->limit_to_eat == philo->total_eat)
		is_done = 1;
	sem_post(philo->sem_philo);
	return (is_done);
}

void	dining(t_philo *philo)
{
	pthread_create(&(philo->thread), NULL, scanner, philo);
	pthread_detach(philo->thread);
	if (philo->id % 2 == 0)
		wait_action(philo->root->start, philo->root->time_to_eat);
	while (!is_dead(philo))
	{
		if (philo_eat(philo))
			break ;
		if (philo->root->limit_to_eat != 0 && is_done(philo))
			sem_post(philo->root->sem_done);
		if (philo_sleep(philo))
			break ;
		philo_think(philo);
	}
	exit(0);
}
