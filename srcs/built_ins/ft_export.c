/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/23 12:41:29 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_varname(const char *var_name)
{
	if (!ft_isalpha(*var_name) && *var_name != '_')
		return (0);
	while (*var_name)
	{
		if (!ft_isalnum(*var_name) && *var_name != '_')
			return (0);
		var_name++;
	}
	return (1);
}

int	ft_export(char **env, char **args, int fd_out)
{
	int		i = 1;
	char	*equal;
	char	*var_name;
	char	*var_value;

	if (args[i] == NULL)
	{
		i = 0;
		while (env[i] != NULL)
		{
			if (*env[i] != '\0' && *env[i] != '=' && ft_strchr(env[i], '='))
				ft_putstr_nl(env[i], fd_out);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	while (args[i] != NULL)
	{
		if (args[i][0] == '\0')
		{
			i++;
			continue;
		}
		equal = ft_strchr(args[i], '=');
		var_name = args[i];
		if (equal != NULL)
		{
			*equal = '\0';
			var_value = equal + 1;
		}
		else
			var_value = ft_getenv(env, var_name);
		if (!is_valid_varname(var_name))
		{
			ft_putstr_nl("export: not a valid identifier", fd_out);
			return (EXIT_FAILURE);
		}
		if (ft_setenv(&env, var_name, var_value) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
