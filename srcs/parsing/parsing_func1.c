/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:49:02 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/30 19:07:32 by sabrugie         ###   ########.fr       */
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
	plane->ori = skip_atov(&str);
	if (!plane->ori.x && !plane->ori.y && !plane->ori.z)
		ft_handle_error("Wrong input\n");
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
	square->ori = skip_atov(&str);
	if (!square->ori.x && !square->ori.y && !square->ori.z)
		ft_handle_error("Wrong input\n");
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
	t_obj	*new;
	t_cy	*cy;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = CY;
	if (!(cy = malloc(sizeof(t_cy))) ||
				!(cy->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	cy->pos = skip_atov(&str);
	cy->ori = skip_atov(&str);
	cy->diam = skip_atof(&str);
	cy->height = skip_atof(&str);
	parse_mat(&str, cy->mat_ptr);
	new->obj = cy;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (!cy->ori.x && !cy->ori.y && !cy->ori.z ?
				ft_handle_error("Wrong input\n") : 1);
}

int		parse_tr(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_tr	*tr;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = TR;
	if (!(tr = malloc(sizeof(t_tr))) ||
				!(tr->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	tr->point0 = skip_atov(&str);
	tr->point1 = skip_atov(&str);
	tr->point2 = skip_atov(&str);
	parse_mat(&str, tr->mat_ptr);
	new->obj = tr;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
}
