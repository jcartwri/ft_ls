/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:26:35 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 14:40:11 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		bubble_sort_ls(t_ls_item *ls)
{
	int	sw;
	int	i;

	sw = 0;
	i = 0;
	if (ls == NULL)
		return ;
	while (ls->cont[i + 1] != NULL)
	{
		if (ft_strcmp(ls->cont[i]->name, ls->cont[i + 1]->name) > 0)
		{
			swap_ls_item(ls->cont[i], ls->cont[i + 1]);
			sw++;
		}
		i++;
		if (ls->cont[i + 1] == NULL && sw != 0)
		{
			sw = 0;
			i = 0;
		}
	}
}

static void	set_dir(t_ls *ls, int i, int j, struct dirent	*dir)
{
	ls->dir[i]->cont[j] = create_ls_item(0);
	f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
	f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
	path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name);
}

static void	set_file(t_ls *ls, int i, int j, struct dirent	*dir)
{
	ls->dir[i]->cont[j] = create_ls_item(0);
	f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
	f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
	path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name);
}

void		grab_ls(t_ls *ls, int i)
{
	int				j;
	DIR				*d;
	struct dirent	*dir;

	j = 0;
	d = opendir(ls->dir[i]->path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((A_FLAG) == 0 && dir->d_name[0] != '.')
			{
				set_dir(ls, i, j, dir);
				j++;
			}
			else if (A_FLAG)
			{
				set_file(ls, i, j, dir);
				j++;
			}
		}
		closedir(d);
	}
	ls->dir[i]->cont[j] = 0;
}

void		no_args(t_ls *ls, int argc)
{
	if (argc == 1)
	{
		ls->dir[(ls->num_dir)] = create_ls_item(1);
		f_strcpy(ls->dir[ls->num_dir]->name, ".");
		path_cpy(ls->dir[ls->num_dir]->path, ".");
		++(ls->num_dir);
	}
	else if (ls->dir[0] == NULL && ls->file[0] == NULL)
	{
		ls->dir[(ls->num_dir)] = create_ls_item(1);
		f_strcpy(ls->dir[ls->num_dir]->name, ".");
		path_cpy(ls->dir[ls->num_dir]->path, ".");
		++(ls->num_dir);
	}
}
