/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:54:48 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/28 21:23:30 by mphobos          ###   ########.fr       */
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

//				main.c
void		call_check(char *buf, char ***env);
void		execute_pwd(char **call);
void		execute_exit(char **call, char **env);
int			get_call_length(char **call);

//				init_call.c
void		init_call(char **call, char **env);
void		init_call_sup1(char **call, char **env, int i);
void		init_call_sup(char **call, char **env, int i);

//				execute_echo.c
void		execute_echo(char **env, char **call);
void		print_echo_str(char *str);

//				execute_cd.c
void		execute_cd(char **call, char **env);
void		check_dir(char *path);
void		check_dir_sup(char *path);

//				execute_setenv.c
void		execute_setenv(char **call, char ***env);
void		add_rep_env_var(char **call, char ***env);
void		add_env_var(char **call, char ***env);
int			replace_env_var(char **call, char **env);

//				execute_unsetenv.c
void		execute_unsetenv(char **call, char ***env);
int			find_var_env(char **call, char **env);
void		delete_var_env(char **call, char ***env);

//				execute_env.c
void		execute_env(char **call, char ***env);
int			env_flags(char ***new_env, char **call);
int			add_env(char ***new_env, char **call);
char		**create_call_unsetenv(char *val_env);
char		**create_call_setenv(char *val_env);

//				execute_env_sup.c
int			env_flags_sup3(char ***new_env, char **call, int i);
void		env_flags_sup2(char ***new_env, char **call, int i);
int			env_flags_sup1(char ***new_env, char **call, int i);
int			env_flags_sup(char ***new_env, char **call, int i);

//              execute_bin.c
void        execute_bin(char **call, char **env, char **new_env);

//				environ.c
char		*give_val_env(char **env, char *var);
void		print_env(char **env);
char		**copy_env(char **environ);
char		**get_new_env(void);
