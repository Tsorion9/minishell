/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:54:48 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/23 17:37:48 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include <dirent.h>

#define BUFSIZE 4096

/*				main.c				*/
void		call_check(char *buf, char **env);
char		*give_val_env(char **env, char *var);

/*				execute_cd.c		*/
void		execute_cd(char **call, char **env);
void		check_dir(char *path);