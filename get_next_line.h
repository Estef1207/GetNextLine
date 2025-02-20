/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esmeza-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:00:16 by esmeza-s          #+#    #+#             */
/*   Updated: 2025/02/20 18:17:14 by esmeza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*get_line(int fd, char **buffer, char **backup);
int		read_file(int fd, char **buffer, char **backup);
char	*separate_line(char **backup);
void	free_ptr(char **ptr);
char	*get_next_line(int fd);
#endif
