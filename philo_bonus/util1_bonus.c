/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:41:25 by dha               #+#    #+#             */
/*   Updated: 2022/04/19 19:24:03 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_each(t_philo *philo, char *msg, time_t cur)
{
	sem_wait(philo->root->sem_output);
	printf("%8ldms %4d %s\n", cur - philo->root->start, philo->id, msg);
	sem_post(philo->root->sem_output);
}

size_t	ft_strlen(const char *s)
{
	const char	*cp;

	cp = s;
	while (*cp)
		cp++;
	return (cp - s);
}

char	*ft_strjoin(char const *s1, char *s2)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		if (i < ft_strlen(s1))
			str[i] = s1[i];
		else
			str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	free(s2);
	return (str);
}

void	kill_until(int i, t_root *root)
{
	int	idx;

	idx = 0;
	while (idx < i)
		kill(root->philos[idx++].pid, SIGTERM);
}
