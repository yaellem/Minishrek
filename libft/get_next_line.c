/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:37:23 by mabed             #+#    #+#             */
/*   Updated: 2023/11/15 13:42:25 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fdi, int b)
{
	char		*linees;
	static char	*save;

	if (b == 0)
		return (free(save), NULL);
	if (fdi < 0 || BUFFER_SIZE <= 0 || fdi > 1024)
		return (0);
	save = ft_strjoin_buf_fd(save, fdi);
	if (!save)
		return (NULL);
	linees = ft_get_line(save);
	save = ft_save(save);
	return (linees);
}

char	*ft_strjoin_buf_fd(char *save, int fdh)
{
	int		i;
	char	*tmp;
	char	*buf;

	i = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((ft_check_newline(save) == 0) && i > 0)
	{
		i = read(fdh, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			free(save);
			return (NULL);
		}
		// printf("iciiiiiiiiiiiiiiiii2\n");
		// printf("%d==================\n", i);
		buf[i] = '\0';
		// printf("%s--------\n", buf);
		tmp = save;
		save = ft_strjoin2(tmp, buf);
		free(tmp);
		// printf("iciiiiiiiiiiiiiiiii2\n");
	}
	// dprintf(2, "save --------> :%s\n", save);
	free(buf);
	return (save);
}

char	*ft_get_line(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = malloc(sizeof(char) * (i + 2));
	if (!s)
		return (0);
	while (j < i)
	{
		s[j] = save[j];
		j++;
	}
	if (save[j] == '\n')
	{
		s[j] = save[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = ft_strlen(save);
	while (save[i] && save[i] != '\n')
		i++;
	if ((j - i) == 0)
	{
		free(save);
		return (0);
	}
	i++;
	s = malloc(sizeof(char) * (j - i + 1));
	if (!s)
		return (0);
	j = 0;
	while (save[i])
		s[j++] = save[i++];
	s[j] = '\0';
	free(save);
	return (s);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	fd = open("42.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free (line);
// 	}
// 	close(fd);
// }
