/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/19 17:58:13 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO check it with real minishell

void	remove_arg(char **env, char *arg)
{
	int		len_arg;
	char	**tmp;

	len_arg = ft_strlen(arg);
	while (*env)
	{
		if (ft_strncmp(*env, arg, len_arg) == 0 && (*env)[len_arg] == '=')
		{
			tmp = env;
			while (*(tmp + 1) != NULL)
            {
                *tmp = *(tmp + 1);
                tmp++;
            }
            *tmp = NULL;
            return;
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
