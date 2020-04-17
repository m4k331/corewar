NAME = asm

CC = gcc

BIN_DIR ?= .

CDIR = srcs
HDIR = includes
ODIR = objects

LBDIRS = libft
LBNAMES = libft.a

FRAMEWORKS =

LDFLAGS += $(addprefix -L , $(LBDIRS)) $(FRAMEWORKS)
LDLIBS += $(addprefix -l , $(LBNAMES:lib%.a=%))

INCDIRS = $(HDIR) $(LBDIRS) $(addsuffix /includes, $(LBDIRS))

DBCFLAGS = -Wno-error -g
CFLAGS = -Wall -Wextra -Werror -O3 $(addprefix -I , $(INCDIRS)) $(DBCFLAGS)

SOURCES =	main.c

OBJECTS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))

.PHONY: all libs clean clean_name fclean re

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

MAKEOVERRIDES =
libs:
	@for i in $(LBDIRS); do \
		make -C $$i 2> /dev/null ; \
	done
