/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburgler <mburgler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:01:45 by mburgler          #+#    #+#             */
/*   Updated: 2023/05/06 20:14:52 by mburgler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft/libft.h"

char	*get_next_line(int fd)
{
	static char	*mem[FD_COUNT];
	char		*out;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	mem[fd] = read_line(fd, mem[fd]);
	if (!mem[fd])
		return (NULL);
	out = kill_after_backslash_n(mem[fd]);
	mem[fd] = save_after_backslash_n(mem[fd]);
	return (out);
}

char	*read_line(int fd, char *mem)
{
	int		chars_read;
	char	*extracted;

	chars_read = 1;
	extracted = ft_calloc(1, BUFFER_SIZE + 1);
	if (!extracted)
		return (NULL);
	while (chars_read > 0)
	{
		chars_read = read(fd, extracted, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(extracted);
			free(mem);
			mem = NULL;
			return (NULL);
		}
		extracted[chars_read] = '\0';
		mem = ft_strjoin2(mem, extracted);
		if (ft_strchr2(mem, '\n'))
			break ;
	}
	free (extracted);
	return (mem);
}

char	*kill_after_backslash_n(char *mem)
{
	int		len;
	int		i;
	char	*out;

	if (!mem[0])
		return (NULL);
	len = seek_end_of_line(mem) + 1;
	if (mem[len - 1] == '\n')
	{
		out = ft_calloc(1, sizeof(char) * (len + 1));
		if (!out)
			return (NULL);
		i = 0;
		while (i < len)
		{
			out[i] = mem[i];
			i++;
		}
		out[i] = '\0';
		return (out);
	}
	else
		return (failsafe(mem));
}

char	*save_after_backslash_n(char *mem)
{
	int		end_of_line;
	int		j;
	char	*sl;

	end_of_line = seek_end_of_line(mem);
	if (!mem[end_of_line])
	{
		free(mem);
		return (NULL);
	}
	sl = ft_calloc(1, sizeof(char) * (ft_strlen2(mem) - end_of_line));
	if (!sl)
	{
		free(mem);
		return (NULL);
	}
	end_of_line++;
	j = 0;
	while (mem[end_of_line])
		sl[j++] = mem[end_of_line++];
	sl[j] = '\0';
	free(mem);
	return (sl);
}

// //ADDITIONAL TESTERS
// int	main(void)
// {
// 	int			fd;
// 	char		*result;

// 	printf("\n-- new version 25.12.2022 --\n\n");
// 	printf("## MAIN INITIALIZED ##\n\n");
// 	fd = open("testdatei.txt", O_RDONLY);
// 	printf("file descriptor: %d\n\n", fd);
// 	result = get_next_line(fd);
// 	printf("line 1:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 2:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 3:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 4:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 5:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 6:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 7:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 8:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 9:  %s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("line 10: %s", result);
// 	free(result);
// 	printf("\n\n##COMPLETED WITHOUT CRASHING##\n\n");
// 	return (0);
// }
