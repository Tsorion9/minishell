/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:54:48 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/24 21:31:52 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include <dirent.h>

#define BUFSIZE 4096

/*				main.c				*/
void		call_check(char *buf, char **env);
void		execute_pwd(char **call);
void		execute_exit(char **call);

/*				execute_echo.c		*/
void		execute_echo(char **env, char **call);
void		print_echo_str(char *str);

/*				execute_cd.c		*/
void		execute_cd(char **call, char **env);
void		check_dir(char *path);

/*              environ.c           */
char		*give_val_env(char **env, char *var);
void		init_call(char **call, char **env);
