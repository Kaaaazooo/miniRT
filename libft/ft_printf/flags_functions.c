/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:12:29 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/30 19:12:30 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		apply_field_width(t_modif *mod, int field_width)
{
	char	c;

	c = (mod->flags & ZERO && !(mod->flags & LEFT)) ? '0' : ' ';
	while (field_width-- > 0)
		check_assign(mod, c);
	return (1);
}

int		apply_prec(t_modif *mod, int len)
{
	while (mod->precision && mod->precision-- > len)
		check_assign(mod, '0');
	return (1);
}

int		apply_alt_form(int base, t_modif *mod)
{
	if (base == 16)
	{
		check_assign(mod, '0');
		check_assign(mod, 'x');
	}
	else if (base == -16)
	{
		check_assign(mod, '0');
		check_assign(mod, 'X');
	}
	return (1);
}

int		apply_sign(int base, t_modif *mod)
{
	if (mod->flags & ALT_FORM)
		if (!(apply_alt_form(base, mod)))
			return (0);
	if (mod->flags & MINUS)
		check_assign(mod, '-');
	else if (mod->flags & PLUS)
		check_assign(mod, '+');
	else if (mod->flags & SPACE && !(mod->flags & PLUS))
		check_assign(mod, ' ');
	return (1);
}

int		pre_flags(int base, t_modif *mod)
{
	if (mod->flags & ZERO)
		if (!(apply_sign(base, mod)))
			return (0);
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width)))
			return (0);
	if (!(mod->flags & ZERO))
		if (!(apply_sign(base, mod)))
			return (0);
	return (1);
}
