/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:26:26 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 20:29:44 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# define FALSE 0
# define TRUE 1

# include <stdio.h>
# include <math.h>
# include <float.h>
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"

# include "vectors.h"
# include "utils.h"
# include "objects.h"
# include "scene.h"
# include "ray.h"
# include "parser.h"
# include "debug.h"
# include "events.h"
# include "errors.h"
# include "bmp.h"
# include "free_functions.h"

typedef struct	s_quadratic_equation
{
	float	a;
	float	b;
	float	c;
	float	delta;
}				t_quad_eq;

#endif
