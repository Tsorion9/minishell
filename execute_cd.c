/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:06:55 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 21:23:15 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_dir_sup(char *path)
{
	ft_putstr(path);
	write(1, "\n", 1);
}

/*
** Проверка директории с переходом
*/

void		check_dir(char *path)
{
	struct stat	fstat;

	stat(path, &fstat);
	if (chdir(path) != 0 && path != NULL)
	{
		if (access(path, F_OK))
		{
			ft_putstr("cd: no such file or directory: ");
			check_dir_sup(path);
		}
		else if (!(S_ISDIR(fstat.st_mode)))
		{
			ft_putstr("cd: not a directory: ");
			check_dir_sup(path);
		}
		else if (access(path, X_OK))
		{
			ft_putstr("cd: Permission denied: ");
			check_dir_sup(path);
		}
	}
	if (path != NULL)
		free(path);
}

/*
** Проверка команды cd
*/

void		execute_cd(char **call, char **env)
{
	if (call[1] != NULL)
	{
		if (call[2] == NULL)
			check_dir(ft_strdup(call[1]));
		else if (call[3] == NULL)
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putstr(call[1]);
			write(1, "\n", 1);
		}
		else
			ft_putstr("cd: too many arguments\n");
	}
	else
		check_dir(give_val_env(env, "HOME"));
}
