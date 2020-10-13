/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:51:07 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 20:40:32 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_r(t_coord **res, t_conf *conf, char *str)
{
	if (*res)
		ft_handle_error("Resolution : double definition\n", conf);
	if (!(*res = malloc(sizeof(t_coord))))
		ft_handle_error("Resolution : malloc failed\n", conf);
	(*res)->x = skip_atoi(&str, conf, "Resolution X");
	(*res)->y = skip_atoi(&str, conf, "Resolution Y");
	if ((*res)->x <= 0 || (*res)->y <= 0)
		ft_handle_error("Resolution : wrong input\n", conf);
	if ((*res)->x > 2560 || (*res)->y > 1440)
		ft_handle_error("Resolution : wrong input\n", conf);
	return (1);
}

int		parse_a(t_amb_l **amb_l, t_conf *conf, char *str)
{
	if (*amb_l)
		ft_handle_error("Ambient light : double definition\n", conf);
	if (!(*amb_l = malloc(sizeof(t_amb_l))))
		ft_handle_error("Ambient Light : malloc failed\n", conf);
	(*amb_l)->ratio = skip_atof(&str, conf, "Ambient Light Ratio");
	if ((*amb_l)->ratio > 1 || (*amb_l)->ratio < 0)
		ft_handle_error("Ambient light : ratio out of range\n", conf);
	if ((*amb_l)->ratio < 0.005)
		(*amb_l)->ratio = 0.005;
	(*amb_l)->rgb = skip_atov(&str, conf, "Ambient Light RGB");
	check_color(&(*amb_l)->rgb, "Ambient Light", conf);
	v_div(&(*amb_l)->rgb, &(*amb_l)->rgb, 255);
	(*amb_l)->ratio > 0.005 ? (*amb_l)->ratio += (1 - (*amb_l)->ratio) / 4 : 0;
	v_mul(&(*amb_l)->rgb, &(*amb_l)->rgb, (*amb_l)->ratio);
	return (1);
}

int		parse_c(t_cam **cam, t_conf *conf, char *str)
{
	t_cam	*tmp;
	t_cam	*new;

	tmp = *cam;
	if (!(new = malloc(sizeof(t_cam))))
		ft_handle_error("Camera : malloc failed\n", conf);
	new->pos = skip_atov(&str, conf, "Camera Position");
	new->vec = skip_atov(&str, conf, "Camera Direction");
	if (!new->vec.x && !new->vec.y && !new->vec.z)
		ft_handle_error("Camera : wrong input\n", conf);
	check_vector(&new->vec, conf, "Camera Direction");
	new->vec.y *= -1;
	new->vec.z *= -1;
	new_vec(&new->vup, 0, 1, 0);
	if ((new->fov = skip_atof(&str, conf, "Camera FOV")) < 0 || new->fov > 180)
		ft_handle_error("Camera : invalid FOV\n", conf);
	new->next = 0;
	new->bpp = 0;
	if (!*cam)
		return ((*cam = new) > 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int		parse_l(t_light **lights, t_conf *conf, char *str)
{
	t_light	*tmp;
	t_light	*new;

	tmp = *lights;
	if (!(new = malloc(sizeof(t_light))))
		ft_handle_error("Light : malloc failed\n", conf);
	new->pos = skip_atov(&str, conf, "Light Position");
	if ((new->ratio = skip_atof(&str, conf, "Light Ratio")) < 0 ||
														new->ratio > 1)
		ft_handle_error("Light : ratio out of range\n", conf);
	new->rgb = skip_atov(&str, conf, "Light RGB");
	check_color(&new->rgb, "Light", conf);
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

int		parse_mat(char **str, t_mat *mat_ptr, t_conf *conf, char *type)
{
	char	type_rgb[128];

	skip_spaces(str);
	if (**str)
		mat_ptr->attenuation = skip_atov(str, conf,
		ft_strcat(ft_strcpy(type_rgb, type), " RGB"));
	else
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : missing color\n", conf);
	}
	check_color(&mat_ptr->attenuation, type, conf);
	v_div(&mat_ptr->attenuation, &mat_ptr->attenuation, 255);
	skip_spaces(str);
	skip_spaces(str);
	if (**str)
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : invalid input at the end of line\n", conf);
	}
	return (1);
}
