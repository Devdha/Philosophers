/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:41:25 by dha               #+#    #+#             */
/*   Updated: 2022/04/18 15:19:32 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_action(time_t begin, time_t limit)
{
	time_t	cur;

	while (1)
	{
		cur = get_cur_time();
		if (cur - begin >= limit)
			break ;
		usleep(100);
	}
}

void	print_in_thread(t_philo *philo, char *msg, time_t cur)
{
	pthread_mutex_lock(&(philo->root->output_mutex));
	printf("%8ldms %4d %s\n", cur - philo->root->start, philo->id, msg);
	pthread_mutex_unlock(&(philo->root->output_mutex));
}
