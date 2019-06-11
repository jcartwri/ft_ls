/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:43:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/05 15:20:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				is_dir(char *path)
{
	struct stat filestat;

	if (path == NULL)
		return (-1);
	if (lstat(path, &filestat) < 0)
		return (-1);
	return ((S_ISDIR(filestat.st_mode)) ? 1 : 0);
}

void			swap_ls_item(t_ls_item *a, t_ls_item *b)
{
	t_ls_item	c;

	c = *a;
	*a = *b;
	*b = c;
}

char			extended_param(char *filename)
{
	acl_t		acl;
	acl_entry_t dummy;
	ssize_t		xattr;
	char		chr;

	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		chr = '@';
	else if (acl != NULL)
		chr = '+';
	else
		chr = ' ';
	return (chr);
}

void			f_strcpy_time(t_ls_item *ls, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] && src[i] != ' ')
		ls->month[j++] = src[i++];
	ls->month[j] = '\0';
	while (src[i] && src[i] == ' ')
		i++;
	j = 0;
	while (src[i] && src[i] != ' ')
		ls->day[j++] = src[i++];
	ls->day[j] = '\0';
	while (src[i] && src[i] == ' ')
		i++;
	j = 0;
	while (src[i])
		ls->time[j++] = src[i++];
	ls->time[j] = '\0';
}

int				time_getter(t_ls_item *ls)
{
	char		time_str[64];
	time_t		now;
	struct stat	sb;
	struct tm	tmfile;
	struct tm	tmnow;

	now = time(NULL);
	if (lstat(ls->path, &sb) == -1)
	{
		perror("stat");
		return (1);
	}
	localtime_r(&sb.st_mtime, &tmfile);
	localtime_r(&now, &tmnow);
	if (tmfile.tm_year == tmnow.tm_year)
	{
		strftime(time_str, sizeof(time_str), "%b %e %H:%M", &tmfile);
		f_strcpy_time(ls, time_str);
	}
	else
	{
		strftime(time_str, sizeof(time_str), "%b %e  %Y", &tmfile);
		f_strcpy_time(ls, time_str);
	}
	return (0);
}
