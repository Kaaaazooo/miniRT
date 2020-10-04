/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:51:07 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/04 12:28:43 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_r(t_coord **res, char *str)
{
	if (!(*res = malloc(sizeof(t_coord))))
		ft_handle_error("malloc failed\n");
	(*res)->x = skip_atoi(&str);
	(*res)->y = skip_atoi(&str);
	if ((*res)->x <= 0 || (*res)->y <= 0)
		ft_handle_error("Resolution : wrong input\n");
	if ((*res)->x > 2560 || (*res)->y > 1440)
		ft_handle_error("Resolution : wrong input\n");
	return (1);
}

int		parse_a(t_amb_l **amb_l, char *str)
{
	if (!(*amb_l = malloc(sizeof(t_amb_l))))
		ft_handle_error("malloc failed\n");
	(*amb_l)->ratio = skip_atof(&str);
	if ((*amb_l)->ratio > 1 || (*amb_l)->ratio < 0)
		ft_handle_error("Ambient light : ratio out of range\n");
	if ((*amb_l)->ratio < 0.005)
		(*amb_l)->ratio = 0.005;
	(*amb_l)->rgb = skip_atov(&str);
	check_color(&(*amb_l)->rgb);
	v_div(&(*amb_l)->rgb, &(*amb_l)->rgb, 255);
	(*amb_l)->ratio > 0.005 ? (*amb_l)->ratio += (1 - (*amb_l)->ratio) / 4 : 0;
	v_mul(&(*amb_l)->rgb, &(*amb_l)->rgb, (*amb_l)->ratio);
	return (1);
}

int		parse_c(t_cam **cam, char *str)
{
	t_cam	*tmp;
	t_cam	*new;

	tmp = *cam;
	if (!(new = malloc(sizeof(t_cam))))
		ft_handle_error("malloc failed\n");
	new->pos = skip_atov(&str);
	new->vec = skip_atov(&str);
	if (!new->vec.x && !new->vec.y && !new->vec.z)
		ft_handle_error("Camera : wrong input\n");
	check_vector(&new->vec, -1, 1);
	new->vec.y *= -1;
	new->vec.z *= -1;
	new_vec(&new->vup, 0, 1, 0);
	if ((new->fov = skip_atof(&str)) < 0 || new->fov > 180)
		ft_handle_error("Camera : invalid FOV\n");
	new->next = 0;
	if (!*cam)
		return ((*cam = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_l(t_light **lights, char *str)
{
	t_light	*tmp;
	t_light	*new;

	tmp = *lights;
	if (!(new = malloc(sizeof(t_light))))
		ft_handle_error("malloc failed\n");
	new->pos = skip_atov(&str);
	if ((new->ratio = skip_atof(&str)) < 0 || new->ratio > 1)
		ft_handle_error("Light : ratio out of range\n");
	new->rgb = skip_atov(&str);
	check_color(&new->rgb);
	v_div(&new->rgb, &new->rgb, 255);
	new->next = 0;
	if (!*lights)
	{
		*lights = new;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_mat(char **str, t_mat *mat_ptr)
{
	skip_spaces(str);
	if (**str)
		mat_ptr->attenuation = skip_atov(str);
	else
		ft_handle_error("Object : missing color\n");
	check_color(&mat_ptr->attenuation);
	v_div(&mat_ptr->attenuation, &mat_ptr->attenuation, 255);
	skip_spaces(str);
	if ((**str == 0 || (**str == 'L' && *((*str + 1)) == 'A')))
		mat_ptr->type = LA;
	else if (**str == 'M' && *((*str + 1)) == 'E')
		mat_ptr->type = ME;
	else
		ft_handle_error("Wrong input\n");
	(*str) += **str ? 2 : 0;
	skip_spaces(str);
	if (**str)
		ft_handle_error("Wrong input\n");
	return (1);
}
