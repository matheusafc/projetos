
// Declaração das biblitecas utilizadas. 
#include<stdio.h> 
#include<math.h>
#include<locale.h> 
#include<string.h>
#include<stdlib.h>
	
	
	
	// Função que monta, imprime e escreve em arquivo, a tabela verdade. 
	void tabelaVerdade(int n, int valor_estado[], char nome_variaveis[][4], char nome_saida[4], FILE *pont_arq) { 
    int linhas = pow(2, n); // Calcula a quantidade de estados de acordo com o número de variáveis
    
    fprintf(pont_arq, "\nTabela Verdade para %d variáveis:\n\nEstado", n); // Escreve no arquivo posteriomente caso desejado pelo usuário
    printf( "\nTabela Verdade para %d variáveis:\n\nEstado", n); // Cabeçalho tabela 

    for (int i = 0; i < n; i++) {  // Loop para impressão dos nomes das variaveis 
        fprintf(pont_arq, "\t| %s", nome_variaveis[i]); // Escreve no arquivo posteriomente caso desejado pelo usuário
		printf( "\t| %s", nome_variaveis[i]); 
    }
    fprintf(pont_arq, "\t| %s \n",nome_saida); // Escreve no arquivo posteriomente caso desejado pelo usuário
	printf( "\t| %s \n",nome_saida);  // Loop para impressão dos nomes de saida
    
	for (int i = 0; i < linhas; i++) { // Loop para impressão de "#" 
        fprintf(pont_arq, "#%d \t", i); // Escreve no arquivo posteriomente caso desejado pelo usuário
        printf( "#%d \t", i);
        
        for (int j = n - 1; j >= 0; j--) { 
            fprintf(pont_arq, "| %d\t", (i >> j) & 1); // Escreve no arquivo posteriomente caso desejado pelo usuário
            printf( "| %d\t", (i >> j) & 1);
        }
        fprintf(pont_arq, "| %d\n", valor_estado[i]); // Escreve no arquivo posteriomente caso desejado pelo usuário
        printf( "| %d\n", valor_estado[i]);
    }
}
 
 // Função Mintermo e Maxtermo
	void gerarMintermoMaxtermo(int n, char nome_variaveis[][4], int valor_estado[], char* mintermo, char* maxtermo) { // Função que gera mintermo e maxtermo
    strcpy(mintermo, ""); // Zera a string do mintermo
    strcpy(maxtermo, ""); // Zera a string do maxtermo
    int linhas=pow(2, n);  // Calcula a quantidade de estados de acordo com o número de variáveis
 

    for (int i = 0; i < linhas; i++) { // Mintermos
        if (valor_estado[i] == 1) {
            if (strlen(mintermo) > 0) {
                strcat(mintermo, " + "); // Se não for o primeiro mintermo, adiciona o operador +
            }
            strcat(mintermo, "(");
            for (int j = 0; j < n; j++) {
                int bit = (i >> (n - j - 1)) & 1; // Valor do bit da variável
                if (bit == 1) {
                    strcat(mintermo, nome_variaveis[j]);  // Mintermo (variável)
                } else {
                    strcat(mintermo, "~");               // Negação no Mintermo
                    strcat(mintermo, nome_variaveis[j]); // Variável no Mintermo
                }
                if (j < n - 1) {
                    strcat(mintermo, " * "); // AND no Mintermo
                }
            }
            strcat(mintermo, ")");
        }
    }

    
    for (int i = 0; i < linhas; i++) { // Maxtermos
        if (valor_estado[i] == 0) {
            if (strlen(maxtermo) > 0) {
                strcat(maxtermo, " * "); // Se não for o primeiro maxtermo, adiciona o operador *
            }
            strcat(maxtermo, "(");
            for (int j = 0; j < n; j++) {
                int bit = (i >> (n - j - 1)) & 1; // Valor do bit da variável
                if (bit == 0) {
                    strcat(maxtermo, nome_variaveis[j]);  // Maxtermo (variável)
                } else {
                    strcat(maxtermo, "~");               // Negação no Maxtermo
                    strcat(maxtermo, nome_variaveis[j]); // Variável no Maxtermo
                }
                if (j < n - 1) {
                    strcat(maxtermo, " + "); // OR no Maxtermo
                }
            }
            strcat(maxtermo, ")");
        }
    }
}
	
	// Função salvar >>> caso solicitado salvar, SALVA O ARQUIVO NA PASTA DO .EXE 
	void salvar(int n, int valor_estado[], char nome_variaveis[][4], char nome_saida[4], FILE *pont_arq, char* mintermo, char* maxtermo, char save, char nome_arquivo[50]) { 
	
	
		while(save!= 's' && save!='S' && save!= 'n' && save!= 'N') // Validação para a opção de escolha do salvar ( Sim ou não )
	{
			printf("\nDeseja salvar? S=Sim / N=Não:"); 
    		scanf(" %c", &save);
	}
    	if(save == 'S' || save == 's') // Estrutura para opção SIM no salvar arquivo
		{
        	printf("\nDigite o nome do arquivo (Sem espaços): ");
        	while (getchar() != '\n');
        	scanf("%49s", nome_arquivo); // Leitura nome do arquivo limitado a 49 caracteres
			pont_arq = fopen(nome_arquivo, "w"); // abertura do arquivo 
        	if(pont_arq == NULL) // Validação se o arquivo foi aberto
		{
			printf("\n\nErro na abertura do arquivo!\n");
        }
        	
			else // Se aberto corretamente, salva no arquivo tabela, variáveis e as funções
        {
        	
        	tabelaVerdade(n, valor_estado, nome_variaveis, nome_saida, pont_arq); // Direcionando ponteiro do arquivo
        	fprintf(pont_arq, "\nFunção de Mintermo: %s\n", mintermo); // Escreve o titulo da função e escreve a função mintermo 
        	fprintf(pont_arq, "Função de Maxtermo: %s\n", maxtermo);  // Escreve o titulo da função e escreve a função maxtermo
        	fclose(pont_arq); // Fecha o arquivo
		
			system("cls");  // Limpar tela 
			system("color 02"); // Alterar cor das letras para verde
			printf("\n\nArquivo salvo com sucesso!");
		}
        
	}
	
	else 
	{
		system("cls"); // Limpar tela 
		printf("\n\nArquivo não salvo!"); // Impressão da mensagem de arquivo não salvo 
	}
	
}


int main() { 
	
    setlocale(LC_ALL, "Portuguese"); // Define o idioma para lingua portuguesa ( utilização de acentuação ) 
	
	// Declaração de variaveis 
	FILE *pont_arq; 
    char save, nome_arquivo[50];
    int n, valid;
    
    
    do { // Leitura e validação da quantidade de variaveis digitado pelo usuario 
	    printf("Digite o número de variáveis (2-7): ");
        valid=scanf("%d", &n);

        while (getchar() != '\n'); 

        if (valid != 1 || n < 2 || n > 7) {
            printf("Número inválido! Digite um número entre 2 e 7.\n\n");
            valid = 0; 
        }
    } while (valid != 1 || n < 2 || n > 7);

    char nome_variaveis[n][4], nome_saida[4]; // Declaração de variaveis 
    
    for(int i = 0; i < n; i++) {  // Leitura e validação dos nomes das variavéis 
        do {
            printf("Digite o nome da variável %d (máx. 3 caracteres): ", i + 1);
            scanf("%s", nome_variaveis[i]);

            if(strlen(nome_variaveis[i]) > 3) {
                printf("Nome inválido! O nome deve conter no máximo até 3 caracteres.\n");
            }
        } while(strlen(nome_variaveis[i]) > 3);
    }
    
    do  // Leitura e validação dos nomes de saida
    {

    printf("\nDigite um nome para a saída (máx. 3 caracteres): ");
    scanf("%s", nome_saida);
	
	if(strlen(nome_saida) > 3) {
                printf("Nome inválido! O nome deve conter no máximo até 3 caracteres.\n");
            }
        } while(strlen(nome_saida) > 3);
    
	
	int linhas = pow(2, n); // Declaração de variavel iniciada para calcular a quantidade de linhas(estados) da tabela verdade
    int valor_estado[linhas]; // Declaração de variavel

    for(int i = 0; i < linhas; i++) { // Leitura e validação do valor de cada estado 
       
       int valid_estado;
       
	    do {
            printf("\nSaída %s #%d (0-1): ",nome_saida, i);
           valid_estado=scanf("%d", &valor_estado[i]);
			while (getchar() != '\n'); 
			
            if(valid_estado != 1 || valor_estado[i] < 0 || valor_estado[i] > 1) 
			{
                printf("\nErro! O valor de saída deve ser 0 ou 1.\n");
            	valid_estado=0; 
			}
        } while(valid_estado != 1 || valor_estado[i] < 0 || valor_estado[i] > 1);
    }


	tabelaVerdade(n, valor_estado, nome_variaveis, nome_saida, pont_arq); // Gerar tabela verdade

    char mintermo[2048]; // Definir String para mintermo
    char maxtermo[2048]; // Definir String para maxtermo
    
    
    gerarMintermoMaxtermo(n, nome_variaveis, valor_estado, mintermo, maxtermo); // Gerar mintermo e maxtermo

    printf("\nFunção de Mintermo: %s\n", mintermo); // Imprimir mintermo
    printf("\nFunção de Maxtermo: %s\n", maxtermo); // Imprimir maxtermo
    
   	salvar(n, valor_estado,  nome_variaveis,  nome_saida, pont_arq,  mintermo, maxtermo,  save,  nome_arquivo); // Chama a função salvar
   	

    return 0;
}

