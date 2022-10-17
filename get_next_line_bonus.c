/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrollo <mrollo@student.42barcelon...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:34:38 by mrollo            #+#    #+#             */
/*   Updated: 2022/02/18 15:34:53 by mrollo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*clean_line(char *save)
{
	char	*temp;
	char	*aux;
	int		len;

	aux = ft_strchr(save, '\n');
	if (!aux)
	{
		free(save);
		temp = NULL;
		return (NULL);
	}
	else
		len = (aux - save) + 1;
	if (!save[len])
	{
		free(save);
		return (NULL);
	}
	temp = ft_substr(save, len, ft_strlen(save) - len);
	free(save);
	return (temp);
}

char	*get_new_line(char *save)
{
	int		len;
	char	*aux;
	char	*line;

	aux = ft_strchr(save, '\n');
	len = (aux - save) + 1;
	line = ft_substr(save, 0, len);
	if (line[0] == '\0')
		return (NULL);
	return (line);
}

char	*ft_read(int fd, char *save)
{
	int		n;
	char	*buffer;

	n = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (n > 0 && (ft_strchr(buffer, '\n') == NULL))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		if (n > 0)
		{
			buffer[n] = '\0';
			save = ft_strjoin(save, buffer);
		}
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[OPEN_MAX];

	if (fd < 0)
		return (NULL);
	if ((save[fd] && !ft_strchr(save[fd], '\n')) || !save[fd])
	{
		save[fd] = ft_read(fd, save[fd]);
	}
	if (!save[fd])
		return (NULL);
	line = get_new_line(save[fd]);
	if (!line)
	{
		free(save[fd]);
		return (NULL);
	}
	save[fd] = clean_line(save[fd]);
	return (line);
}
