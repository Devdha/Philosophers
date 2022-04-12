/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:11:51 by dha               #+#    #+#             */
/*   Updated: 2022/04/12 11:56:46 by dha              ###   ########seoul.kr  */
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
		pthread_create(&root->philos[i].thread, NULL,
			dining, &root->philos[i]);
	}
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (set_args(&root, argc, argv))
		return (1);
	if (init_table(&root))
		return (1);
	// 초기화
	start(&root);
	// 수행
	// 뮤텍스 날리고
	// 남은 거 프리 해주면 끝
	return (0);
}
