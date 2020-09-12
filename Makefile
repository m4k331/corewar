NAME = BIN

.PHONY: all clean fclean re norm obnulyay

PROJECT_PART_PATHS = $(ASM) $(VM)
BIN_DIR = $(PWD)/$(NAME)
export BIN_DIR

WHITE		:= '\033[1;107m'
BLUE		:= '\033[0;104m'
RED			:= '\033[1;101m'
TEXT_BLACK	:= '\033[1;30m'
EOC			:= '\033[0;0m'

ASM	= ./asm_dir
VM	= ./vm_dir

all: $(NAME)
	@for i in $(PROJECT_PART_PATHS); do \
		make -C $$i; \
	done

$(NAME):
	mkdir -p $(BIN_DIR)

clean:
	@for i in $(PROJECT_PART_PATHS); do \
		make -C $$i clean; \
	done

fclean: clean
	rm -rf $(NAME)
	@for i in $(PROJECT_PART_PATHS); do \
		make -C $$i fclean; \
	done

re: fclean all

norm:
	@for i in $(PROJECT_PART_PATHS); do \
		make -C $$i norm; \
	done

obnulyay:
	@echo $(TEXT_BLACK) $(WHITE) "⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(WHITE) "⣿⣿⣿⣵⣿⣿⣿⠿⡟⣛⣧⣿⣯⣿⣝⡻⢿⣿⣿⣿⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(WHITE) "⣿⣿⣿⣿⣿⠋⠁⣴⣶⣿⣿⣿⣿⣿⣿⣿⣦⣍⢿⣿⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(WHITE) "⣿⣿⣿⣿⢷⠄⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⢼⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(WHITE) "⢹⣿⣿⢻⠎⠔⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(BLUE) "⢸⣿⣿⠇⡶⠄⣿⣿⠿⠟⡛⠛⠻⣿⡿⠿⠿⣿⣗⢣⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(BLUE) "⠐⣿⣿⡿⣷⣾⣿⣿⣿⣾⣶⣶⣶⣿⣁⣔⣤⣀⣼⢲⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(BLUE) "⠄⣿⣿⣿⣿⣾⣟⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⢟⣾⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(BLUE) "⠄⣟⣿⣿⣿⡷⣿⣿⣿⣿⣿⣮⣽⠛⢻⣽⣿⡇⣾⣿⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(BLUE) "⠄⢻⣿⣿⣿⡷⠻⢻⡻⣯⣝⢿⣟⣛⣛⣛⠝⢻⣿⣿⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(RED) "⠄⠸⣿⣿⡟⣹⣦⠄⠋⠻⢿⣶⣶⣶⡾⠃⡂⢾⣿⣿⣿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(RED) "⠄⠄⠟⠋⠄⢻⣿⣧⣲⡀⡀⠄⠉⠱⣠⣾⡇⠄⠉⠛⢿⣿⣿⣿" $(EOC)
	@echo $(TEXT_BLACK) $(RED) "⠄⠄⠄⠄⠄⠈⣿⣿⣿⣷⣿⣿⢾⣾⣿⣿⣇⠄⠄⠄⠄⠄⠉⠉" $(EOC)
	@echo $(TEXT_BLACK) $(RED) "⠄⠄⠄⠄⠄⠄⠸⣿⣿⠟⠃⠄⠄⢈⣻⣿⣿⠄⠄⠄⠄⠄⠄⠄" $(EOC)
	@echo $(TEXT_BLACK) $(RED) "⠄⠄⠄⠄⠄⠄⠄⢿⣿⣾⣷⡄⠄⢾⣿⣿⣿⡄⠄⠄⠄⠄⠄⡀" $(EOC)
	
