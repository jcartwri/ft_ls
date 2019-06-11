/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:08:38 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 14:16:48 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_attribute_dir(t_ls_item *ls, int *mas, int i, int j)
{
	if ((int)ft_strlen(ls->cont[i]->perms) > mas[j])
		mas[j] = (int)ft_strlen(ls->cont[i]->perms);
	j++;
	if ((int)ft_strlen(ft_itoa(ls->cont[i]->links)) > mas[j])
		mas[j] = (int)ft_strlen(ft_itoa(ls->cont[i]->links));
	j++;
	if ((int)ft_strlen(ls->cont[i]->uid) > mas[j])
		mas[j] = (int)ft_strlen(ls->cont[i]->uid);
	j++;
	if ((int)ft_strlen(ls->cont[i]->guid) > mas[j])
		mas[j] = (int)ft_strlen(ls->cont[i]->guid);
	j++;
	if ((int)ft_strlen(ft_itoa(ls->cont[i]->file_size)) > mas[j])
		mas[j] = (int)ft_strlen(ft_itoa(ls->cont[i]->file_size));
	j++;
	if ((int)ft_strlen(ls->cont[i]->month) > mas[j])
		mas[j] = (int)ft_strlen(ls->cont[i]->month);
	j++;
	if ((int)ft_strlen(ls->cont[i]->day) > mas[j])
		mas[j] = (int)ft_strlen(ls->cont[i]->day);
	j++;
	if ((int)ft_strlen(ls->cont[i]->time) > mas[j])
		mas[j] = (int)ft_strlen(ls->cont[i]->time);
}

static void	check_attribute_file(t_ls *ls, int *mas, int i, int j)
{
	if ((int)ft_strlen(ls->file[i]->perms) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->perms);
	j++;
	if ((int)ft_strlen(ft_itoa(ls->file[i]->links)) > mas[j])
		mas[j] = (int)ft_strlen(ft_itoa(ls->file[i]->links));
	j++;
	if ((int)ft_strlen(ls->file[i]->uid) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->uid);
	j++;
	if ((int)ft_strlen(ls->file[i]->guid) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->guid);
	j++;
	if ((int)ft_strlen(ft_itoa(ls->file[i]->file_size)) > mas[j])
		mas[j] = (int)ft_strlen(ft_itoa(ls->file[i]->file_size));
	j++;
	if ((int)ft_strlen(ls->file[i]->month) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->month);
	j++;
	if ((int)ft_strlen(ls->file[i]->day) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->day);
	j++;
	if ((int)ft_strlen(ls->file[i]->time) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->time);
}

void		ft_max_len_attrb_file(t_ls *ls, int *mas)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 10)
		mas[j++] = 0;
	while (ls->file[i])
	{
		j = 0;
		check_attribute_file(ls, mas, i, j);
		i++;
	}
}

void		ft_output_ls_right_side(char *str, int max)
{
	int i;

	i = (int)ft_strlen(str);
	while (i < max)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(str);
	ft_putchar(' ');
}

void		ft_max_len_attributes(t_ls_item *ls, int *mas)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 10)
		mas[j++] = 0;
	while (ls->cont[i])
	{
		j = 0;
		check_attribute_dir(ls, mas, i, j);
		i++;
	}
}
