/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:06:55 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/02 10:10:44 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_dir_sup(char *path)
{
	ft_putstr(path);
	write(1, "\n", 1);
}

void		check_dir_sup1(char *path)
{
	ft_putstr("cd: no such file or directory: ");
	check_dir_sup(path);
}

/*
** Проверка директории с переходом
*/

void		check_dir(char *path, char *prev_dir)
{
	struct stat	fstat;
	char		prev_prev_dir[BUFSIZE];

	stat(path, &fstat);
	ft_memcpy(prev_prev_dir, prev_dir, BUFSIZE);
	getcwd(prev_dir, BUFSIZE);
	if (chdir(path) != 0)
	{
		ft_memcpy(prev_dir, prev_prev_dir, BUFSIZE);
		if (access(path, F_OK))
			check_dir_sup1(path);
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
	free(path);
}

/*
** Проверка команды cd
*/

void		execute_cd(char **call, char **env)
{
	static char	prev_dir[BUFSIZE];
	char		dir[BUFSIZE];

	if (call[1] != NULL)
	{
		if (call[2] == NULL && ft_strcmp(call[1], "-") != 0)
			check_dir(ft_strdup(call[1]), prev_dir);
		else if (call[2] == NULL && ft_strcmp(call[1], "-") == 0)
		{
			check_dir(ft_strdup(prev_dir), prev_dir);
			getcwd(dir, BUFSIZE);
			check_dir_sup(dir);
		}
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
		check_dir(give_val_env(env, "HOME"), prev_dir);
}
