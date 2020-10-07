/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:47:45 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/05 16:07:24 by sabrugie         ###   ########.fr       */
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

void	check_arg(int ac, char **av)
{
	if (ac < 2 || !av[1])
		ft_handle_error("No arguments\n");
	if (ac > 3)
		ft_handle_error("Too many arguments\n");
	if (ac == 3 && (!*av[2] || ft_strcmp(av[2], "-save")))
		ft_handle_error("Invalid argument\n");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3))
		ft_handle_error("Not a valid file\n");
}

void	check_color(t_vec *color)
{
	if (color->x < 0 || color->x > 255)
		ft_handle_error("RGB out of range\n");
	if (color->y < 0 || color->y > 255)
		ft_handle_error("RGB out of range\n");
	if (color->z < 0 || color->z > 255)
		ft_handle_error("RGB out of range\n");
}

void	check_vector(t_vec *color, float x1, float x2)
{
	if (color->x < x1 || color->x > x2)
		ft_handle_error("Vector out of range\n");
	if (color->y < x1 || color->y > x2)
		ft_handle_error("Vector out of range\n");
	if (color->z < x1 || color->z > x2)
		ft_handle_error("Vector out of range\n");
}
