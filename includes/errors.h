/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:48:19 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 20:39:54 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "mini_rt.h"

void	check_arg(int ac, char **av);
int		ft_handle_error(char *str, t_conf *conf);
void	check_color(t_vec *color, char *type, t_conf *conf);
void	check_vector(t_vec *vec, t_conf *conf, char *type);

#endif
