/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sysbin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 14:35:03 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/29 14:43:37 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_sysbin(char *filename, char *path)
{
	char		*filepath;
	struct stat	fstat;
	char		*temp;

	temp = ft_strjoin(path, "/");
	filepath = ft_strjoin(temp, filename);
	stat(filepath, &fstat);
	if (S_ISDIR(fstat.st_mode))
	{
		free(filepath);
		free(temp);
		return (2);
	}
	else if (access(filepath, X_OK))
	{
		free(filepath);
		free(temp);
		return (3);
	}
	free(filepath);
	free(temp);
	return (1);
}

int			execute_sysbin_sup(char **c, char **n, char **p, int *e)
{
	int		i;
	char	*filepath;
	char	*temp;

	i = 0;
	while (p[i] != NULL)
	{
		temp = ft_strjoin(p[i], "/");
		filepath = ft_strjoin(temp, *c);
		free(temp);
		if (access(filepath, F_OK) == 0)
			if ((*e = check_sysbin(*c, p[i])) == 1)
			{
				if (fork() == 0)
					execve(filepath, c, n);
				else
					wait(NULL);
				free(filepath);
				ft_freestrsplit(p);
				return (1);
			}
		free(filepath);
		i++;
	}
	return (0);
}

int			execute_sysbin_sup1(int error, char **call)
{
	if (error == 2)
	{
		ft_putstr("minishell: is a directory: ");
		ft_putstr(*call);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

int			execute_sysbin(char **call, char **env, char **new_env)
{
	char	*val_path;
	char	**path;
	int		error;

	if ((val_path = give_val_env(env, "PATH")) == NULL)
		return (0);
	path = ft_strsplit(val_path, ':');
	free(val_path);
	error = 0;
	if (execute_sysbin_sup(call, new_env, path, &error) == 1)
		return (1);
	ft_freestrsplit(path);
	if (execute_sysbin_sup1(error, call) == 1)
		return (1);
	if (error == 3)
	{
		ft_putstr("minishell: permission denied: ");
		ft_putstr(*call);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
