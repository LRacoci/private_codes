Arqs = main.o HashTable.o Builder.o iasDefs.o Word.o  Error.o

%.hex: %.in ias-as
	./ias-as $< $@

%.o: %.c
	gcc -c $< -o $@ -std=c99 -pedantic -Wall -Werror -lm -g

ias-as: $(Arqs)
	gcc $(Arqs) -o ias-as -std=c99 -pedantic -Wall -Werror -lm

.PHONY : clean_all clean
clean_all:
	make clean
	rm -f *.hex ias-as
clean:
	rm -f *.o
