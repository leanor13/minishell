/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/31 15:01:34 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_delnode(t_env **env_list, int l)
{
    t_env *temp_prev = NULL;
    t_env *temp_del = NULL;
    t_env *current = *env_list;
    int i;

	i = 0;
	if (l == 0)
	{
		temp_del = current;
		*env_list = current->next;
		free(temp_del->var_name);
		free(temp_del->var_value);
		free(temp_del);
		return;
	}
	while (i < l && current)
	{
		temp_prev = current;
		current = current->next;
		i++;
	}
	temp_del = current;
	if (temp_prev != NULL)
		temp_prev->next = temp_del->next;
	temp_del->next = NULL;
	free(temp_del->var_name);
	free(temp_del->var_value);
	free(temp_del);
}

int	ft_unset(t_shell *shell, t_arg *command)
{
	int		i = 1;
	int		l = 0;
	int		k = 0;

	char 	**args = command->arguments;
	char	*find_command = NULL;
	t_env	*env_lst;

	if (args[i] == NULL)
		return (EXIT_SUCCESS);
	while(args[i])
	{
		l = 0;
		env_lst = shell->env_list;
		find_command = ft_strdup(args[i]);
		k = ft_strlen(find_command);
		while(shell->env_list)
		{
			if(!ft_strncmp(shell->env_list->var_name, find_command, k))
			{
				ft_delnode(&env_lst, l);
				break ;
			}
			l++;
			shell->env_list = shell->env_list->next;
		}
		free(find_command);
		i++;
	}
	shell->env_list = env_lst;
	update_env_2d(shell);
	return (EXIT_SUCCESS);
}
