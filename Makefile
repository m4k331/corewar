.PHONY: all clean fclean re norm obnulyay

ASM	= ./asm_dir
VM	= ./vm_dir

PROJECTS = $(ASM) $(VM)

define part_exec
	@for i in $(PROJECTS); do \
    	make -C $$i $(1); \
    done
endef

BIN_DIR = $(PWD)
export BIN_DIR

WHITE		:= '\033[1;107m'
BLUE		:= '\033[0;104m'
RED			:= '\033[1;101m'
TEXT_BLACK	:= '\033[1;30m'
EOC			:= '\033[0;0m'

all:
	$(call part_exec,$@)

clean:
	$(call part_exec,$@)

fclean: clean
	$(call part_exec,$@)

re: fclean all

norm:
	$(call part_exec,$@)

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
	
