/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 18:57:31 by thuy-ngu         ###   ########.fr       */
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

void	ft_changenode(t_env **env_list, char *copy_value)
{
	free((*env_list)->var_value);
	(*env_list)->var_value = NULL;
	(*env_list)->var_value = ft_strdup(copy_value);
}

int	no_export(t_shell *shell, char **args, t_env *env_lst_start )
{
	env_lst_start = shell->env_list;
	if (args[0] == NULL)
	{
		while (shell->env_list)
		{
			if (!shell->env_list->var_value)
				ft_printf("declare -x %s\n", shell->env_list->var_name);
			else if (ft_strcmp(shell->env_list->var_value, " ") == 0)
				ft_printf("declare -x %s=\"\"\n", shell->env_list->var_name);
			else
			{
				ft_printf("declare -x %s=\"", shell->env_list->var_name);
				ft_printf("%s\"\n", shell->env_list->var_value);
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = env_lst_start;
		return (0);
	}
	return (1);
}

int	ft_export(t_shell *shell, t_arg *command)
{
	int		i;
	char	**args;
	char	*equal_sign;
	int		sign;
	t_env	*env_lst_start;

	env_lst_start = shell->env_list;
	i = 1;
	args = command->arguments;
	equal_sign = NULL;
	sign = 0;
	if(!no_export(shell, args, env_lst_start))
		return (EXIT_SUCCESS);
	while (args[i] != NULL) 
	{
		equal_sign = strchr(args[i], '=');
		if (equal_sign)
		{
			size_t name_len = equal_sign - args[i];
			char *var_name = ft_strndup(args[i], name_len);
			char *var_name_test = ft_strdup(var_name);
			if(!is_valid_varname(var_name_test))
			{
				ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
				free(var_name);
				free(var_name_test);
				return(EXIT_FAILURE);
			}
			free(var_name_test);
			char *var_value = ft_strdup(equal_sign + 1);
			int k = ft_strlen(var_name);
			t_env *env_lst_start = shell->env_list;
			while(shell->env_list)
			{
				if(!ft_strncmp(shell->env_list->var_name, var_name, k))
				{
					ft_changenode(&shell->env_list, var_value);
					free(var_name);	
					free(var_value);
					sign = 1;
					break;
				}
				shell->env_list = shell->env_list->next;
			}
			shell->env_list = env_lst_start;
			if (sign == 0)
			{
				add_back_env(&shell->env_list, var_name, var_value);
				free(var_name);	
				free(var_value);
			}
		}
		else
		{
			if (!is_valid_varname(args[i]))
			{
				ft_putstr_nl("exit: not a valid identifier", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			size_t name_len = ft_strlen(args[i]);
			char *var_name = ft_strndup(args[i], name_len);
			int k = ft_strlen(var_name);
			t_env *env_lst_start = shell->env_list;
			while (shell->env_list)
			{
				if (!ft_strncmp(shell->env_list->var_name, var_name, k))
				{
					free(var_name);
					sign = 1;
					break ;
				}
				shell->env_list = shell->env_list->next;
			}
			shell->env_list = env_lst_start;
			if (sign == 0)
			{
				add_back_env(&shell->env_list, args[i], NULL);
				free(var_name);
			}
		}
		i++;
	}
	if (equal_sign)
		shell->env_list = env_lst_start;
	update_env_2d(shell);
	return (EXIT_SUCCESS);
}
