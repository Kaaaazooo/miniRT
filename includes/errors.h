/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:48:19 by sabrugie          #+#    #+#             */
/*   Updated: 2020/03/07 10:28:37 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "mini_rt.h"

# define NO_ARG -1
# define BAD_NAME -2
# define MLX_FAIL -3
# define ALLOC_FAIL -4
# define WRONG_INPT -5
# define NO_CAM -6
# define WRONG_AC -7

void	check_arg(int ac, char *str, t_mlx *mlx);
int		ft_handle_error(int err);

#endif
