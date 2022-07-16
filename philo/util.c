/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:30:04 by dha               #+#    #+#             */
/*   Updated: 2022/07/16 17:45:11 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

time_t	get_cur_time(void)
{
	struct timeval	t_val;
	time_t			cur;

	gettimeofday(&t_val, NULL);
	cur = t_val.tv_sec * 1000 + t_val.tv_usec / 1000;
	return (cur);
}

int	ft_atoi(const char *str)
{
	unsigned long	tot;
	int				sign;

	tot = 0;
	sign = 1 - ((*str == '-') << 1);
	str += (*str == '-' || *str == '+');
	while (*str >= '0' && *str <= '9')
	{
		if (tot > (unsigned long) LONG_MAX / 10 + (sign < 0))
			return ((sign < 0) - 1);
		tot = tot * 10;
		if (tot > (unsigned long) LONG_MAX - (*str - '0') + (sign < 0)
			&& *str != '0')
			return ((sign < 0) - 1);
		tot += (*str - '0');
		str++;
	}
	return (tot * sign);
}

int	ft_isnum(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
		write(fd, s++, 1);
}

int	ft_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (*ptr == NULL)
		return (err_malloc());
	memset(*ptr, 0, size);
	return (0);
}
