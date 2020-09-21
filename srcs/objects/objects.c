/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 11:40:37 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/17 10:12:29 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_objs(t_obj *objs)
{
	t_obj	*tmp;

	while (objs)
	{
		tmp = objs->next;
		free(objs);
		objs = tmp;
	}
}

t_obj	*new_obj(char type, void *object, t_obj *next, t_func f)
{
	t_obj	*obj;

	if (!(obj = malloc(sizeof(obj))))
		ft_handle_error("malloc failed\n");
	obj->type = type;
	obj->obj = object;
	obj->next = next;
	obj->f = f;
	return (obj);
}
