/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:26:15 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/21 13:28:48 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_check_args(char format, va_list args, int *count, int fd)
{
	if (format == 'c')
		ft_putchar(va_arg(args, int), count, fd);
	else if (format == 's')
		ft_putstr(va_arg(args, char *), count, fd);
	else if (format == 'p')
	{
		ft_putstr("0x", count, fd);
		ft_putnbr_base(va_arg(args, long long unsigned int), \
		"0123456789abcdef", count, fd);
	}
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), count, fd);
	else if (format == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789", count, fd);
	else if (format == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), \
		"0123456789abcdef", count, fd);
	else if (format == 'X')
		ft_putnbr_base(va_arg(args, unsigned int),
			"0123456789ABCDEF", count, fd);
	else if (format == '%')
		ft_putchar('%', count, fd);
}
