/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:08:33 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 19:00:23 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_ls_cleaner_string(t_ls_item *ls)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		ls->time[i] = '\0';
		ls->day[i] = '\0';
		ls->month[i] = '\0';
	}
	i = 0;
	while (i < 256)
		ls->name[i++] = '\0';
	i = 0;
	while (i < 2048)
		ls->path[i++] = '\0';
	i = 0;
	while (i < 16)
		ls->perms[i++] = '\0';
	i = -1;
	while (++i < 64)
	{
		ls->uid[i] = '\0';
		ls->guid[i] = '\0';
	}
	ls->next = NULL;
}

void		free_ls_item(t_ls_item *ls)
{
	int	i;

	i = 0;
	if (!ls)
		return ;
	if (ls->cont != NULL)
	{
		while (ls->cont[i])
		{
			ft_ls_cleaner_string(ls->cont[i]);
			ft_memdel((void **)&(ls->cont[i++]));
		}
	}
	ft_ls_cleaner_string(ls);
	ft_memdel((void **)&(ls->cont));
}

int			ft_free_ls(t_ls **ls)
{
	int	i;

	i = 0;
	while ((*ls)->dir[i])
	{
		free_ls_item((*ls)->dir[i]);
		ft_memdel((void **)&((*ls)->dir[i]));
		(*ls)->dir[i++] = NULL;
	}
	ft_memdel((void **)&((*ls)->dir));
	i = 0;
	while ((*ls)->file[i])
	{
		free_ls_item((*ls)->file[i]);
		ft_memdel((void **)&((*ls)->file[i++]));
		(*ls)->file[i] = NULL;
	}
	ft_memdel((void **)&((*ls)->file));
	i = 0;
	while (i < 256)
		(*ls)->path[i++] = '\0';
	ft_memdel((void **)ls);
	return (0);
}

void		ft_print_rev_l(t_ls *ls, int j, int a, int len)
{
	if (ls->dir[j]->cont[0] != NULL)
	{
		if (FLAG_R)
			reverse_ls_output(ls->dir[j]);
		if (ls->dir[j]->cont[0] != NULL)
			ft_print_dir_file(ls->dir[j]->cont, a, len);
	}
}
