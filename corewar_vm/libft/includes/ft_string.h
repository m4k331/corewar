/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:29:35 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>
# include "ft_mem.h"

# define MHZERO 0x0101010101010101UL
# define DHZERO 0x8080808080808080UL
# define FALSE 0
# define TRUE 1

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strnlen(const char *str, size_t maxlen);
size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,\
									size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char(*f)(unsigned int, char));
char				*ft_strjoin(const char *s1, const char *s2);
char				**ft_strsplit(const char *s, char c);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strtolower(char *str);
char				*ft_strtoupper(char *str);
char				*ft_strtrim(const char *s);
size_t				ft_strchrcount(const char *s, int c);

#endif
