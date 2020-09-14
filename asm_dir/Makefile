.PHONY: all clean fclean re norm libs clean_name

NAME = asm

CC = gcc

#BIN_DIR = ../resources
BIN_DIR ?= .

CDIR = srcs
HDIR = includes
ODIR = objects

LBDIRS = libft
LBNAMES = libft.a

LDFLAGS += $(addprefix -L , $(LBDIRS))
LDLIBS += $(addprefix -l , $(LBNAMES:lib%.a=%))

INCDIRS = $(HDIR) $(LBDIRS) $(addsuffix /includes, $(LBDIRS))

# DBCFLAGS = -Wno-error -g
OPTFLAGS = -O3
CFLAGS = -g -Wall -Wextra -Werror -MD $(addprefix -I , $(INCDIRS)) $(DBCFLAGS) $(OPTFLAGS)

SOURCES = \
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
         main.c\

OBJECTS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))
DEPS = $(OBJECTS:.o=.d)

all: libs $(ODIR) $(BIN_DIR) $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/$(NAME): $(OBJECTS)
	$(LINK.o) $^ $(LDLIBS) -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(CDIR)/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm -rf $(ODIR)
	@for i in $(LBDIRS); do \
		if ! $(MAKE) -C $$i fclean 2> /dev/null; then \
			$(MAKE) -C $$i clean; \
		fi; \
	done

clean_name:
	rm -f $(BIN_DIR)/$(NAME)

fclean: clean clean_name

re: fclean all

norm:
	norminette $(CDIR)/* $(HDIR)/*

MAKEOVERRIDES =
libs:
	@for i in $(LBDIRS); do \
		make -C $$i 2> /dev/null ; \
	done

-include $(wildcard $(DEPS))
