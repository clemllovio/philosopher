/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:05:21 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/01 11:59:50 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_strlen(char *str);

void	ft_putnbr(int n, int *count, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', count, fd);
		ft_putnbr(n * (-1), count, fd);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10, count, fd);
		ft_putnbr(n % 10, count, fd);
	}
	if (n >= 0 && n <= 9)
		ft_putchar(n + '0', count, fd);
}

void	ft_putnbr_base(unsigned long nbr, char *base, int *count, int fd)
{
	unsigned long	base_size;

	base_size = (unsigned long)ft_strlen(base);
	if (nbr < 0)
	{
		ft_putchar('-', count, fd);
		nbr = nbr * -1;
		ft_putnbr_base(nbr, base, count, fd);
	}
	else if (nbr / base_size)
	{
		ft_putnbr_base(nbr / base_size, base, count, fd);
		ft_putchar(base[nbr % base_size], count, fd);
	}
	else
		ft_putchar(base[nbr], count, fd);
}

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
