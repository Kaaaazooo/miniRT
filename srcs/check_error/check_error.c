/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:47:45 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/17 10:17:28 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_handle_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	exit(0);
	return (0);
}

void	check_arg(int ac, char *str)
{
	if (ac < 2 || !*str)
		ft_handle_error("No arguments\n");
	if (ac > 3)
		ft_handle_error("Too many arguments\n");
	if (ft_strncmp(str + ft_strlen(str) - 3, ".rt", 3))
		ft_handle_error("Not a valid file\n");
}
