/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/09 15:24:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO check it with real minishell

void	remove_arg(char **env, char *arg)
{
	int		len_arg;
	char	**tmp;

	if (ft_getenv(env, arg) == NULL)
        return ;
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

int	ft_unset(t_shell *shell, t_arg *command)
{
	char 	**env = shell->env_2d;
	char 	**args = command->args_doublechar; 
	
	if (*env == NULL || *args == NULL || **args == '\0')
        return (EXIT_SUCCESS);
	while (*args != NULL)
	{
		remove_arg(env, *args);
		args ++;
	}
	return (EXIT_SUCCESS);
}
