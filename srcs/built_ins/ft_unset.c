/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 18:44:33 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_unset(t_shell *shell, t_env **env_lst, int k, char *find_command)
{
	int	l;

	l = 0;
	if (!shell->env_list)
		return ;
	while (shell->env_list)
	{
		if (!ft_strncmp(shell->env_list->var_name, find_command, k))
		{
			ft_delnode(env_lst, l);
			break ;
		}
		l++;
		shell->env_list = shell->env_list->next;
	}
}

t_env	*ft_findcommand(t_env *env_lst, t_shell *shell, char **args)
{
	char	*find_command;
	int		i;
	int		k;

	i = 1;
	find_command = NULL;
	while (args[i])
	{
		env_lst = shell->env_list;
		find_command = ft_strdup(args[i]);
		k = ft_strlen(find_command);
		find_unset(shell, &env_lst, k, find_command);
		free(find_command);
		i++;
	}
	return (env_lst);
}

int	ft_unset(t_shell *shell, t_arg *command)
{
	char	**args;
	t_env	*env_lst;

	env_lst = NULL;
	args = command->arguments;
	if (args[0] == NULL)
		return (EXIT_SUCCESS);
	env_lst = ft_findcommand(env_lst, shell, args);
	shell->env_list = env_lst;
	update_env_2d(shell);
	return (EXIT_SUCCESS);
}
