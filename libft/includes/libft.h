/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:32:40 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/03 11:48:28 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef FD
#  define FD 1
# endif

# ifndef FLAG
#  define FLAG "cspdiuxX%"
# endif

# ifndef HEX_BASE
#  define HEX_BASE "0123456789abcdef"
# endif

# ifndef HEX_BASE_MAJ
#  define HEX_BASE_MAJ "0123456789ABCDEF"
# endif

typedef struct s_list
{
	void			*content;
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_atoi_base(const char *nptr, int base);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strndup(const char *s, int size);
char	*ft_strdup(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	**ft_split(char const *s, char *c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_is_charset(char c, char *charset);

//////// PRINTF /////////

int		ft_printf(const char *str, ...);
int		do_c_to_str(va_list ap);
int		do_s_to_str(va_list ap);
int		do_p_to_str(va_list ap);
int		do_di_to_str(va_list ap);
int		do_u_to_str(va_list ap);
int		do_x_to_str(va_list ap, char type);

////////// GNL  ///////////

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_gnl {
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

char	*get_next_line(int fd);
int		ft_read_write(int fd, t_gnl **stash);
void	ft_to_stash(t_gnl **stash, char *buffer, int c_read);
void	ft_line_from_stash(t_gnl *lst, char **line);
void	ft_gnlclean_stash(t_gnl **stash);

t_gnl	*ft_gnllast(t_gnl *lst);
int		ft_is_newline(t_gnl *stash);
int		ft_gnl_strlen(t_gnl *lst);
void	ft_gnlclean(t_gnl **lst);

#endif
