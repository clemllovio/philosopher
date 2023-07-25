/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:35:00 by cllovio           #+#    #+#             */
/*   Updated: 2023/07/21 13:15:57 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i] && count != -1)
	{
		if (format[i] == '%')
		{
			i++;
			ft_check_args(format[i], args, &count, fd);
			if (!format[i])
				break ;
		}
		else
			ft_putchar(format[i], &count, fd);
		i++;
	}
	va_end(args);
	return (count);
}
