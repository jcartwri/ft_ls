/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:08:46 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 18:55:32 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_ls_one_flag(t_ls *ls)
{
	int i;
	int j;

	i = -1;
	while (ls->dir[++i] != NULL)
	{
		if (ls->dir[i] != ls->dir[0])
			ft_putchar('\n');
		if (ls->num_dir != 1 || ls->num_file > 0)
			ft_printf("%s:\n", ls->dir[i]->name);
		j = 0;
		bubble_sort_ls(ls->dir[i]);
		if (FLAG_R)
			reverse_ls_output(ls->dir[j]);
		while (ls->dir[i]->cont[j] != NULL)
			ft_putendl(ls->dir[i]->cont[j++]->name);
	}
	i = -1;
	bubble_sort_ls(ls->file[0]);
	while (ls->file[++i] != NULL)
		ft_putendl(ls->file[i]->name);
}

static void	print_plus_sp(t_ls_item **ls, int i, int a)
{
	int	m;
	int	j;

	m = a - (int)ft_strlen(ls[i]->name);
	ft_putstr(ls[i]->name);
	if (ls[i + 1] != NULL)
	{
		j = -1;
		while (++j < m)
			ft_putchar(' ');
	}
}

void		ft_body_print(t_ls_item **ls, int a, int len, int row)
{
	int m[3];

	m[2] = 0;
	m[1] = 1;
	m[0] = 0;
	while (m[1] <= row)
	{
		if (m[2] == row)
		{
			print_plus_sp(ls, m[0], a);
			m[2] = 0;
		}
		else
			(ADD);
		if (m[0] == len)
		{
			ft_putchar('\n');
			m[0] = 0;
			m[0] += m[1];
			m[1]++;
			if (m[1] <= row)
				print_plus_sp(ls, m[0], a);
			m[2] = 0;
		}
	}
}

void		ft_print_dir_file(t_ls_item **ls, int a, int len)
{
	int	i;
	int	ws;
	int	col;
	int	row;

	i = 0;
	ws = get_terminal_width();
	ws == 0 ? ws = 100 : 0;
	col = ws / a;
	row = len / col;
	if (row * col < len)
		row++;
	print_plus_sp(ls, i, a);
	ft_body_print(ls, a, len, row);
}

int			ft_print_anti_l(t_ls *ls)
{
	int	a;
	int	j;
	int	len;

	j = 0;
	if (ls->file[j])
	{
		a = (ft_find_max_len(ls->file) / 8 + 1) * 8;
		ft_print_dir_file(ls->file, a, ls->num_file);
		if (ls->dir[0] != NULL)
			ft_putchar('\n');
	}
	j = -1;
	while (ls->dir[++j])
	{
		if (ls->dir[j] != ls->dir[0])
			ft_putchar('\n');
		if (ls->num_dir != 1 || ls->num_file > 0)
			ft_printf("%s:\n", ls->dir[j]->name);
		len = cont_len(ls->dir[j]);
		a = (ft_find_max_len(ls->dir[j]->cont) / 8 + 1) * 8;
		bubble_sort_ls(ls->dir[j]);
		ft_print_rev_l(ls, j, a, len);
	}
	return (0);
}
