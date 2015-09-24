##########################################################
# Description: The makefile for "trab01".
#
# Author: Lucas Alves Racoci - ra156331@students.ic.unicamp.br
##########################################################

Arqs = main.o HashTable.o Builder.o Word.o MemMap.o

# Default rule
all: ias-as


# All the .o files depends on the .c and .h with the same name
%.o: %.c
	gcc -c $< -o $@ -std=c99 -pedantic -Wall -Werror -lm -g

##########################################################
# Do not change this rule
##########################################################

# -- Rule to make the executable ias-as
ias-as: $(Arqs)
	gcc -g $(Arqs) -o ias-as
	make clean

##########################################################
# Rules to clean the directory
##########################################################
.PHONY : clean_all clean
# Clean the .hex outputs, and the executable file
clean_all:
	make clean
	rm -f *.hex ias-as
# Clean the .o files
clean:
	rm -f *.o
