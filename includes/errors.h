/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:48:19 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/05 16:04:20 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "mini_rt.h"

void	check_arg(int ac, char **av);
int		ft_handle_error(char *str);
void	check_color(t_vec *color);
void	check_vector(t_vec *vec, float x1, float x2);

#endif
