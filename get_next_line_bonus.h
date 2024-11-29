/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agragera <agragera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:56:47 by agragera          #+#    #+#             */
/*   Updated: 2024/03/25 17:56:47 by agragera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

char		*get_next_line(int fd);
char		*read_line(int fd, char **storage);
char		*copy_and_advance(char *dest, const char *src, size_t len);
char		*extract_line(char **storage);
char		*strjoin_and_free(char *s1, char *s2);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif
#endif
