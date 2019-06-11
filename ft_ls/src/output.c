/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:07:22 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 18:46:11 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_output_ls_left_side(char *str, int max)
{
	int	i;

	ft_putstr(str);
	i = (int)ft_strlen(str);
	while (i < max)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putchar(' ');
}

void		ft_output_field_struct(t_ls_item *ls, int *mas)
{
	int	i;

	i = 0;
	ft_output_ls_left_side(ls->perms, mas[i++]);
	if (mas[i - 1] != 11)
		ft_putchar(' ');
	ft_output_ls_right_side(ft_itoa(ls->links), mas[i++]);
	ft_output_ls_left_side(ls->uid, mas[i++]);
	ft_putchar(' ');
	ft_output_ls_left_side(ls->guid, mas[i++]);
	ft_putchar(' ');
	ft_output_ls_right_side(ft_itoa(ls->file_size), mas[i++]);
	ft_output_ls_left_side(ls->month, mas[i++]);
	ft_output_ls_right_side(ls->day, mas[i++]);
	ft_output_ls_right_side(ls->time, mas[i]);
	ft_putstr(ls->name);
	ft_putchar('\n');
}

static int	ft_priority(t_ls *ls)
{
	int	i;
	int	j;
	int	a;

	i = -1;
	a = 0;
	while (ls->argv[++i])
	{
		j = -1;
		while (ls->argv[i][++j] && ls->argv[i][0] == '-')
		{
			if (ls->argv[i][j] == 'l' && a == 0)
				a = 1;
			if (ls->argv[i][j] == '1' && a == 0)
				a = -1;
		}
	}
	if (a == 1)
		return (1);
	else
		return (-1);
}

void		ls_base(t_ls *ls)
{
	if (T_FLAG)
		ft_tsort(ls);
	if ((L_FLAG && !ONE_FLAG) || (L_FLAG && ONE_FLAG && ft_priority(ls) == -1))
	{
		perm_maker(ls);
		ft_output_l(ls);
	}
	else if (ONE_FLAG)
	{
		print_ls_one_flag(ls);
	}
	else
		ft_print_anti_l(ls);
}

void		ls_recoursive(char *path, int flag)
{
	t_ls		*ls;
	int			i;
	static int	fl;

	(INIT);
	ls->flag = flag;
	ls->dir[(ls->num_dir)] = create_ls_item(1);
	f_strcpy(ls->dir[ls->num_dir]->name, path);
	path_cpy(ls->dir[ls->num_dir]->path, path);
	++(ls->num_dir);
	get_contents(ls);
	ft_sort_by_ascii_all_dir_file(ls);
	ls->dir[0]->name[ft_strlen(ls->dir[0]->name) - 1] = '\0';
	fl != 0 ? ft_printf("\n%s:\n", ls->dir[0]->name) : fl++;
	if (ls->dir[0]->cont[0] == NULL)
		(FREE);
	ls_base(ls);
	while (ls->dir[0]->cont[i] != NULL)
	{
		if (is_dir(ls->dir[0]->cont[i]->path) == 1)
			ls_recoursive(ls->dir[0]->cont[i]->path, flag);
		i++;
	}
	ft_free_ls(&ls);
}
