/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:06:55 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/23 19:36:11 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// проверка директории с переходом
void		check_dir(char *path)
{
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) == 1)
		{
			ft_putstr("cd: not a directory: ");
			ft_putstr(path);
		}
		if (access(path, 4) == 1)
		{
			ft_putstr("cd: permission denied: ");
			ft_putstr(path);
		}
		if (access(path, 0) == 1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr(path);
		}
	}
}

// проверка cd
void		execute_cd(char **call, char **env)
{
	if (call[1] != NULL)
	{
		if (call[2] == NULL)
			check_dir(call[1]);
	}
	else
		check_dir(give_val_env(env, "HOME"));
}
