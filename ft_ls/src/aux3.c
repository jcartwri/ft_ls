/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:33:14 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 18:08:29 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_check_end_argument(t_ls *ls, char *tmp)
{
	f_strcpy(tmp, ".");
	if (ft_check_open_dir(tmp) == 1)
	{
		ls->dir[(ls->num_dir)] = create_ls_item(1);
		f_strcpy(ls->dir[ls->num_dir]->name, tmp);
		path_cpy(ls->dir[ls->num_dir]->path, tmp);
		++(ls->num_dir);
	}
	else
		return (-1);
	return (1);
}

static void	ft_fill_dir(t_ls *ls, char *tmp)
{
	ls->dir[(ls->num_dir)] = create_ls_item(1);
	f_strcpy(ls->dir[ls->num_dir]->name, tmp);
	path_cpy(ls->dir[ls->num_dir]->path, tmp);
	++(ls->num_dir);
}

static void	ft_fill_file(t_ls *ls, char *tmp)
{
	ls->file[(ls->num_file)] = create_ls_item(0);
	f_strcpy(ls->file[ls->num_file]->name, tmp);
	path_cpy(ls->file[ls->num_file]->path, tmp);
	++(ls->num_file);
}

int			ft_cheak_dir_or_file(t_ls *ls, char *tmp)
{
	if (is_dir(tmp) == 1)
	{
		if (ft_check_open_dir(tmp) == 1)
			ft_fill_dir(ls, tmp);
		else
			return (-1);
	}
	else
	{
		if (ft_check_open_file(tmp) == 1)
			ft_fill_file(ls, tmp);
		else
			return (-1);
	}
	return (1);
}
