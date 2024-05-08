/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:07:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 11:53:08 by yioffe           ###   ########.fr       */
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

/* 
To hide from env
SHELL, BASH_VERSION, HISTFILE, HISTSIZE, PWD, OLDPWD, etc. 
These variables are considered internal to the shell and are not typically displayed when you run env.
Internal Shell Variables: Variables used internally by the shell for its operation, such as SHLVL (shell level), 
RANDOM (random number generator seed), LINENO (current line number), PS1 (primary shell prompt), 
PS2 (secondary shell prompt), IFS (internal field separator), etc. 
These variables are often not relevant to user programs and are not displayed by default.

 */

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
	int 	fd_out = STDOUT_FILENO;

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
			ft_putstr_nl("export: not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (ft_setenv(&env, var_name, var_value) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
