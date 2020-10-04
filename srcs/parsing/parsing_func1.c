/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:49:02 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/04 13:35:53 by sabrugie         ###   ########.fr       */
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
	if ((sphere->radius = skip_atof(&str) / 2) < 0)
		ft_handle_error("Sphere : negative diameter\n");
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
	t_pl	*pl;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = PL;
	if (!(pl = malloc(sizeof(t_pl))) ||
			!(pl->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	printf("av : str = [%s]\n", str);
	pl->pos = skip_atov(&str);
	printf("[%f, %f, %f]\n", pl->pos.x, pl->pos.y, pl->pos.z);
	printf("ap : str = [%s]\n", str);
	pl->ori = skip_atov(&str);
	check_vector(&pl->ori, -1, 1);
	if (!pl->ori.x && !pl->ori.y && !pl->ori.z)
		ft_handle_error("Plane : wrong input\n");
	parse_mat(&str, pl->mat_ptr);
	new->obj = pl;
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
	t_sq	*sq;

	tmp = *objs;
	if (!(new = malloc(sizeof(t_obj))))
		ft_handle_error("malloc failed\n");
	new->type = SQ;
	if (!(sq = malloc(sizeof(t_sq))) ||
		!(sq->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	sq->pos = skip_atov(&str);
	sq->ori = skip_atov(&str);
	check_vector(&sq->ori, -1, 1);
	if ((!(sq->ori.x) && !(sq->ori.y) && !(sq->ori.z)) ||
		(sq->size = skip_atof(&str)) < 0)
		ft_handle_error("Square : wrong input\n");
	parse_mat(&str, sq->mat_ptr);
	new->obj = sq;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
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
	if (!(cy = malloc(sizeof(t_cy))) || (!cy->ori.x && !cy->ori.y && !cy->ori.z)
			|| !(cy->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error("malloc failed\n");
	cy->pos = skip_atov(&str);
	cy->ori = skip_atov(&str);
	check_vector(&cy->ori, -1, 1);
	if ((cy->diam = skip_atof(&str)) < 0 ||
			(cy->height = skip_atof(&str)) < 0)
		ft_handle_error("Cylinder : wrong input\n");
	parse_mat(&str, cy->mat_ptr);
	new->obj = cy;
	new->next = 0;
	if (!*objs)
		return ((*objs = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	return ((tmp->next = new) > 0);
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
