/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:54 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/09 15:24:40 by yioffe           ###   ########.fr       */
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
	char    *temp;

	temp = ft_strjoin(name, "=");
	new_entry = ft_strjoin(temp, value);
	free(temp); // Free the memory from the first ft_strjoin

	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0 && (*env)[i][ft_strlen(name)] == '=')
		{
			//free((*env)[i]);
			(*env)[i] = new_entry;
			return (EXIT_SUCCESS);
		}
		i++;
	}

	new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_env) // Check if malloc succeeded
		return (EXIT_FAILURE);

	j = 0;
	while ((*env)[j])
	{
		new_env[j] = (*env)[j];
		j++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	//free(*env);
	*env = new_env;
	return (EXIT_SUCCESS);
}

int	ft_cd(t_shell *shell, t_arg *command)
{
	char	*pwd;
	char	*path;
	char	*new_pwd;
	char    *old_pwd;
	char 	**env = shell->env_2d;
	char 	**args = command->args_doublechar; 
	int 	fd_out = STDOUT_FILENO;


	pwd = ft_getenv(env, "PWD");
	old_pwd = pwd ? ft_strdup(pwd) : NULL; // Make a copy of the pwd string

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
	if (ft_setenv(&env, "OLDPWD", old_pwd) != EXIT_SUCCESS)
		return (ft_putstr_nl("cd: failed to set OLDPWD", STDERR_FILENO), EXIT_FAILURE);
	free(old_pwd); // Free the old_pwd string
	new_pwd = get_current_pwd();
	if (new_pwd == NULL)
		return (ft_putstr_nl("cd: failed to get new directory", STDERR_FILENO),
			EXIT_FAILURE);
	if (ft_setenv(&env, "PWD", new_pwd) != EXIT_SUCCESS)
		return (ft_putstr_nl("cd: failed to set PWD", STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
int main(void)
{
    char *env[] = {
        "PWD=/",
        "HOME=/home",
        NULL
    };
    char *args1[] = {
        "cd",
        NULL
    };
    char *args2[] = {
        "cd",
        "/tmp",
        NULL
    };

    printf("Initial PWD: %s\n", getenv("PWD"));
    printf("Initial HOME: %s\n", getenv("HOME"));

    if (ft_cd(env, args1, 1) != EXIT_SUCCESS) {
        fprintf(stderr, "Failed to change directory to HOME\n");
        return EXIT_FAILURE;
    }

    printf("After changing to HOME, PWD: %s\n", getenv("PWD"));

    if (ft_cd(env, args2, 1) != EXIT_SUCCESS) {
        fprintf(stderr, "Failed to change directory to /tmp\n");
        return EXIT_FAILURE;
    }

    printf("After changing to /tmp, PWD: %s\n", getenv("PWD"));

    return EXIT_SUCCESS;
} */