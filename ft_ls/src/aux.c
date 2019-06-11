/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:13:05 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 15:19:12 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_bitwise_shift(unsigned int flag, unsigned int a)
{
	flag = flag >> a;
	flag = flag + 1;
	flag = flag << a;
	return (flag);
}

int		ft_get_bit(int argc, char **argv)
{
	int		flag;
	char	*str;

	flag = 0;
	str = ft_get_str_options(argc, argv);
	if (check_on_consist(str, 'G') == 1)
		flag = ft_bitwise_shift(flag, 6);
	if (check_on_consist(str, '1') == 1)
		flag = ft_bitwise_shift(flag, 5);
	if (check_on_consist(str, 't') == 1)
		flag = ft_bitwise_shift(flag, 4);
	if (check_on_consist(str, 'r') == 1)
		flag = ft_bitwise_shift(flag, 3);
	if (check_on_consist(str, 'a') == 1)
		flag = ft_bitwise_shift(flag, 2);
	if (check_on_consist(str, 'R') == 1)
		flag = ft_bitwise_shift(flag, 1);
	if (check_on_consist(str, 'l') == 1)
		flag = ft_bitwise_shift(flag, 0);
	ft_memdel((void **)&str);
	return (flag);
}

void	f_strcpy(char *dst, const char *src)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (dst[j] != '\0')
		j++;
	while (src[++i])
		dst[j++] = src[i];
	dst[j] = '\0';
}

void	path_cpy(char *dst, const char *src)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (dst[j] != '\0')
		j++;
	while (src[++i])
		dst[j++] = src[i];
	dst[j] = '\0';
	if (is_dir(dst) && dst[j - 1] != '/')
	{
		dst[j] = '/';
		dst[j + 1] = '\0';
	}
}

int		check_on_consist(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (-1);
}
