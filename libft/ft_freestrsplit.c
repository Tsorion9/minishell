#include "libft.h"

void        ft_freestrsplit(char **str)
{
    int i;

    if (str != NULL)
	{
		i = 0;
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}