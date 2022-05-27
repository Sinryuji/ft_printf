/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:59:18 by hyeongki          #+#    #+#             */
/*   Updated: 2022/05/27 13:19:47 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	select_specifier(char spec, va_list *ap, t_flag *flag)
{
	int	ret;

	ret = 0;
	if (spec == 'c')
		ret = ft_printf_char(ap, flag);
	else if (spec == 's')
		ret = ft_printf_string(ap, flag);
	else if (spec == 'p')
		ret = ft_printf_pointer(ap, flag);
	else if (spec == 'd' || spec == 'i')
		ret = ft_printf_decimal(ap, flag);
	else if (spec == 'u')
		ret = ft_printf_unsigned(ap, flag);
	else if (spec == 'x' || spec == 'X')
		ret = ft_printf_hexa(ap, spec, flag);
	else if (spec == '%')
		ret = ft_printf_percent(flag);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;
	t_flag	*flag;

	va_start(ap, format);
	ret = 0;
	flag = malloc(sizeof(t_flag));
	ft_memset(flag, 0, sizeof(t_flag));
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			prework_width(flag, &format);
			prework_precision(flag, &format);
			ret += select_specifier(*format, &ap, flag);
		}
		else
			ret += write(1, format, 1);
		format++;
	}		
	va_end(ap);
	free(flag);
	return (ret);
}

//int	main()
//{
//	char	*str = "asdf";
//	printf("%d\n", printf("printf :%10s\n", str));
//	printf("%d\n", ft_printf("ft_printf :%10s\n", str));
//}
