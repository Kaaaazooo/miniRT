/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:47:45 by sabrugie          #+#    #+#             */
/*   Updated: 2020/03/07 10:36:51 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_handle_error(int err)
{
	if (err == NO_ARG)
		write(1, "Error - No filename\n", 20);
	else if (err == BAD_NAME)
		write(1, "Error - Wrong file\n", 19);
	else if (err == MLX_FAIL)
		write(1, "Error - MLX init failed\n", 23);
	else if (err == ALLOC_FAIL)
		write(1, "Error - Malloc failed\n", 22);
	else if (err == WRONG_INPT)
		write(1, "Error - Wrong input\n", 20);
	else if (err == NO_CAM)
		write(1, "Error - No camera\n", 18);
	exit(0);
	return (0);
}

void	check_arg(int ac, char *str, t_mlx *mlx)
{
	if (ac < 2 || !*str)
		ft_handle_error(NO_ARG);
	if (ac > 3)
		ft_handle_error(WRONG_AC);
	if (ft_strncmp(str + ft_strlen(str) - 3, ".rt", 3))
		ft_handle_error(BAD_NAME);
	if (!(mlx->ptr = mlx_init()))
		ft_handle_error(MLX_FAIL);
}
