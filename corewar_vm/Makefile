.PHONY: all clean fclean re libft

CAR =	vm_car_get_types_and_step.c \
		vm_car_implement_op.c\
		vm_car_play.c

COMMANDS = vm_command_clean.c \
           vm_command_connect.c \
           vm_command_connect_parse.c \
           vm_command_connect_workers.c \
           vm_command_disconnect.c \
           vm_command_exit.c \
           vm_command_handshake.c \
           vm_command_help.c \
           vm_command_process.c \
           vm_command_status.c \
           vm_command_utils.c \
           vm_command_wksetlog.c

INPUT = vm_input_av_parse.c \
        vm_input_create_queue.c \
        vm_input_define_mode.c \
        vm_input_init.c \
        vm_input_parse.c \
        vm_input_parse_champ.c \
        vm_input_receive_data.c \
        vm_input_remove.c \
        vm_input_socket_parse.c

MESSAGE = vm_message_endgame.c \
          vm_message_presentation_champs.c \
          vm_message_operation.c \
          vm_message_proc_statuses.c \
          vm_message_sendgame.c \
          vm_message_set_header.c \
          vm_message_game_loaded.c

SOCKET = vm_socket_block.c \
         vm_socket_close.c \
         vm_socket_connect_wait.c \
         vm_socket_connection_process.c \
         vm_socket_disconnect.c \
         vm_socket_fill.c \
         vm_socket_io_destroy.c \
         vm_socket_io_setup.c \
         vm_socket_recv.c \
         vm_socket_send.c \
         vm_socket_unblock.c \
         vm_socket_utils.c

WORKER = vm_worker_game_state_notify.c \
         vm_worker_log_dead_proc.c \
         vm_worker_manager_init.c \
         vm_worker_manager_remove.c \
         vm_worker_run.c \
         vm_worker_show_map.c \
         vm_worker_socket_notify.c \
         vm_worker_winner_notify.c \
         vm_worker_get_data_from_queue.c

OPERATIONS =	vm_op_log.c\
         vm_op_worker_add.c\
         vm_op_worker_aff.c\
         vm_op_worker_and.c\
         vm_op_worker_fork.c\
         vm_op_worker_ld.c\
         vm_op_worker_ldi.c\
         vm_op_worker_lfork.c\
         vm_op_worker_live.c\
         vm_op_worker_lld.c\
         vm_op_worker_lldi.c\
         vm_op_worker_or.c\
         vm_op_worker_st.c\
         vm_op_worker_sti.c\
         vm_op_worker_sub.c\
         vm_op_worker_xor.c\
         vm_op_worker_zjmp.c\
         vm_worker_fork_utils.c\
         vm_worker_op_utils.c


SERVER = vm_main.c \
         vm_man_error.c \
         vm_server_run.c \
         vm_server_start.c \
         vm_server_multithread.c

NAME = corewar

DIR_SRC = srcs/
DIR_INC = -I./includes/ -I./libft/includes/
DIR_OBJ = obj/

LIB = libft.a
DIR_LIB = ./libft/

HEADERS = corewar_vm.h op.h vm_game_input.h vm_io_interface.h vm_messages.h vm_server.h libft.h

OBJ = $(SRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)

SRC =	$(CAR) \
		$(COMMANDS) \
		$(INPUT) \
		$(MESSAGE) \
		$(SOCKET) \
		$(WORKER) \
		$(OPERATIONS) \
		$(SERVER)

SRCS = $(SRC:%.c=$(DIR_SRC)%.c)
OBJS = $(SRC:%.c=$(DIR_OBJ)%.o)
DEPS = $(SRC:%.c=$(DIR_OBJ)%.d)

MKDIR_P = mkdir -p

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): libft $(DIR_OBJ) $(OBJS)
	@echo Preparing CoreWarMachine
	$(COMPILER) $(FLAGS) -o $(NAME) $(OBJS) -L$(DIR_LIB) -lft

$(DIR_OBJ):
	@$(MKDIR_P) $@

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@echo Compiling: $<
	@$(COMPILER) $(FLAGS) -MD -o $@ -c $< $(DIR_INC) 

-include $(wildcard $(DEPS))

libft:
	$(MAKE) -C $(DIR_LIB)

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
		rm $(NAME)

re: clean all
