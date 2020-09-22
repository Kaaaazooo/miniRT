/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 09:07:06 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/22 09:13:30 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "mini_rt.h"
# include "utils.h"
# include "material.h"
# include "ray.h"

# define SP 1
# define PL 2
# define SQ 4
# define CY 8
# define TR 16
# define R 32
# define A 64
# define C 128
# define L 256

typedef struct	s_sphere
{
	t_vec					pos;
	float					radius;
	struct s_mat			*mat_ptr;
}				t_sp;

typedef struct	s_plane
{
	t_vec			pos;
	t_vec			ori;
	struct s_mat	*mat_ptr;
}				t_pl;

typedef struct	s_square
{
	t_vec			pos;
	t_vec			ori;
	float			size;
	struct s_mat	*mat_ptr;
}				t_sq;

typedef struct	s_cylinder
{
	t_vec			pos;
	t_vec			ori;
	float			diam;
	float			height;
	t_vec			rgb;
}				t_cy;

typedef struct	s_triangle
{
	t_vec			point0;
	t_vec			point1;
	t_vec			point2;
	t_vec			ori;
	struct s_mat	*mat_ptr;
}				t_tr;

typedef struct	s_light
{
	t_vec					pos;
	float					ratio;
	t_vec					rgb;
	struct s_light			*next;
}				t_light;

typedef t_bool	(*t_func)(struct s_sphere *sp, t_hit *hit);

typedef struct	s_object_list
{
	char					type;
	void					*obj;
	struct s_object_list	*next;
	t_func					f;
}				t_obj;

t_bool			hit_any(t_obj *objs, t_hit *hit, t_hit_rec *rec);
t_bool			hit_sphere(t_sp *sp, t_hit *hit, t_hit_rec *rec);
t_bool			hit_plane(t_pl *pl, t_hit *hit, t_hit_rec *rec);
t_bool			hit_square(t_sq *sq, t_hit *hit, t_hit_rec *rec);
t_bool			hit_triangle(t_tr *tr, t_hit *hit, t_hit_rec *rec);
t_obj			*new_obj(char type, void *obj, t_obj *next, t_func f);
t_sp			*new_sphere(t_sp *dest, t_vec *v1, float radius);
t_vec			*rand_unit_sp(t_vec *dest, t_xor *seed);
#endif
