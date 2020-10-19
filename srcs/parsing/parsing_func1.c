/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:49:02 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 21:07:37 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sp(t_obj **objs, t_conf *conf, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_sp	*sphere;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("Sphere : malloc failed\n", conf);
	new->type = SP;
	if (!(sphere = malloc(sizeof(t_sp))) ||
				!(sphere->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("Sphere : malloc failed\n", conf);
	sphere->pos = skip_atov(&str, conf, "Sphere Position");
	if ((sphere->radius = skip_atof(&str, conf, "Sphere Radius") / 2) < 0)
		ft_handle_error("Sphere : not a valid diameter\n", conf);
	parse_mat(&str, sphere->mat_ptr, conf, "Sphere");
	new->obj = sphere;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_pl(t_obj **objs, t_conf *conf, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_pl	*pl;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("Plane : malloc failed\n", conf);
	new->type = PL;
	if (!(pl = malloc(sizeof(t_pl))) ||
			!(pl->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("Plane : malloc failed\n", conf);
	pl->pos = skip_atov(&str, conf, "Plane Position");
	pl->ori = skip_atov(&str, conf, "Plane Orientation");
	check_vector(&pl->ori, conf, "Plane Orientation");
	if (!pl->ori.x && !pl->ori.y && !pl->ori.z)
		ft_handle_error("Plane : wrong input\n", conf);
	parse_mat(&str, pl->mat_ptr, conf, "Plane");
	new->obj = pl;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_sq(t_obj **objs, t_conf *conf, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_sq	*sq;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("Square : malloc failed\n", conf);
	new->type = SQ;
	if (!(sq = malloc(sizeof(t_sq))) ||
		!(sq->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("Square : malloc failed\n", conf);
	sq->pos = skip_atov(&str, conf, "Square Position");
	sq->ori = skip_atov(&str, conf, "Square Orientation");
	check_vector(&sq->ori, conf, "Square Orientation");
	if ((!(sq->ori.x) && !(sq->ori.y) && !(sq->ori.z)) ||
		(sq->size = skip_atof(&str, conf, "Square")) < 0)
		ft_handle_error("Square : wrong input\n", conf);
	parse_mat(&str, sq->mat_ptr, conf, "Square");
	new->obj = sq;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
}

int		parse_cy(t_obj **objs, t_conf *conf, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_cy	*cy;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("Cylinder : malloc failed\n", conf);
	new->type = CY;
	if (!(cy = malloc(sizeof(t_cy)))
			|| !(cy->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("Cylinder : malloc failed\n", conf);
	cy->pos = skip_atov(&str, conf, "Cylinder Position");
	cy->ori = skip_atov(&str, conf, "Cylinder Orientation");
	check_vector(&cy->ori, conf, "Cylinder Orientation");
	if ((cy->diam = skip_atof(&str, conf, "Cylinder Diameter")) < 0 ||
			(cy->height = skip_atof(&str, conf, "Cylinder Height")) < 0)
		ft_handle_error("Cylinder : wrong input\n", conf);
	parse_mat(&str, cy->mat_ptr, conf, "Cylinder");
	new->obj = cy;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
}

int		parse_tr(t_obj **objs, t_conf *conf, char *str)
{
	t_obj	*tmp;
	t_obj	*new;
	t_tr	*tr;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("Triangle : malloc failed\n", conf);
	new->type = TR;
	if (!(tr = malloc(sizeof(t_tr))) ||
				!(tr->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("Triangle : malloc failed\n", conf);
	tr->point0 = skip_atov(&str, conf, "Triangle Point 0");
	tr->point1 = skip_atov(&str, conf, "Triangle Point 1");
	tr->point2 = skip_atov(&str, conf, "Triangle Point 2");
	parse_mat(&str, tr->mat_ptr, conf, "Triangle");
	new->obj = tr;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
}
