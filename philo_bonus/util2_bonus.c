/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:19:42 by dha               #+#    #+#             */
/*   Updated: 2022/04/19 19:20:00 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static unsigned char	alen(int n)
{
	long long		num;
	unsigned char	len;

	if (n == 0)
		return (1);
	len = 0;
	num = n;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static unsigned int	pow_ten(unsigned char exp)
{
	unsigned int	ret;

	ret = 1;
	while (exp--)
		ret *= 10;
	return (ret);
}

char	*ft_itoa(int n)
{
	long long		num;
	char			*ret;
	unsigned char	len;
	unsigned char	i;

	len = alen(n);
	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (0);
	i = 0;
	num = n;
	if (num < 0)
	{
		num = -num;
		ret[i++] = '-';
		len--;
	}
	while (len > 0)
	{
		ret[i++] = (num / pow_ten(len - 1)) + '0';
		num %= pow_ten(len - 1);
		len--;
	}
	ret[i] = '\0';
	return (ret);
}
