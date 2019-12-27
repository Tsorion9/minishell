#include "minishell.h"

int         check_bunfile_sup(char *filepath, char *temp, char *filename)
{
    if (filepath)
        free(filepath);
    if (temp)
        free(temp);
    ft_putstr("./");
    ft_putstr(filename);
	write(1, "\n", 1);
    return (0);
}

int         check_binfile(char *filename, char *path)
{
    char        *filepath;
    struct stat fstat;
    char        *temp;

    temp = ft_strjoin(path, "/");
    filepath = ft_strjoin(temp, filename);
    stat(filepath, &fstat);
    if (access(filepath, F_OK))
	{
		ft_putstr("minishell: no such file or directory: ");
        return (check_bunfile_sup(filepath, temp, filename));
	}
    else if (S_ISDIR(fstat.st_mode))
	{
		ft_putstr("minishell: is a directory: ");
        return (check_bunfile_sup(filepath, temp, filename));
	}
    else if (access(filepath, X_OK))
	{
		ft_putstr("minishell: permission denied: ");
        return (check_bunfile_sup(filepath, temp, filename));
	}
    free(filepath);
    free(temp);
    return (1);
}

int         check_sysbin(char *filename, char *path)
{
    char        *filepath;
    struct stat fstat;
    char        *temp;

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

int         execute_sysbin(char **call, char **env, char **new_env)
{
    char    *val_path;
    char    **path;
    char    *filepath;
    char    *temp;
    int     i;
    int     error;

    if ((val_path = give_val_env(env, "PATH")) == NULL)
        return (0);
    path = ft_strsplit(val_path, ':');
    free(val_path);
    i = 0;
    error = 0;
    while (path[i] != NULL)
    {
        temp = ft_strjoin(path[i], "/");
        filepath = ft_strjoin(temp, *call);
        free(temp);
        if (access(filepath, F_OK) == 0)
        {
            if ((error = check_sysbin(*call, path[i])) == 1)
            {
                if (fork() == 0)
                    execve(filepath, call, new_env);
                else
                    wait(NULL);
                free(filepath);
                ft_freestrsplit(path);
                return (1);
            }
        }
        free(filepath);
        i++;
    }
    ft_freestrsplit(path);
    if (error == 2)
    {
        ft_putstr("minishell: is a directory: ");
        ft_putstr(*call);
        write(1, "\n", 1);
        return (1);
    }
    if (error == 3)
    {
        ft_putstr("minishell: permission denied: ");
        ft_putstr(*call);
        write(1, "\n", 1);
        return (1);
    }
    return (0);
}

void        execute_bin(char **call, char **env, char **new_env)
{
    if (ft_strncmp(call[0], "./", 2) == 0)
    {
        if (check_binfile(&(call[0][2]), "./") == 0)
            return ;
        if (fork() == 0)
            execve(&(call[0][2]), call + 1, new_env);
        else
            wait(NULL);
        return ;
    }
    if (execute_sysbin(call, env, new_env) == 0)
    {
	    ft_putstr("minishell: command not found: ");
	    ft_putstr(call[0]);
	    write(1, "\n", 1);
        return ;
    }
}
