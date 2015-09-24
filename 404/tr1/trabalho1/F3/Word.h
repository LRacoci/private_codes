#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"
/* Declara uma série de funções auxiliares para manipulação de
 * Strings e caracteres que não existem ou eu não conheço da
 * biblioteca padrão
 ************************************************************/

/* Copia de uma string para outra, semelhante a strcpy */
String copy_word(String src, unsigned int * len_resp);
/* Verifica se o caracter em target esta na String s */
bool char_in_string(char target, String s);
/* Extrai somente uma parte da string src de acordo com a formatação f */
bool filter_Word(String src, const String f);

typedef enum TypeArg{
	HEX = 1,
	DEC = 2,
	SYM = 3,
	ROT = 4
} TypeArg;
/* Devolve uma string ao arquivo em src */
bool ungetword(FILE * src, String str);
/* Pega uma palavra do arquivo src e devolve quantas linhas
 * foram saltadas no processo em *lines além de devolder em
 * *ok se não ocorreu o EOF por exemplo */
String fgetword(FILE * src, unsigned int * lines, bool * ok);
