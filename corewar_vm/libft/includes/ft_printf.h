/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:13:31 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_FT_PRINTF_H
# define COREWAR_VM_FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <inttypes.h>
# include "ft_mem.h"
# include "ft_checkers.h"
# include "ft_string.h"
# include "ft_put.h"
# include "ft_tonum.h"
# include "ft_dstr.h"

typedef char		t_c8;
typedef uint8_t		t_u8;
typedef uint16_t	t_u16;
typedef uint32_t	t_u32;
typedef uint64_t	t_u64;
typedef int8_t		t_s8;
typedef int16_t		t_s16;
typedef int32_t		t_s32;
typedef int64_t		t_s64;
typedef float		t_f32;
typedef double		t_f64;
typedef long double	t_f80;
# define MHZERO 0x0101010101010101UL
# define DHZERO 0x8080808080808080UL
# define DBL_BUFFER 20000
# define DBL_MAX_LEN 5000
# define RED "\033[0;31m"
# define REDBOLD "\033[1;31m"
# define GREEN "\033[0;32m"
# define GREENBOLD "\033[1;32m"
# define YELLOW "\033[0;33m"
# define YELLOWBOLD "\033[1;33m"
# define BLUE "\033[0;34m"
# define BLUEBOLD "\033[1;34m"
# define MAGENTA "\033[0;35m"
# define MAGENTABOLD "\033[1;35m"
# define CYAN "\033[0;36m"
# define CYANBOLD "\033[1;36m"
# define RESET "\033[0m"

typedef struct			s_rules
{
	unsigned short int	flags;
	unsigned short int	mod;
	int					width;
	unsigned char		prec_on;
	long long			prec;
	long long			len_word;
	long long			len_num;
	int					sign;
	int					num;
	char				*word_start;
	int					skip;
	int					fd;
	int					err;
	char				*color;
	t_dstr				*dstr;
}						t_rules;

typedef union			u_dbl
{
	t_f64				d;
	t_f80				dlong;
	t_u64				l;
	struct				s_parts
	{
		t_u64			mantisa : 52;
		t_u64			exponent : 11;
		t_u64			sign : 1;
	}					t_parts;
	struct				s_dblp
	{
		t_u64			mantisa : 63;
		t_u64			mant_int : 1;
		t_u64			exponent : 15;
		t_u64			sign : 1;
	}					t_dblp;
}						t_dbl;

typedef struct			s_bint
{
	size_t				len;
	t_u32				arr[DBL_MAX_LEN];
}						t_bint;

/*
** bint_api.c
*/
size_t					bint_len(t_bint *bint);
int						bint_comp(const t_bint *first, const t_bint *second);
t_bint					*bint_copy(t_bint *dst, const t_bint *src);
void					get_exp_first_digit(t_dbl dbl, int *exp,
											t_rules *rules);
/*
** c_proc.c
*/
void					c_writer(int arg, t_rules *rules, char **res);
/*
** di_proc.c
*/
char					*ft_itoa_len(int n, t_rules *rules);
char					*ft_itoa_long(long long n, t_rules *rules);
/*
** f_proc.c
*/
char					*ft_dtoa(long double num, t_rules *rules);
char					*ft_dtoa_long(long double num, t_rules *rules);
/*
** f_proc_ldbl.c
*/
char					*f_proc(long double arg, t_rules *rules);
void					f_proc_dec(t_dbl dbl, t_rules *rules,
							char *res, int *exp);
int						f_handle_extremums(t_dbl dbl, t_rules *rules,
							char **res);
/*
** f_proc_powten.c
*/
void					bint_mult_powten(t_bint *result, t_u32 exp);
/*
** f_proc_prec_ldbl.c
*/
char					*handle_prec(char *digits, t_rules *rules, int exp);
/*
** f_proc_support.c
*/
t_bint					*bint_mult_bint(t_bint *res, const t_bint *first,
							const t_bint *second);
t_bint					*bint_add_bint(t_bint *res,
							const t_bint *first, const t_bint *sec);
t_bint					*bint_mult_u32(t_bint *res, t_u32 num);
void					def_big_small_bint(const t_bint *first,
							const t_bint *second,
							const t_bint **big, const t_bint **small);
t_bint					*move_left(t_bint *bint, t_u32 step);
/*
** f_proc_support2.c
*/
t_bint					*bint_minus_bint(t_bint *res, const t_bint *first,
							const t_bint *second);
int						bint_div_bint_to_int(const t_bint *dec,
							const t_bint *div);
t_bint					*int_to_bint(t_u64 num, t_bint *bint);
int						get_exponent(long double value);
/*
** ft_printf.c
*/
int						ft_printf(const char *format, ...);
int						ft_printfd(int fd, const char *format, ...);
int						ft_printfs(t_dstr *dstr, const char *format, ...);
char					*pf_rulesinit(t_rules *rules, const char **str,
							va_list *arg);
int						pf_stringrunner(int fd, const char *format,
						va_list *arg);
int						pf_stringrunner_s(t_dstr *dstr, const char *format,
						va_list *arg);
const char				*ft_parse_s(const char *str, va_list *arg,
						t_rules *rules);
void					specifier_parser(const char *str, va_list *arg,
							t_rules *rules, char **num);
void					percent_writer(t_rules *rules, char **res);
/*
** handle_f_extremums.c
*/
int						handle_extremums(long double dbl, char **res,
							t_rules *rules);
/*
** o_proc.c
*/
char					*otoa_base_len(unsigned int num, int base, int letter,
							t_rules *rules);
char					*otoa_base_long(unsigned long num, int base, int letter,
							t_rules *rules);
char					*otoa_base_llong(unsigned long long num, int base,
							int letter, t_rules *rules);
char					*otoa_base_short(unsigned short num, int base,
							int letter, t_rules *rules);
char					*otoa_base_hshort(unsigned char num, int base,
							int letter, t_rules *rules);
/*
** o_proc_continue.c
*/
char					*pf_zero_case_o(t_rules *rules);
size_t					pf_setstart(t_rules *rules, int num_zero);
char					*pf_fillrest(char *res, t_rules *rules,
							long long strt, int letter);
/*
** p_proc.c
*/
void					p_writer(void *pointer, t_rules *rules, char **mem);
/*
** parsecolors.c
*/
const char				*ft_parsecolor(const char *str, t_rules *rules);
/*
** parseman.c
*/
const char				*ft_parse(const char *str, va_list *arg,
							t_rules *rules);
/*
** processor.c
*/
void					f_writer(t_rules *rules, va_list *arg, char **num);
void					di_writer(t_rules *rules, va_list *arg, char **num);
void					u_writer(t_rules *rules, va_list *arg, char **num);
void					o_writer(t_rules *rules, va_list *arg, char **num);
void					x_writer(const char *str, t_rules *rules,
							va_list *arg, char **num);
/*
** s_proc.c
*/
void					s_writer(char *arg, t_rules *rules, char **res,
							int f_mod);
/*
** u_proc.c
*/
char					*ft_itoa_ulen(unsigned int n, t_rules *rules);
char					*ft_itoa_ulong(unsigned long long n, t_rules *rules);
/*
** utils.c
*/
void					pf_prepstr(t_rules *rules, char *res, long long start);
void					pf_procninenine(char **res_old, long long i,
							t_rules *rules, long long prec);
void					pf_rounding(char **res, long long i, t_rules *rules,
							long long prec);
void					pf_skip_non_prc(t_rules *rules, const char **format);
/*
** x_proc.c
*/
char					*itoa_base_len(unsigned int num, int base, int letter,
							t_rules *rules);
char					*itoa_base_long(unsigned long num, int base,
							int letter, t_rules *rules);
char					*itoa_base_short(unsigned short num, int base,
							int letter, t_rules *rules);
/*
** x_proc_continue.c
*/
char					*pf_zero_case_x(t_rules *rules);
void					pf_fillprec_x(t_rules *rules, char *res,
							long long strt, int letter);
void					pf_fillnoprec_x(t_rules *rules, char *res,
							long long strt, int letter);
char					*pf_dbl_rounding(char *digits, t_rules *rules,
							int *exp, long long *start);

#endif
