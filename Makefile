BIN_DIR=$(PWD)

export BIN_DIR

all:
	echo ---------------------------------- $(BIN_DIR)
	make -C asm
	make -C vm

clean:
	make -C asm clean
	make -C vm clean

fclean: clean
	make -C asm fclean
	make -C vm fclean

re: fclean all
