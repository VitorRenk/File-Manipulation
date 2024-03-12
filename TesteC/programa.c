#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char codigo_vendedor[5];
    char nome_vendedor[20];
    float valor_da_venda;
    int mes;
    char nome_arquivo_entrada[10];
    char nome_arquivo_saida[10];
    int opcao;
    char linha[100];
    FILE *arquivo;
    FILE *arq;
    char excluir_escolhido[20];


    while (opcao != 7) {

    	printf("----------------OPÇÕES------------------\n\n");
		printf("1- Criar o arquivo de dados\n");
		printf("2- Incluir um determinado registro no arquivo\n");
		printf("3- Excluir um determinado vendedor no arquivo\n");
		printf("4- Alterar o valor de uma venda no arquivo\n");
		printf("5- Imprimir os registros na saída padrão\n");
		printf("6- Excluir o arquivo de dados\n");
		printf("7- Finalizar o programa\n\n");

        printf("Selecione sua opção:\n");
        fflush(stdout);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe o nome do arquivo de entrada:\n");
                fflush(stdout);
                scanf("%s", nome_arquivo_entrada);
                getchar();

                arquivo = fopen(nome_arquivo_entrada, "w");
                fclose(arquivo);
                break;

            case 2:
                arquivo = fopen(nome_arquivo_entrada, "a");
                if (arquivo) {
                    printf("Informe o registro:\n");
                    printf("Código do vendedor:\n");
                    fflush(stdout);
                    scanf("%s", codigo_vendedor);
                    getchar();

                    printf("Nome do vendedor:\n");
                    fflush(stdout);
                    scanf("%s", nome_vendedor);
                    getchar();

                    printf("Valor da venda:\n");
                    fflush(stdout);
                    scanf("%f", &valor_da_venda);

                    printf("Informe o mes:\n");
                    fflush(stdout);
                    scanf("%d", &mes);

                    fprintf(arquivo, "Código do vendedor: %s\n", codigo_vendedor);
                    fprintf(arquivo, "Nome do vendedor: %s\n", nome_vendedor);
                    fprintf(arquivo, "Valor da venda: %.2f\n", valor_da_venda);
                    fprintf(arquivo, "Mes: %d\n", mes);
                    fprintf(arquivo, "\n");

                    fclose(arquivo);
                } else {
                    printf("Não há arquivo para abrir");
                }
                break;

            case 3:
            	printf("Selecione o vendedor que deseja excluir:\n");
				arquivo = fopen(nome_arquivo_entrada, "r");

				if (arquivo) {
					int i = 1;
					char opcao_excluir[100][20];

					while (fgets(linha, sizeof(linha), arquivo)) {
						if (sscanf(linha, "Nome do vendedor: %s", nome_vendedor) == 1) {
							printf("%d- %s\n", i, nome_vendedor);
							strcpy(opcao_excluir[i], nome_vendedor);
							i++;
						}
					}

					printf("\nSelecione a opção desejada:\n");
					fflush(stdout);
					scanf("%d", &i);
					strcpy(excluir_escolhido, opcao_excluir[i]);

					fclose(arquivo);

					arquivo = fopen(nome_arquivo_entrada, "r");
					arq = fopen("reserva.txt", "w");

					if (arquivo && arq) {
						int contador = 0;
						int linha_desejada;
						while (fgets(linha, sizeof(linha), arquivo)) {
							contador++;
							if (strstr(linha, excluir_escolhido)) {
								linha_desejada = contador - 2;
							}

						}


						fclose(arquivo);
						fclose(arq);

						arquivo = fopen(nome_arquivo_entrada, "r");
						arq = fopen("reserva.txt", "w");

						contador = 0;
						while (fgets(linha, sizeof(linha), arquivo)) {
							contador++;
							if (contador == linha_desejada) {

								for(int i = 0; i < 5; i++){
									fgets(linha, sizeof(linha), arquivo);

								}

							}
							fprintf(arq, linha);
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

							printf("O vendedor %s foi excluído com sucesso.\n", excluir_escolhido);
						} else {
							printf("Não foi possível abrir o arquivo de destino para escrita.\n");
						}
					} else {
						printf("Não foi possível abrir os arquivos de leitura/escrita.\n");
					}
				} else {
					printf("Não há arquivo para ler.\n");
				}
				break;

            case 4:

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
					opcao_venda = vendas[i];
            	}
            	else{
            		printf("Não há arquivo para ler");
            	}

            	fclose(arquivo);

            	float valor_novo;

            	printf("\nQual o novo valor:\n");
            	fflush(stdout);
            	scanf("%f", &valor_novo);

            	printf("\nopcao venda: %.2f\n", opcao_venda);
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



					printf("A troca do valor foi efetuada com sucesso.\n");
				} else {
					printf("Não foi possível abrir o arquivo de destino para escrita.\n");
				}

            	break;

            case 5:

            	printf("Informe a saída padrão do arquivo:\n");
            	fflush(stdout);
            	scanf("%s", nome_arquivo_saida);

            	FILE *arq_saida = fopen(nome_arquivo_saida, "w");
            	arquivo = fopen(nome_arquivo_entrada, "r");

            	if(arq_saida && arquivo){

            		while(fgets(linha, sizeof(linha), arquivo)){

            			fprintf(arq_saida, linha);
            		}
            		printf("Arquivos repassados com sucesso!");
            	}
            	else{
            		printf("Não há arquivo para escrever/ler\n");
            	}
            	fclose(arq_saida);
            	fclose(arquivo);

            	break;

            case 6:

            	remove(nome_arquivo_entrada);

            	printf("Arquivo de entrada removido com sucesso");

            	break;

            case 7:

            	printf("\n-------FINALIZANDO-O-PROGRAMA-------\n");

            	break;

            default:

            	break;
    		}
        }

    return 0;
}






