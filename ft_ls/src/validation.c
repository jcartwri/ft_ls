/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:18:33 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 18:08:29 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			arg_checker(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] != 'l' && argv[i][j] != 'R' && argv[i][j] != 'a'
				&& argv[i][j] != 'r' && argv[i][j] != 't' && argv[i][j] != '1'
				&& argv[i][j] != 'G')
			{
				ft_putstr("ls: illegal option -- ");
				ft_putchar(argv[i][j]);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_get_count_flags(int argc, char **argv)
{
	int	a;
	int	i;
	int	j;

	i = 1;
	a = 0;
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			a++;
			j++;
		}
		i++;
	}
	return (a);
}

char		*ft_get_str_options(int argc, char **argv)
{
	int		i;
	int		j;
	int		a;
	char	*str;

	i = 1;
	a = ft_get_count_flags(argc, argv);
	str = ft_memalloc(sizeof(char) * a);
	str[a] = '\0';
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		a = 0;
		while (argv[i][j])
		{
			if (check_on_consist(str, argv[i][j]) == -1)
			{
				str[a++] = argv[i][j];
				str[a] = '\0';
			}
			j++;
		}
		i++;
	}
	return (str);
}

int			ft_check_open_dir(char *tmp)
{
	DIR	*n;

	if ((n = opendir(tmp)) == NULL)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", tmp);
		closedir(n);
		return (-1);
	}
	closedir(n);
	return (1);
}

int			ft_check_open_file(char *tmp)
{
	struct stat		filestat;

	if (fopen(tmp, "r") == NULL)
	{
		if (lstat(tmp, &filestat) < 0)
		{
			ft_printf("ft_ls: %s: No such file or directory\n", tmp);
			return (-1);
		}
	}
	return (1);
}
