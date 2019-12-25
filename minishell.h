/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:54:48 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/25 19:45:07 by mphobos          ###   ########.fr       */
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
void		call_check(char *buf, char ***env);
void		execute_pwd(char **call);
void		execute_exit(char **call, char **env);
int			get_call_length(char **call);

/*				execute_echo.c		*/
void		execute_echo(char **env, char **call);
void		print_echo_str(char *str);

/*				execute_cd.c		*/
void		execute_cd(char **call, char **env);
void		check_dir(char *path);

/*				execute_setenv		*/
void		execute_setenv(char **call, char ***env);
void		add_rep_env_var(char **call, char ***env);
void		add_env_var(char **call, char ***env);
int			replace_env_var(char **call, char **env);

/*				environ.c			*/
char		*give_val_env(char **env, char *var);
void		init_call(char **call, char **env);
void		print_env(char **env);
char		**copy_env(char **environ);
