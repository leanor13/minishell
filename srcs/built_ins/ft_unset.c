/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 17:01:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_arg(char **env, char *arg)
{
	int		len_arg;
	char	**tmp;

	len_arg = ft_strlen(arg);
	while (*env)
	{
		if (ft_strncmp(*env, arg, len_arg) == 0 && *env[len_arg] == "=", 1)
		{
			tmp = env;
			while (*(env + 1) != NULL)
			{
				*env = *(env + 1);
				env ++;
			}
			*env = NULL;
			return ;
		}
		env ++;
	}
}

int	ft_unset(char **env, char **args, int fd_out)
{
	 if (*env == NULL || *args == NULL || **args == '\0')
        return (EXIT_SUCCESS);
	while (*args != NULL)
	{
		remove_arg(env, *args);
		args ++;
	}
	(void)fd_out;
	return (EXIT_SUCCESS);
}
