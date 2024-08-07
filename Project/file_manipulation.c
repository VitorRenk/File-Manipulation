#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// função para verificar se o código de registro é igual de outro registro
int verificar_codigo(char *codigo_vendedor, FILE *arquivo) {
    char linha[100];
    int codigo_invalido = 0;

    if (arquivo) {
        while (fgets(linha, sizeof(linha), arquivo)) {
            char *posicao = strstr(linha, "Código do vendedor: ");
            if (posicao != NULL) {
                posicao += strlen("Código do vendedor: ");

                posicao[strcspn(posicao, "\r\n")] = 0;

                if (strcmp(posicao, codigo_vendedor) == 0) {
                    codigo_invalido = 1;
                    printf("Erro: código idêntico a outro vendedor\n\n");
                    break;
                }
            }
        }
        fclose(arquivo);

        if (!codigo_invalido) {
            return 0;
        }
        else {
        	return 1;
        }
    }
    else{
    	return -1;
    }
}

// função para verificar se o mês é válido
int verificar_intervalo(char *codigo_vendedor) {

    int codigo = atoi(codigo_vendedor);
    if (codigo < 1 || codigo > 12) {
    	printf("Erro: mês inválido\n");
        return 0;
    } else {
        return 1;
    }
}

// função para verificar se os caracteres formam uma string
int isString(char *str) {

    while (*str) {
        if (!isalpha((unsigned char)*str)) {
        	if (*str != ' ') {
				return 0;
			}
        }
        str++;
    }
    return 1;
}

// função para verificar se os caracteres contém apenas dígitos
int isDigit(char *digit) {

	while (*digit) {
		if (!isdigit((unsigned char)*digit)) {
			return 0;
		}
		digit++;
	}
	return 1;
}

// função para verificar se os caracteres formam um float
int isFloat(const char *str) {
    char *endptr;
    strtod(str, &endptr);
    if (*endptr != '\0' || endptr == str) {
        return 0;
    }
    return 1;
}

// função para verificar se os caracteres formam um int
int isInteger(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    if (*endptr != '\0' || endptr == str) {
        return 0;
    }
    return 1;
}

// função para limpar o buffer de entrada
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    char codigo_vendedor[5];
    int value_codigo;
    char nome_vendedor[30];
    float valor_da_venda;
    int mes;
    char nome_arquivo_entrada[10];
    char nome_arquivo_saida[10];
    int opcao;
    char entrada[10];
    char linha[100];
    FILE *arquivo;
    FILE *arq;
    FILE *arq_saida;
    char excluir_escolhido[20];
    char c;
    int codigo_invalido = 0;

    while (opcao != 9) {
        printf("----------------OPÇÕES-----------------\n\n");
        printf("1- Criar um novo arquivo de entrada\n");
        printf("2- Incluir um determinado registro no arquivo\n");
        printf("3- Excluir um determinado vendedor no arquivo\n");
        printf("4- Alterar o valor de uma venda no arquivo\n");
        printf("5- Mostrar os registos no console de entrada\n");
        printf("6- Mostrar os registros no console de saida\n");
        printf("7- Imprimir os registros na saída padrão\n");
        printf("8- Excluir o arquivo de entrada\n");
        printf("9- Finalizar o programa\n\n");

        printf("Selecione sua opção:\n");
        fflush(stdout);
        scanf("%s", entrada);
        clearInputBuffer();

        int valido = 1;
		for(int i = 0; i < strlen(entrada); i++){
			if (!isdigit(entrada[i])) {
				valido = 0;
				break;
			}
		}

		if(!valido){
			printf("Erro: informe uma opção entre 1 e 9!\n\n");
			continue;
		}

		// Converte a entrada para inteiro
		opcao = atoi(entrada);

		// Verifica se o inteiro está entre 1 e 9
		if(opcao < 1 || opcao > 9){
			printf("Erro: informe uma opção entre 1 e 9!\n\n");
			continue;
		}

        switch (opcao) {
            case 1:
                printf("Informe o nome do arquivo de entrada:\n");
                fflush(stdout);
                scanf("%s", nome_arquivo_entrada);
                clearInputBuffer();

                arquivo = fopen(nome_arquivo_entrada, "w");
                if(arquivo){
                	fclose(arquivo);
                	printf("Arquivo criado com sucesso.\n\n");
                } else {
                	printf("Não foi possível criar o arquivo.\n\n");
                }

                break;

            case 2:

            	arquivo = fopen(nome_arquivo_entrada, "r");
            	if (arquivo){
            		fclose(arquivo);

					value_codigo = 0;

					while(value_codigo != 1){

						codigo_invalido = 0;

						printf("Informe o registro do novo vendedor:\n");
						printf("Código do vendedor:\n");
						fflush(stdout);
						scanf("%s", codigo_vendedor);

						if (!isDigit(codigo_vendedor)){
							printf("Erro: informe um código válido\n\n");
							codigo_invalido = 1;
							continue;
						}
						arquivo = fopen(nome_arquivo_entrada, "r");

						codigo_invalido = verificar_codigo(codigo_vendedor, arquivo);


						value_codigo = 1;

						if(codigo_invalido){
							value_codigo = 0;
						}

					}
					clearInputBuffer();

					printf("Nome do vendedor:\n");
					fflush(stdout);
					fgets(nome_vendedor, sizeof(nome_vendedor), stdin);
					nome_vendedor[strcspn(nome_vendedor, "\n")] = 0;
					if (!isString(nome_vendedor)){
						printf("Erro: informe um nome válido\n\n");
						break;
					}

					char input_venda[50];
					int value_venda = 0;

					while(value_venda != 1){

						printf("Valor da venda:\n");
						fflush(stdout);
						fgets(input_venda, sizeof(input_venda), stdin);
						input_venda[strcspn(input_venda, "\n")] = '\0';

						if (!isFloat(input_venda)) {
							printf("Erro: informe um valor válido\n\n");

						} else {
							valor_da_venda = strtof(input_venda, NULL);
							value_venda = 1;
						}
					}

					char input_mes[50];
					int value_mes = 0;

					while(value_mes != 1){

						do{
							printf("Informe um mes válido [1-12]:\n");
							fflush(stdout);
							fgets(input_mes, sizeof(input_mes), stdin);
							input_mes[strcspn(input_mes, "\n")] = '\0';

						}while(!verificar_intervalo(input_mes));

						if (!isInteger(input_mes)) {
							printf("Erro: informe um mes válido\n\n");
						} else {
							mes = strtol(input_mes, NULL, 10);
							value_mes = 1;

						}

					}

					arquivo = fopen(nome_arquivo_entrada, "a");
					if (arquivo) {

						fprintf(arquivo, "Código do vendedor: %s\n", codigo_vendedor);
						fprintf(arquivo, "Nome do vendedor: %s\n", nome_vendedor);
						fprintf(arquivo, "Valor da venda: %.2f\n", valor_da_venda);
						fprintf(arquivo, "Mes: %d\n\n", mes);

						fclose(arquivo);
						printf("Registro adicionado com sucesso.\n\n");
					} else {
						printf("Não foi possível abrir o arquivo para escrita.\n\n");
					}

            	}

            	else{
            		printf("Não há arquivo de entrada\n\n");
            	}

				break;

            case 3:

            	if(arquivo){
            		fclose(arquivo);
					printf("Selecione pelo número o vendedor que deseja excluir:\n");

					arquivo = fopen(nome_arquivo_entrada, "r");

					if (arquivo) {
					int i = 1;
					char opcao_excluir[100][20];

					while (fgets(linha, sizeof(linha), arquivo)) {
						char *posicao = strstr(linha, "Nome do vendedor: ");
						if (posicao != NULL) {
							posicao += strlen("Nome do vendedor: ");
							strcpy(nome_vendedor, posicao);
							nome_vendedor[strcspn(nome_vendedor, "\n")] = 0;
							printf("%d- %s\n", i, nome_vendedor);
							strcpy(opcao_excluir[i], nome_vendedor);
							i++;
						}
					}
					fclose(arquivo);

					printf("\nSelecione a opção desejada:\n");
					fflush(stdout);
					scanf("%d", &i);

					if (i < 1 || i >= 100 || opcao_excluir[i][0] == '\0') {
						printf("Opção inválida\n\n");
						break;
					}

					strcpy(excluir_escolhido, opcao_excluir[i]);

					arquivo = fopen(nome_arquivo_entrada, "r");
					arq = fopen("reserva.txt", "w");


					if (arquivo && arq) {
						int cont_linha = (i - 1) * 5;
						int cont = 1;

						while (fgets(linha, sizeof(linha), arquivo)) {

							if(cont_linha == 0){
								if(cont == 1){
									for(int j = 0; j < 5; j++){
										fgets(linha, sizeof(linha), arquivo);
									}
								}
							}
							if(cont == cont_linha){
								for(int j = 0; j < 5; j++){
									fgets(linha, sizeof(linha), arquivo);
								}
							}
							fprintf(arq, "%s", linha);
							cont++;
						}

						fclose(arquivo);
						fclose(arq);

						remove(nome_arquivo_entrada);
						rename("reserva.txt", nome_arquivo_entrada);

						printf("O vendedor %s foi excluído com sucesso.\n\n", excluir_escolhido);
					}
					else {
						if (arquivo) fclose(arquivo);
						if (arq) fclose(arq);
						printf("Não foi possível abrir os arquivos de leitura/escrita.\n\n");
					}
					}
            	}
            	else {
            		printf("Não há arquivo de entrada\n\n");
            	}

				break;

            case 4:
            	if (arquivo){
            		fclose(arquivo);
					printf("\nSelecione a venda que deseje alterar:\n");

					arquivo = fopen(nome_arquivo_entrada, "r");

					float opcao_venda;
					if(arquivo){

						int i = 1;
						float vendas[100];

						while(fgets(linha, sizeof(linha), arquivo)){
							if (sscanf(linha, "Valor da venda: %f", &valor_da_venda) == 1) {
								printf("%d- %.2f\n", i, valor_da_venda);
								vendas[i] = valor_da_venda;

								i++;
							}
						}

						printf("\nQual opção:\n");
						fflush(stdout);
						scanf("%d", &i);
						getchar();
						opcao_venda = vendas[i];
					}
					else{
						printf("Não há arquivo para ler");
					}

					fclose(arquivo);

					float valor_novo;
					char input[50];
					int value = 0;

					while(value != 1){

						printf("Qual o novo valor:\n");
						fflush(stdout);
						fgets(input, sizeof(input), stdin);
						input[strcspn(input, "\n")] = '\0';

						if (!isFloat(input)) {
							printf("Erro: informe um novo valor válido\n\n");
						} else {
							valor_novo = strtof(input, NULL);
							printf("Novo valor aceito: %.2f\n", valor_novo);
							value = 1;
						}

					}

					printf("\nTrocando o valor %.2f para %.2f\n\n", opcao_venda, valor_novo);

					arquivo = fopen(nome_arquivo_entrada, "r");
					arq = fopen("reserva.txt", "w");

					if(arquivo && arq){

						while(fgets(linha, sizeof(linha), arquivo)){

							if (sscanf(linha, "Valor da venda: %f", &valor_da_venda) == 1){
								if(valor_da_venda == opcao_venda){

									valor_da_venda = valor_novo;
									fprintf(arq, "Valor da venda: %.2f\n", valor_da_venda);
									continue;
								}

							}
							fprintf(arq, linha);

						}

					}

					fclose(arquivo);
					fclose(arq);

					arquivo = fopen(nome_arquivo_entrada, "w");
					arq = fopen("reserva.txt", "r");

					if (arquivo && arq) {
						while (fgets(linha, sizeof(linha), arq)) {
							fprintf(arquivo, linha);
						}
						fclose(arquivo);
						fclose(arq);

						remove("reserva.txt");

						printf("A troca do valor foi efetuada com sucesso.\n\n");
					}
					else {
						printf("Não foi possível abrir o arquivo de destino para escrita.\n\n");
					}
            	}
            	else{
            		printf("Não há arquivo de entrada\n\n");
            	}

				break;
            case 5:
                arquivo = fopen(nome_arquivo_entrada, "r");
                if (arquivo) {
                    while ((c = getc(arquivo)) != EOF) {
                        printf("%c", c);
                    }
                    fclose(arquivo);
                } else {
                    printf("Não há arquivo de entrada para ler.\n\n");
                }
                break;

            case 6:
                arq_saida = fopen(nome_arquivo_saida, "r");
                if (arq_saida) {
                    while ((c = getc(arq_saida)) != EOF) {
                        printf("%c", c);
                    }
                    fclose(arq_saida);
                } else {
                    printf("Não há arquivo de saída para ler.\n\n");
                }
                break;

            case 7:

            	if (arquivo){
            		fclose(arquivo);
					printf("Informe o nome do arquivo da saída padrão:\n");
					fflush(stdout);
					scanf("%s", nome_arquivo_saida);

					arq_saida = fopen(nome_arquivo_saida, "a");
					arquivo = fopen(nome_arquivo_entrada, "r");

					if(arq_saida && arquivo){

						while(fgets(linha, sizeof(linha), arquivo)){

							fprintf(arq_saida, linha);
						}
						printf("Arquivos repassados com sucesso!\n\n");
					}
					else{
						printf("Não há arquivo para escrever/ler\n\n");
					}
					fclose(arq_saida);
					fclose(arquivo);
            	}
            	else{
            		printf("Não há arquivo de entrada\n\n");
            	}

            	break;

            case 8:

            	if(arquivo){
            		fclose(arquivo);
					remove(nome_arquivo_entrada);

					printf("Arquivo de entrada removido com sucesso\n\n");
            	}
            	else{
            		printf("Não há arquivo de entrada\n\n");
            	}

            	break;

            case 9:

            	printf("\n-------FINALIZANDO-O-PROGRAMA-------\n");

            	break;

            default:

            	printf("Opção inválida. Tente novamente.\n\n");
            	break;
    		}
        }

    return 0;
}






