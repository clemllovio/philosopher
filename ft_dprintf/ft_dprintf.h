/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cllovio <cllovio@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:05:45 by cllovio           #+#    #+#             */
/*   Updated: 2023/08/01 12:01:59 by cllovio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <unistd.h>

//ft_printf.c
int		ft_dprintf(int fd, const char *format, ...);

//ft_print_nbr.c
void	ft_check_args(char format, va_list args, int *count, int fd);

//ft_print_char.c
void	ft_putchar(int c, int *count, int fd);
void	ft_putstr(char *s, int *count, int fd);

//ft_print_nbr.c
void	ft_putnbr(int n, int *count, int fd);
void	ft_putnbr_base(unsigned long nbr, char *base, int *count, int fd);

#endif