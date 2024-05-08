/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 14:21:00 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO
/* 
while (curr != NULL)
	{
		shell->exit_code = 0;
		if (ft_strcmp(var_name, hidden[i]) == TRUE)
			;
		else if (var_content == NULL)
			printf("declare -x %s\n", var_name);
		else if (var_content != NULL && var_content[0] == ' '
			&& ft_strlen(var_content) == 1)
			printf("declare -x %s=\"\"\n", var_name);
		else
			printf("declare -x %s=\"%s\"\n", var_name, var_content);
		var -> next;
	}
 */


// add "" for var_value
// don't print = if no var_value

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

int	ft_export(t_shell *shell, t_arg *command)
{
	int		i = 1;
	char	*equal;
	char	*var_name;
	char	*var_value;
	char 	**env = shell->env_2d;
	char 	**args = command->args_parsed; 
	//int 	fd_out = STDOUT_FILENO;
	t_env	*env_lst = shell->env_list;

	if (args[i] == NULL)
	{
		i = 0;
		while (env_lst)
		{
			if (!env_lst->var_value)
				// TODO: this is not working - check why
				ft_printf("declare -x %s\n", env_lst->var_name);
			else if (ft_strcmp(env_lst->var_value, " ") == 0)
				ft_printf("declare -x %s=\"\"\n", env_lst->var_name);
			else
			{
				ft_printf("declare -x %s=\"", env_lst->var_name);
				ft_printf("%s\"\n", env_lst->var_value);
			}
			env_lst = env_lst->next;
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
			ft_putstr_nl("export: not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (ft_setenv(&env, var_name, var_value) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
