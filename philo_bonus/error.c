/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:49:22 by dha               #+#    #+#             */
/*   Updated: 2022/04/11 17:28:37 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_invalid_input(void)
{
	ft_putstr_fd("Error: Invalid input\n", 2);
	return (0);
}

int	err_argnum(void)
{
	ft_putstr_fd("Error: Philo needs 4 or 5 arguments\n", 2);
	return (0);
}

int	err_malloc(void)
{
	ft_putstr_fd("Error: Memory allocation failed\n", 2);
	return (1);
}
