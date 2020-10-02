/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:10:05 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/02 11:43:43 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
# include "material.h"

struct s_mat;

t_conf	*read_file(char *filename, t_mlx *mlx);
int		parse(t_conf *config, char *str);
int		parse_r(t_coord **res, char *str);
int		parse_a(t_amb_l **amb_l, char *str);
int		parse_c(t_cam **cam, char *str);
int		parse_l(t_light **lights, char *str);
int		parse_sp(t_obj **objs, char *str);
int		parse_pl(t_obj **objs, char *str);
int		parse_sq(t_obj **objs, char *str);
int		parse_cy(t_obj **objs, char *str);
int		parse_tr(t_obj **objs, char *str);
int		parse_mat(char **str, struct s_mat *mat_ptr);

#endif
