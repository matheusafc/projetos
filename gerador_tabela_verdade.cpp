// Matheus Alexandre Farias Cioca  RA  1140482422031
// Matheus de Oliveira             RA  1140482422025
// Pedro Aguirre                   RA  1140482422032


// Declara��o das biblitecas utilizadas. 
#include<stdio.h> 
#include<math.h>
#include<locale.h> 
#include<string.h>
#include<stdlib.h>
	
	
	
	// Fun��o que monta, imprime e escreve em arquivo, a tabela verdade. 
	void tabelaVerdade(int n, int valor_estado[], char nome_variaveis[][4], char nome_saida[4], FILE *pont_arq) { 
    int linhas = pow(2, n); // Calcula a quantidade de estados de acordo com o n�mero de vari�veis
    
    fprintf(pont_arq, "\nTabela Verdade para %d vari�veis:\n\nEstado", n); // Escreve no arquivo posteriomente caso desejado pelo usu�rio
    printf( "\nTabela Verdade para %d vari�veis:\n\nEstado", n); // Cabe�alho tabela 

    for (int i = 0; i < n; i++) {  // Loop para impress�o dos nomes das variaveis 
        fprintf(pont_arq, "\t| %s", nome_variaveis[i]); // Escreve no arquivo posteriomente caso desejado pelo usu�rio
		printf( "\t| %s", nome_variaveis[i]); 
    }
    fprintf(pont_arq, "\t| %s \n",nome_saida); // Escreve no arquivo posteriomente caso desejado pelo usu�rio
	printf( "\t| %s \n",nome_saida);  // Loop para impress�o dos nomes de saida
    
	for (int i = 0; i < linhas; i++) { // Loop para impress�o de "#" 
        fprintf(pont_arq, "#%d \t", i); // Escreve no arquivo posteriomente caso desejado pelo usu�rio
        printf( "#%d \t", i);
        
        for (int j = n - 1; j >= 0; j--) { 
            fprintf(pont_arq, "| %d\t", (i >> j) & 1); // Escreve no arquivo posteriomente caso desejado pelo usu�rio
            printf( "| %d\t", (i >> j) & 1);
        }
        fprintf(pont_arq, "| %d\n", valor_estado[i]); // Escreve no arquivo posteriomente caso desejado pelo usu�rio
        printf( "| %d\n", valor_estado[i]);
    }
}
 
 // Fun��o Mintermo e Maxtermo
	void gerarMintermoMaxtermo(int n, char nome_variaveis[][4], int valor_estado[], char* mintermo, char* maxtermo) { // Fun��o que gera mintermo e maxtermo
    strcpy(mintermo, ""); // Zera a string do mintermo
    strcpy(maxtermo, ""); // Zera a string do maxtermo
    int linhas=pow(2, n);  // Calcula a quantidade de estados de acordo com o n�mero de vari�veis
 

    for (int i = 0; i < linhas; i++) { // Mintermos
        if (valor_estado[i] == 1) {
            if (strlen(mintermo) > 0) {
                strcat(mintermo, " + "); // Se n�o for o primeiro mintermo, adiciona o operador +
            }
            strcat(mintermo, "(");
            for (int j = 0; j < n; j++) {
                int bit = (i >> (n - j - 1)) & 1; // Valor do bit da vari�vel
                if (bit == 1) {
                    strcat(mintermo, nome_variaveis[j]);  // Mintermo (vari�vel)
                } else {
                    strcat(mintermo, "~");               // Nega��o no Mintermo
                    strcat(mintermo, nome_variaveis[j]); // Vari�vel no Mintermo
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
                strcat(maxtermo, " * "); // Se n�o for o primeiro maxtermo, adiciona o operador *
            }
            strcat(maxtermo, "(");
            for (int j = 0; j < n; j++) {
                int bit = (i >> (n - j - 1)) & 1; // Valor do bit da vari�vel
                if (bit == 0) {
                    strcat(maxtermo, nome_variaveis[j]);  // Maxtermo (vari�vel)
                } else {
                    strcat(maxtermo, "~");               // Nega��o no Maxtermo
                    strcat(maxtermo, nome_variaveis[j]); // Vari�vel no Maxtermo
                }
                if (j < n - 1) {
                    strcat(maxtermo, " + "); // OR no Maxtermo
                }
            }
            strcat(maxtermo, ")");
        }
    }
}
	
	// Fun��o salvar >>> caso solicitado salvar, SALVA O ARQUIVO NA PASTA DO .EXE 
	void salvar(int n, int valor_estado[], char nome_variaveis[][4], char nome_saida[4], FILE *pont_arq, char* mintermo, char* maxtermo, char save, char nome_arquivo[50]) { 
	
	
		while(save!= 's' && save!='S' && save!= 'n' && save!= 'N') // Valida��o para a op��o de escolha do salvar ( Sim ou n�o )
	{
			printf("\nDeseja salvar? S=Sim / N=N�o:"); 
    		scanf(" %c", &save);
	}
    	if(save == 'S' || save == 's') // Estrutura para op��o SIM no salvar arquivo
		{
        	printf("\nDigite o nome do arquivo (Sem espa�os): ");
        	while (getchar() != '\n');
        	scanf("%49s", nome_arquivo); // Leitura nome do arquivo limitado a 49 caracteres
			pont_arq = fopen(nome_arquivo, "w"); // abertura do arquivo 
        	if(pont_arq == NULL) // Valida��o se o arquivo foi aberto
		{
			printf("\n\nErro na abertura do arquivo!\n");
        }
        	
			else // Se aberto corretamente, salva no arquivo tabela, vari�veis e as fun��es
        {
        	
        	tabelaVerdade(n, valor_estado, nome_variaveis, nome_saida, pont_arq); // Direcionando ponteiro do arquivo
        	fprintf(pont_arq, "\nFun��o de Mintermo: %s\n", mintermo); // Escreve o titulo da fun��o e escreve a fun��o mintermo 
        	fprintf(pont_arq, "Fun��o de Maxtermo: %s\n", maxtermo);  // Escreve o titulo da fun��o e escreve a fun��o maxtermo
        	fclose(pont_arq); // Fecha o arquivo
		
			system("cls");  // Limpar tela 
			system("color 02"); // Alterar cor das letras para verde
			printf("\n\nArquivo salvo com sucesso!");
		}
        
	}
	
	else 
	{
		system("cls"); // Limpar tela 
		printf("\n\nArquivo n�o salvo!"); // Impress�o da mensagem de arquivo n�o salvo 
	}
	
}


int main() { 
	
    setlocale(LC_ALL, "Portuguese"); // Define o idioma para lingua portuguesa ( utiliza��o de acentua��o ) 
	
	// Declara��o de variaveis 
	FILE *pont_arq; 
    char save, nome_arquivo[50];
    int n, valid;
    
    
    do { // Leitura e valida��o da quantidade de variaveis digitado pelo usuario 
	    printf("Digite o n�mero de vari�veis (2-7): ");
        valid=scanf("%d", &n);

        while (getchar() != '\n'); 

        if (valid != 1 || n < 2 || n > 7) {
            printf("N�mero inv�lido! Digite um n�mero entre 2 e 7.\n\n");
            valid = 0; 
        }
    } while (valid != 1 || n < 2 || n > 7);

    char nome_variaveis[n][4], nome_saida[4]; // Declara��o de variaveis 
    
    for(int i = 0; i < n; i++) {  // Leitura e valida��o dos nomes das variav�is 
        do {
            printf("Digite o nome da vari�vel %d (m�x. 3 caracteres): ", i + 1);
            scanf("%s", nome_variaveis[i]);

            if(strlen(nome_variaveis[i]) > 3) {
                printf("Nome inv�lido! O nome deve conter no m�ximo at� 3 caracteres.\n");
            }
        } while(strlen(nome_variaveis[i]) > 3);
    }
    
    do  // Leitura e valida��o dos nomes de saida
    {

    printf("\nDigite um nome para a sa�da (m�x. 3 caracteres): ");
    scanf("%s", nome_saida);
	
	if(strlen(nome_saida) > 3) {
                printf("Nome inv�lido! O nome deve conter no m�ximo at� 3 caracteres.\n");
            }
        } while(strlen(nome_saida) > 3);
    
	
	int linhas = pow(2, n); // Declara��o de variavel iniciada para calcular a quantidade de linhas(estados) da tabela verdade
    int valor_estado[linhas]; // Declara��o de variavel

    for(int i = 0; i < linhas; i++) { // Leitura e valida��o do valor de cada estado 
       
       int valid_estado;
       
	    do {
            printf("\nSa�da %s #%d (0-1): ",nome_saida, i);
           valid_estado=scanf("%d", &valor_estado[i]);
			while (getchar() != '\n'); 
			
            if(valid_estado != 1 || valor_estado[i] < 0 || valor_estado[i] > 1) 
			{
                printf("\nErro! O valor de sa�da deve ser 0 ou 1.\n");
            	valid_estado=0; 
			}
        } while(valid_estado != 1 || valor_estado[i] < 0 || valor_estado[i] > 1);
    }


	tabelaVerdade(n, valor_estado, nome_variaveis, nome_saida, pont_arq); // Gerar tabela verdade

    char mintermo[2048]; // Definir String para mintermo
    char maxtermo[2048]; // Definir String para maxtermo
    
    
    gerarMintermoMaxtermo(n, nome_variaveis, valor_estado, mintermo, maxtermo); // Gerar mintermo e maxtermo

    printf("\nFun��o de Mintermo: %s\n", mintermo); // Imprimir mintermo
    printf("\nFun��o de Maxtermo: %s\n", maxtermo); // Imprimir maxtermo
    
   	salvar(n, valor_estado,  nome_variaveis,  nome_saida, pont_arq,  mintermo, maxtermo,  save,  nome_arquivo); // Chama a fun��o salvar
   	

    return 0;
}

