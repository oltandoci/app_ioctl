######################
# Application Makefile
######################

#Genral paths
SRC_PATH=./src

#Compiler
CC=gcc

#Compilation flags
CFLAGS=-W -Wall -Wextra -Werror -O2
LDFLAGS=

#Application name
EXEC=test_ioctl

#Header folders
HDR=../../kernel/ioctl/inc

#Source files
SRC=src/main.c


#Clean files
clean-files=$(SRC_PATH)/*.o
clean-files+=*.o

#Object files
OBJ=$(SRC:.c=.o)

default: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

#Add all header folders (dependencies and commands)	 
%.o: %.c $(HDR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(HDR)

clean:
	@rm -rf $(clean-files)
	@rm -rf $(EXEC)
	

