/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:47:45 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 20:41:31 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_handle_error(char *str, t_conf *conf)
{
	if (str)
		write(1, str, ft_strlen(str));
	free_all(conf);
	exit(0);
	return (0);
}

void	check_arg(int ac, char **av)
{
	if (ac < 2 || !av[1])
		ft_handle_error("No arguments\n", NULL);
	if (ac > 3)
		ft_handle_error("Too many arguments\n", NULL);
	if (ac == 3 && (!*av[2] || ft_strcmp(av[2], "-save")))
		ft_handle_error("Invalid argument\n", NULL);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3))
		ft_handle_error("Not a valid file\n", NULL);
}

void	check_color(t_vec *color, char *type, t_conf *conf)
{
	if (color->x < 0 || color->x > 255 ||
		color->y < 0 || color->y > 255 ||
		color->z < 0 || color->z > 255)
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : RGB out of range\n", conf);
	}
}

void	check_vector(t_vec *color, t_conf *conf, char *type)
{
	if (color->x < -1 || color->x > 1 ||
		color->y < -1 || color->y > 1 ||
		color->z < -1 || color->z > 1)
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : vector out of range\n", conf);
	}
}
