/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:04:39 by dha               #+#    #+#             */
/*   Updated: 2022/04/18 10:17:15 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_root *root)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&(root->mutex));
	if (root->dead)
		is_dead = 1;
	pthread_mutex_unlock(&(root->mutex));
	return (is_dead);
}

void	*scanner(void *ptr)
{
	time_t	cur;
	t_root	*root;
	int		i;

	i = 0;
	root = ptr;
	while (is_dead(root) == 0)
	{
		// printf("idx: %d\n", i);
		cur = get_cur_time();
		pthread_mutex_lock(&(root->philos[i].mutex));
		if (cur - root->philos[i].last >= root->time_to_die)
		{
			cur = get_cur_time();
			pthread_mutex_lock(&(root->mutex));
			if (root->dead == 0)
			{
				root->dead = 1;
				print_in_thread(&(root->philos[i]), "died", cur);
				// printf("%ld %d died\n", cur - root->start, root->philos[i].id);
			}
			pthread_mutex_unlock(&(root->mutex));
		}
		pthread_mutex_unlock(&(root->philos[i].mutex));
		if (++i == root->num_of_philo)
			i = 0;
	}
	return (NULL);
}
