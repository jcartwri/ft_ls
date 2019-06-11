/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:00:28 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 16:04:55 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	perm_getter_ext(t_ls_item *ls, struct stat filestat,
		char *link_read, ssize_t bytes_read)
{
	if (S_ISLNK(filestat.st_mode))
	{
		bytes_read = readlink(ls->path, link_read, 254);
		link_read[bytes_read] = '\0';
		f_strcpy(ls->name, " -> ");
		f_strcpy(ls->name, link_read);
	}
	return (0);
}

int			perm_getter(t_ls_item *ls)
{
	struct stat		filestat;
	char			link_read[255];
	ssize_t			bytes_read;

	bytes_read = 0;
	if (lstat(ls->path, &filestat) < 0)
		return (1);
	ls->perms[0] = (char)((S_ISDIR(filestat.st_mode)) ? 'd' : '-');
	ls->perms[1] = (char)((filestat.st_mode & S_IRUSR) ? 'r' : '-');
	ls->perms[2] = (char)((filestat.st_mode & S_IWUSR) ? 'w' : '-');
	ls->perms[3] = (char)((filestat.st_mode & S_IXUSR) ? 'x' : '-');
	ls->perms[4] = (char)((filestat.st_mode & S_IRGRP) ? 'r' : '-');
	ls->perms[5] = (char)((filestat.st_mode & S_IWGRP) ? 'w' : '-');
	ls->perms[6] = (char)((filestat.st_mode & S_IXGRP) ? 'x' : '-');
	ls->perms[7] = (char)((filestat.st_mode & S_IROTH) ? 'r' : '-');
	ls->perms[8] = (char)((filestat.st_mode & S_IWOTH) ? 'w' : '-');
	ls->perms[9] = (char)((filestat.st_mode & S_ISVTX) ? 't' : '-');
	if (ls->perms[9] == '-')
		ls->perms[9] = (char)((filestat.st_mode & S_IXOTH) ? 'x' : '-');
	ls->perms[10] = extended_param(ls->path);
	if (ls->perms[10] != '@' && ls->perms[10] != '+')
		ls->perms[10] = '\0';
	ls->perms[11] = '\0';
	return (perm_getter_ext(ls, filestat, link_read, bytes_read));
}

int			ft_find_max_len(t_ls_item **ls)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (ls[i])
	{
		if ((int)ft_strlen(ls[i]->name) > a)
			a = ft_strlen(ls[i]->name);
		i++;
	}
	return (a);
}

void		get_contents(t_ls *ls)
{
	int	i;

	i = 0;
	if (ls->dir[0] != NULL)
	{
		while (ls->dir[i] != NULL)
		{
			grab_ls(ls, i);
			i++;
		}
	}
}

int			cont_len(t_ls_item *ls)
{
	int	i;

	i = 0;
	while (ls->cont[i])
		i++;
	return (i);
}
