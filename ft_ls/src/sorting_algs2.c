/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:52:47 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/13 14:53:22 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverse_ls_output(t_ls_item *ls)
{
	int	len;
	int	i;

	len = cont_len(ls);
	i = 0;
	while (i <= len)
	{
		swap_ls_item(ls->cont[i++], ls->cont[--len]);
		if (i >= len)
			break ;
	}
}
