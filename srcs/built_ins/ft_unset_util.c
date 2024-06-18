/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:30:59 by yioffe            #+#    #+#             */
/*   Updated: 2024/06/14 18:36:39 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_command(t_env ***env_list, int l, t_env **current)
{
	t_env	**temp_del;

	temp_del = NULL;
	if (l == 0)
	{
		temp_del = current;
		**env_list = (*current)->next;
		free((*temp_del)->var_name);
		free((*temp_del)->var_value);
		free((*temp_del));
		return (0);
	}
	return (1);
}

void	ft_first_element(int l, t_env **temp_prev, t_env **current)
{
	int	i;

	i = 0;
	while (i < l && (*current))
	{
		(*temp_prev) = (*current);
		(*current) = (*current)->next;
		i++;
	}
}

void	ft_delnode(t_env **env_list, int l)
{
	t_env	*temp_prev;
	t_env	*temp_del;
	t_env	*current;

	temp_prev = NULL;
	temp_del = NULL;
	current = *env_list;
	if (!new_command(&env_list, l, &current))
		return ;
	ft_first_element(l, &temp_prev, &current);
	temp_del = current;
	if (temp_prev != NULL)
		temp_prev->next = temp_del->next;
	temp_del->next = NULL;
	free(temp_del->var_name);
	free(temp_del->var_value);
	free(temp_del);
}
