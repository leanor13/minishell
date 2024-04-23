/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:54 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/23 12:54:23 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char **env, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

int	ft_setenv(char ***env, const char *name, const char *value)
{
    int		i = 0;
    char	*new_entry;
    char	**new_env;
    int		j;

    new_entry = ft_strjoin(name, "=");
    new_entry = ft_strjoin(new_entry, value);
    if (ft_getenv(*env, name) != NULL)
    {
        i = 0;
        while ((*env)[i])
        {
            if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0 && (*env)[i][ft_strlen(name)] == '=')
            {
                free((*env)[i]);
                (*env)[i] = new_entry;
                return (EXIT_SUCCESS);
            }
            i++;
        }
    }
    new_env = (char **)malloc((i + 2) * sizeof(char *));
    j = 0;
    while ((*env)[j])
    {
        new_env[j] = (*env)[j];
        j++;
    }
    new_env[i] = new_entry;
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
    return (EXIT_SUCCESS);
}

int	ft_cd(char **env, char **args, int fd_out)
{
	char	*pwd;
	char	*path;
	char	*new_pwd;

	pwd = ft_getenv(env, "PWD");
	(void)fd_out;
	if (pwd == NULL)
		return (ft_putstr_nl("cd: failed to get current directory", STDERR_FILENO),
			EXIT_FAILURE);
	if (args && args[1] && args[2])
		return (ft_putstr_nl("cd: too many arguments", STDERR_FILENO), EXIT_FAILURE);
	if (!args[1])
	{
		path = ft_getenv(env, "HOME");
		if (!path)
			return (ft_putstr_nl("cd: HOME not set", STDERR_FILENO), EXIT_FAILURE);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
		return (perror("cd path"), EXIT_FAILURE);
	if (ft_setenv(&env, "OLDPWD", pwd) != EXIT_SUCCESS)
		return (ft_putstr_nl("cd: failed to set OLDPWD", STDERR_FILENO), EXIT_FAILURE);
	new_pwd = get_current_pwd();
	if (new_pwd == NULL)
		return (ft_putstr_nl("cd: failed to get new directory", STDERR_FILENO),
			EXIT_FAILURE);
	if (ft_setenv(&env, "PWD", new_pwd) != EXIT_SUCCESS)
		return (ft_putstr_nl("cd: failed to set PWD", STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
