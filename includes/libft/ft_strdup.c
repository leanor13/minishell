/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:43:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/07 11:58:51 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char		*str_new;
	int			src_len;
	int			i;

	if (!src)
		return (NULL);
	src_len = ft_strlen(src);
	str_new = (char *)malloc(src_len * sizeof(char) + 1);
	if (str_new == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str_new[i] = src[i];
		i ++;
	}
	str_new[i] = '\0';
	return (str_new);
}
