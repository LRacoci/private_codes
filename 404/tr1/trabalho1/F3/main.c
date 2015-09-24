#include <stdio.h>
#include <string.h>
#include "auxTypes.h"
#include "Builder.h"

int main(int argc, char *argv[]) {
	FILE *src = NULL, *out = NULL;
	String out_name;
	bool ok = true;
	/* Analisa o numero de argumentos */
	switch (argc){
		/* Se houver apenas uma arquivo ... */
		case 2:
			src = fopen(argv[1], "r");
			out_name = strcat(argv[1], ".aux");
			out = fopen(out_name, "w");
			break;
		/* Se houverem dois arquivos ... */
		case 3:
			src = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
	}
	/* Se o arquivo de entrada foi aberto com sucesso */
	if( src == NULL ){
		stderror(-1, "Error while opening the source file.\n");
		ok = false;
	}
	/* Se o arquivo de saída foi aberto com sucesso */
	if( out == NULL ){
		stderror(-1, "Error while opening the output file.\n");
		ok = false;
	}
	/* Atualiza a variavel ok com o valor de retorno da função
	 * pricipal de montagem */
    ok = ok? build(src, out) : false;
	/* Fecha os arquivos corretamente abertos */
    if(src)
        fclose(src);
    if(out)
        fclose(out);
	/* Retorna os codigos de saida correta ou incorreta dependendo de ok */
    return ok? EXIT_SUCESS : EXIT_FAIL;
}
