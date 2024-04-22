/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:15:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 18:11:01 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: clean fd_out every time we run command with it

int	ft_env(char **env, char **args, int fd_out)
{
	int		i;

	i = 0;
	if (args && args[0] && args[1])
		return (EXIT_FAILURE);
	while (env && env[i] != NULL)
	{
		if (*env[i] != '\0' && *env[i] != '=' && ft_strchr(env[i], '='))
			ft_putstr_nl(env[i], fd_out);
		i ++;
	}
	return (EXIT_SUCCESS);
}
