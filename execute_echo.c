/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:54:13 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/25 18:12:19 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// вывести строку из echo
void		print_echo_str(char *str)
{
	while (*str != 0)
	{
		if (*str != 92)
			write(1, str, 1);
		str++;
	}
}

// выполнение echo
void		execute_echo(char **env, char **call)
{
	int		i;

	(void)env;
	i = 1;
	if (call[1] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (call[1] != NULL)
		if (ft_strcmp(call[1], "-n") == 0)
			i = 2;
	while (call[i] != NULL)
	{
		print_echo_str(call[i]);
		if (call[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (call[1] != NULL)
		if (ft_strcmp(call[1], "-n") != 0)
			write(1, "\n", 1);
}
