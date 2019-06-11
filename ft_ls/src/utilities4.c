/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:59:39 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 18:46:11 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				uid_guid_getter(t_ls_item *ls)
{
	struct stat		sb;
	struct passwd	*pw;
	struct group	*gr;

	if (lstat(ls->path, &sb) == -1)
	{
		perror("stat");
		return (1);
	}
	pw = getpwuid(sb.st_uid);
	gr = getgrgid(sb.st_gid);
	f_strcpy(ls->uid, pw->pw_name);
	f_strcpy(ls->guid, gr->gr_name);
	return (0);
}

long int		total(t_ls_item *ls)
{
	struct stat		sb;
	long long int	a;

	if (lstat(ls->path, &sb) == -1)
	{
		perror("stat");
		return (1);
	}
	a = (long)sb.st_blocks;
	return (a);
}

int				get_terminal_width(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

static void		ft_output_l_ext(t_ls *ls, int i)
{
	if (ls->dir[i] != ls->dir[0])
		ft_putchar('\n');
	if (ls->num_dir != 1 || ls->num_file > 0)
		ft_printf("%s:\n", ls->dir[i]->name);
	if (ft_strcmp(ls->dir[i]->path, "/") == 0)
		ls->dir[i]->st_blocks += 9;
	if (ls->dir[i]->cont[0] != NULL)
		ft_printf("total %lli\n", ls->dir[i]->st_blocks);
}

void			ft_output_l(t_ls *ls)
{
	int	mas[10];
	int	i;
	int	j;

	if (ls->file[0])
	{
		ft_max_len_attrb_file(ls, mas);
		j = 0;
		while (ls->file[j])
			ft_output_field_struct(ls->file[j++], mas);
	}
	i = -1;
	while (ls->dir[++i])
	{
		ft_output_l_ext(ls, i);
		ft_max_len_attributes(ls->dir[i], mas);
		j = 0;
		if (FLAG_R)
			reverse_ls_output(ls->dir[i]);
		while (ls->dir[i]->cont[j])
			ft_output_field_struct(ls->dir[i]->cont[j++], mas);
	}
}
