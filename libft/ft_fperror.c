/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fperror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:47:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/12/25 01:36:14 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fperror(char *msg, int file, bool flush)
{
	if (file > -1 && file < 3 && msg)
	{
		ft_putstr_fd("Error:\n", file);
		ft_putstr_fd(msg, file);
		if (flush)
			ft_putchar_fd('\n', file);
	}
	return ;
}
