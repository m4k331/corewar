NAME = asm

.PHONY : all clean fclean re directories

DIR_OBJ = obj/

LIB = libft.a
DIR_LIB	= $(LIB:.a=/)

SOURCE = \
         check_file_name.c\
         compile.c\
         initialization.c\
         lexer.c\
         memory_cleaning.c\
         is_name_or_comment.c\
         is_string.c\
         is_label_instr_reg.c\
         is_comment.c\
         is_separator.c\
         is_label_char.c\
         is_direct.c\
         is_num.c\
         make_tree.c\
         parse_token.c\
         parse_name_and_comment.c\
         error.c\
         parse_instruction.c\
         instructions_1.c\
         check_last_end.c\
         parse_tree.c\
         instructions_2.c\
         make_hex_buffer.c\
         put_commands.c\
         calc_sizes.c\
         get_op_weight.c\
         make_file.c\
         main.c



HEADERS =	asm.h\
            op.h

FLAGS = -Wall -Wextra -Werror
OBJ = $(SOURCE:%.c=%.o)
DEP = $(OBJ:%.o=%.d)
SRCS = $(addprefix $(SRC))
OBJS = $(addprefix $(DIR_OBJ),$(OBJ))
DEPS = $(addprefix $(DIR_OBJ),$(DEP))

MKDIR_P = mkdir -p

all: $(NAME)

$(NAME): $(OBJS) | $(LIB)
	gcc $(FLAGS) -o $(NAME) $+ -L$(DIR_LIB) -lft

$(DIR_OBJ)%.o: %.c
	gcc $(FLAGS) -MD -o $@ -c $< -I$(DIR_INC) -I$(LIB_INCLUDES)
include $(wildcard $(DEPS))

$(OBJS): | $(DIR_OBJ)

$(LIB):
	$(MAKE) -C $(DIR_LIB)

$(DIR_OBJ):
	$(MKDIR_P) $@

clean:
	rm -f $(DIR_OBJ)*.o
	rm -rf $(DIR_OBJ)
	$(MAKE) -s -C $(DIR_LIB) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -s -C $(DIR_LIB) fclean

re: fclean all

