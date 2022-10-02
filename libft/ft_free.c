/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 09:57:27 by otoufah           #+#    #+#             */
/*   Updated: 2022/10/02 09:57:28 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_free(char *str)
{
	if (str)
		free(str);
}

void    ft_free_double(char **str)
{
	int i;

	i = -1;
	while (str && str[++i])
		ft_free(str[i]);
	if (str)
		free(str);
}
