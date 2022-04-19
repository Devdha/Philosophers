/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:27:17 by dha               #+#    #+#             */
/*   Updated: 2022/04/19 19:17:21 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->num_of_philo)
	{
		root->philos[i].pid = fork();
		if (root->philos[i].pid == 0)
		{
			dining(root->philos[i]);
			break ;
		}
		else if (root->philos[i].pid < 0)
		{
			kill_until(i, root);
			exit(1);
		}
		++i;
	}
}

void	end(t_root *root)
{
	
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (set_args(&root, argc, argv))
		return (1);
	if (init_table(&root))
		return (1);
	start(&root);
	sem_wait(root.sem_end);
	end(&root);
}
