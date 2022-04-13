/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:41:25 by dha               #+#    #+#             */
/*   Updated: 2022/04/13 21:34:10 by dha              ###   ########seoul.kr  */
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
		usleep(10);
	}
}
