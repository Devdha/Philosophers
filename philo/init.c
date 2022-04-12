/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:24:02 by dha               #+#    #+#             */
/*   Updated: 2022/04/11 17:39:33 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_root *root)
{
	int	i;

	if (ft_malloc(root->philos, root->num_of_philo * sizeof(t_philo)))
		return (1);
	if (ft_malloc(root->forks, root->num_of_philo * sizeof(pthread_mutex_t)))
		return (1);
	i = 0;
	while (i < root->num_of_philo)
	{
		root->philos[i].id = i + 1;
		pthread_mutex_init(&root->forks[i], NULL);
		pthread_mutex_init(&root->philos[i].mutex, NULL);
		root->philos[i].lfork = &root->forks[i];
		root->philos[i].rfork = &root->forks[i + 1 % root->num_of_philo];
		root->philos[i].root = root;
		i++;
	}
	return (0);
}
