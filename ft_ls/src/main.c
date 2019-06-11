/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:00:53 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 18:18:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	func_copy(char *argv[], t_ls *ls, char *tmp, int *m)
{
	int	k;

	k = 0;
	while (argv[m[0]][m[1]] != '\0' && argv[m[0]][m[1]] != ' ')
	{
		tmp[k] = argv[m[0]][m[1]];
		m[1]++;
		k++;
	}
	tmp[k] = '\0';
	if (ft_cheak_dir_or_file(ls, tmp) == -1)
		return (-1);
	ft_bzero(tmp, (size_t)k);
	return (1);
}

static int	get_arguments(int argc, char *argv[], t_ls *ls)
{
	int		m[2];
	char	tmp[256];

	m[0] = 1;
	while (m[0] < argc)
	{
		if (argv[m[0]][0] == '-')
			m[0]++;
		else
		{
			m[1] = 0;
			while (ISSPACE(argv[m[0]][m[1]]))
				m[1]++;
			if (argv[m[0]][m[1]] == '\0')
				return (ft_check_end_argument(ls, tmp));
			if (func_copy(argv, ls, tmp, m) == -1)
				return (-1);
			m[0]++;
		}
	}
	no_args(ls, argc);
	return (1);
}

int			main(int argc, char **argv)
{
	t_ls	*ls;
	int		i;

	i = -1;
	if (arg_checker(argc, argv) == -1)
	{
		ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
			"[file ...]\n");
		return (0);
	}
	ls = create_ls_main();
	ls->argv = argv;
	ls->flag = ft_get_bit(argc, argv);
	if (get_arguments(argc, argv, ls) != 1)
		return (ft_free_ls(&ls));
	get_contents(ls);
	ft_sort_by_ascii_all_dir_file(ls);
	if (R_FLAG)
	{
		while (ls->dir[++i] != NULL)
			ls_recoursive(ls->dir[i]->name, ls->flag);
	}
	else
		ls_base(ls);
	return (ft_free_ls(&ls));
}
