/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:23:13 by cmateos-          #+#    #+#             */
/*   Updated: 2023/11/21 21:59:06 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# define D_QUOTES 34
# define S_QUOTES 39

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

//FILE DESCRIPTOR:
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//LISTAS
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

//FT_PRINTF
int		ft_printf(char const *s, ...);
int		ft_putchr_pf(char c);
int		ft_putstr_pf(char *s);
int		ft_putnbr_pf(long nbr, int *count);
int		ft_putptr_pf(unsigned long nbr, char *hex, int count);
int		ft_puthex(unsigned int nbr, char *hex, int *count);
int		ft_putun(unsigned int nbr, int *count);

//GET_NEXT_LINE
char	*get_next_line(int fd);

int		ft_strposchr(const char *s, int c);
int		ft_isspace(int c);
int		check_emptyorspace(char *str);
void	ft_print_strarray(char **array);
void	ft_freematrix(char ***matrix);
char	**ft_sarrcpy(char **arr);
void	ft_putstr_fd_noquotes(char *s, int fd);
char	*ft_arrtostr(char **arr);
char	**ft_split_minishell(char const *s);
int		ft_lenstring_minishell(char const *s, int i);
char	**ft_sarradd(char **array, char *str);
char	**ft_sarrcpy(char **arr);
size_t	ft_sarrlen(char **array);
char	**ft_clear_sarradd(char **array, char *str);

#endif