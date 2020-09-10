/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:49:02 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:48:47 by sabrugie         ###   ########.fr       */
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
		ft_handle_error(ALLOC_FAIL);
	new->type = SP;
	if (!(sphere = malloc(sizeof(t_sp))) ||
				!(sphere->mat_ptr = malloc(sizeof(t_mat))))
		ft_handle_error(ALLOC_FAIL);
	sphere->pos = skip_atov(&str);
	sphere->radius = skip_atof(&str);
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
	t_sp	*sphere;

	tmp = *objs;
	while (tmp)
		tmp = tmp->next;
	if (!(tmp = malloc(sizeof(tmp))))
		ft_handle_error(ALLOC_FAIL);
	tmp->type = SP;
	if (!(sphere = malloc(sizeof(sphere))))
		ft_handle_error(ALLOC_FAIL);
	sphere->pos = skip_atov(&str);
	sphere->radius = skip_atof(&str);
	if (!*objs)
		*objs = tmp;
	return (1);
}

int		parse_sq(t_obj **objs, char *str)
{
	t_obj	*tmp;
	t_sp	*sphere;

	tmp = *objs;
	while (tmp)
		tmp = tmp->next;
	if (!(tmp = malloc(sizeof(tmp))))
		ft_handle_error(ALLOC_FAIL);
	tmp->type = SP;
	if (!(sphere = malloc(sizeof(sphere))))
		ft_handle_error(ALLOC_FAIL);
	sphere->pos = skip_atov(&str);
	sphere->radius = skip_atof(&str);
	if (!*objs)
		*objs = tmp;
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
		ft_handle_error(ALLOC_FAIL);
	tmp->type = SP;
	if (!(sphere = malloc(sizeof(sphere))))
		ft_handle_error(ALLOC_FAIL);
	sphere->pos = skip_atov(&str);
	sphere->radius = skip_atof(&str);
	if (!*objs)
		*objs = tmp;
	return (1);
}

int		parse_tr(t_obj **objs, char *str)
{
	t_obj		*tmp;
	t_sp	*sphere;

	tmp = *objs;
	while (tmp)
		tmp = tmp->next;
	if (!(tmp = malloc(sizeof(tmp))))
		ft_handle_error(ALLOC_FAIL);
	tmp->type = SP;
	if (!(sphere = malloc(sizeof(sphere))))
		ft_handle_error(ALLOC_FAIL);
	sphere->pos = skip_atov(&str);
	sphere->radius = skip_atof(&str);
	if (!*objs)
		*objs = tmp;
	return (1);
}
