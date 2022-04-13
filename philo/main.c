/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:11:51 by dha               #+#    #+#             */
/*   Updated: 2022/04/13 19:53:00 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_root *root)
{
	int			i;
	pthread_t	thread;

	i = 0;
	root->start = get_cur_time();
	while (i < root->num_of_philo)
	{
		root->philos[i].last = root->start;
		pthread_create(&root->philos[i].thread, NULL, dining, &root->philos[i]);
		pthread_create(&thread, NULL, scanner, &root->philos[i]);
		pthread_detach(thread);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (set_args(&root, argc, argv))
		return (1);
	if (init_table(&root))
		return (1);
	start(&root);
	int	i = 0;
	while (i < root.num_of_philo)
		pthread_join(root.philos[i++].thread, NULL);
	return (0);
}
