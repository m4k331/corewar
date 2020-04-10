.PHONY: all clean fclean re directories libft

DIR_CAR = vm_car
CAR =	$(DIR_CAR)/vm_car_get_types_and_step.c \
		$(DIR_CAR)/vm_car_implement_op.c\
		$(DIR_CAR)/vm_car_play.c

DIR_COMMANDS = vm_commands_server
COMMANDS = $(DIR_COMMANDS)/vm_command_clean.c \
           $(DIR_COMMANDS)/vm_command_connect.c \
           $(DIR_COMMANDS)/vm_command_connect_parse.c \
           $(DIR_COMMANDS)/vm_command_connect_workers.c \
           $(DIR_COMMANDS)/vm_command_disconnect.c \
           $(DIR_COMMANDS)/vm_command_exit.c \
           $(DIR_COMMANDS)/vm_command_handshake.c \
           $(DIR_COMMANDS)/vm_command_help.c \
           $(DIR_COMMANDS)/vm_command_process.c \
           $(DIR_COMMANDS)/vm_command_status.c \
           $(DIR_COMMANDS)/vm_command_utils.c \
           $(DIR_COMMANDS)/vm_command_wksetlog.c

DIR_INPUT = vm_input
INPUT = $(DIR_INPUT)/vm_input_av_parse.c \
        $(DIR_INPUT)/vm_input_create_queue.c \
        $(DIR_INPUT)/vm_input_define_mode.c \
        $(DIR_INPUT)/vm_input_init.c \
        $(DIR_INPUT)/vm_input_parse.c \
        $(DIR_INPUT)/vm_input_parse_champ.c \
        $(DIR_INPUT)/vm_input_receive_data.c \
        $(DIR_INPUT)/vm_input_remove.c \
        $(DIR_INPUT)/vm_input_socket_parse.c

DIR_MESSAGE = vm_message
MESSAGE = $(DIR_MESSAGE)/vm_message_endgame.c \
          $(DIR_MESSAGE)/vm_message_game_loaded_notify.c \
          $(DIR_MESSAGE)/vm_message_operation.c \
          $(DIR_MESSAGE)/vm_message_proc_statuses.c \
          $(DIR_MESSAGE)/vm_message_sendgame.c \
          $(DIR_MESSAGE)/vm_message_set_header.c

DIR_SOCKET = vm_socket
SOCKET = $(DIR_SOCKET)/vm_socket_block.c \
         $(DIR_SOCKET)/vm_socket_close.c \
         $(DIR_SOCKET)/vm_socket_connect_wait.c \
         $(DIR_SOCKET)/vm_socket_connection_process.c \
         $(DIR_SOCKET)/vm_socket_disconnect.c \
         $(DIR_SOCKET)/vm_socket_fill.c \
         $(DIR_SOCKET)/vm_socket_io_destroy.c \
         $(DIR_SOCKET)/vm_socket_io_setup.c \
         $(DIR_SOCKET)/vm_socket_recv.c \
         $(DIR_SOCKET)/vm_socket_send.c \
         $(DIR_SOCKET)/vm_socket_unblock.c \
         $(DIR_SOCKET)/vm_socket_utils.c

DIR_WORKER = vm_worker
WORKER = $(DIR_WORKER)/vm_worker_game_state_notify.c \
         $(DIR_WORKER)/vm_worker_log_dead_proc.c \
         $(DIR_WORKER)/vm_worker_manager_init.c \
         $(DIR_WORKER)/vm_worker_manager_remove.c \
         $(DIR_WORKER)/vm_worker_run.c \
         $(DIR_WORKER)/vm_worker_show_map.c \
         $(DIR_WORKER)/vm_worker_socket_notify.c \
         $(DIR_WORKER)/vm_worker_winner_notify.c \
         $(DIR_WORKER)/vm_worker_get_data_from_queue.c

DIR_OPERATIONS = worker_operations
OPERATIONS =	$(DIR_OPERATIONS)/vm_op_log.c\
         $(DIR_OPERATIONS)/vm_op_worker_add.c\
         $(DIR_OPERATIONS)/vm_op_worker_aff.c\
         $(DIR_OPERATIONS)/vm_op_worker_and.c\
         $(DIR_OPERATIONS)/vm_op_worker_fork.c\
         $(DIR_OPERATIONS)/vm_op_worker_ld.c\
         $(DIR_OPERATIONS)/vm_op_worker_ldi.c\
         $(DIR_OPERATIONS)/vm_op_worker_lfork.c\
         $(DIR_OPERATIONS)/vm_op_worker_live.c\
         $(DIR_OPERATIONS)/vm_op_worker_lld.c\
         $(DIR_OPERATIONS)/vm_op_worker_lldi.c\
         $(DIR_OPERATIONS)/vm_op_worker_or.c\
         $(DIR_OPERATIONS)/vm_op_worker_st.c\
         $(DIR_OPERATIONS)/vm_op_worker_sti.c\
         $(DIR_OPERATIONS)/vm_op_worker_sub.c\
         $(DIR_OPERATIONS)/vm_op_worker_xor.c\
         $(DIR_OPERATIONS)/vm_op_worker_zjmp.c\
         $(DIR_OPERATIONS)/vm_worker_fork_utils.c\
         $(DIR_OPERATIONS)/vm_worker_op_utils.c


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

HEADERS = corewar_vm.h op.h vm_game_input.h vm_server.h libft.h

FLAGS = -O2 -Wall -Wextra -Werror -pthread
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

DIRS = $(DIR_OBJ) \
		$(DIR_OBJ)/$(DIR_CAR) \
		$(DIR_OBJ)/$(DIR_COMMANDS) \
		$(DIR_OBJ)/$(DIR_INPUT) \
		$(DIR_OBJ)/$(DIR_MESSAGE) \
		$(DIR_OBJ)/$(DIR_SOCKET) \
		$(DIR_OBJ)/$(DIR_WORKER) \
		$(DIR_OBJ)/$(DIR_OPERATIONS)

SRCS = $(SRC:%.c=$(DIR_SRC)%.c)
OBJS = $(SRC:%.c=$(DIR_OBJ)%.o)
DEPS = $(SRC:%.c=$(DIR_OBJ)%.d)

MKDIR_P = mkdir -p

COMPILER = gcc

all: $(NAME)

$(NAME): libft $(DIRS) $(OBJS)
	$(COMPILER) $(FLAGS) -o $(NAME) $(OBJS) -L$(DIR_LIB) -lft

$(DIRS):
	@$(MKDIR_P) $(DIRS)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	$(COMPILER) $(FLAGS) -MD -o $@ -c $< $(DIR_INC)
-include $(wildcard *.d)

libft:
	$(MAKE) -C $(DIR_LIB)

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
		rm $(NAME)

re: clean all
