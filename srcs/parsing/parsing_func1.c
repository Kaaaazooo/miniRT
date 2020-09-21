/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:49:02 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/21 16:01:11 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sp(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_sp	*sphere;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = SP;
	if (!(sphere = malloc(sizeof(t_sp))) ||
				!(sphere->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	sphere->pos = skip_atov(&str);
	sphere->pos.x *= -1;
	sphere->radius = skip_atof(&str) / 2;
	parse_mat(&str, sphere->mat_ptr);
	new->obj = sphere;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_pl(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_pl	*plane;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = PL;
	if (!(plane = malloc(sizeof(t_pl))) ||
				!(plane->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	plane->pos = skip_atov(&str);
	plane->pos.x *= -1;
	plane->ori = skip_atov(&str);
	parse_mat(&str, plane->mat_ptr);
	new->obj = plane;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_sq(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_sq	*square;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = SQ;
	if (!(square = malloc(sizeof(t_sq))) ||
				!(square->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	square->pos = skip_atov(&str);
	square->pos.x *= -1;
	square->ori = skip_atov(&str);
	square->size = skip_atof(&str);
	parse_mat(&str, square->mat_ptr);
	new->obj = square;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_cy(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_sp	*sphere;

	tmp = *objs;
	while (tmp)
		tmp = tmp->next;
	if (!(tmp = malloc(sizeof(tmp))))
		ft_handle_error("malloc failed\n");
	tmp->type = SP;
	if (!(sphere = malloc(sizeof(sphere))))
		ft_handle_error("malloc failed\n");
	sphere->pos = skip_atov(&str);
	sphere->pos.x *= -1;
	sphere->radius = skip_atof(&str);
	if (!*objs)
		*objs = tmp;
	return (1);
}

int		parse_tr(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_tr	*triangle;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = TR;
	if (!(triangle = malloc(sizeof(t_tr))) ||
				!(triangle->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	triangle->point0 = skip_atov(&str);
	triangle->point0.x *= -1;
	triangle->point1 = skip_atov(&str);
	triangle->point1.x *= -1;
	triangle->point2 = skip_atov(&str);
	triangle->point2.x *= -1;
	parse_mat(&str, triangle->mat_ptr);
	new->obj = triangle;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
}
