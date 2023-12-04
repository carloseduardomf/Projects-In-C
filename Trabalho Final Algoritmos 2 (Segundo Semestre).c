/******************************************************************************

Aluno: Carlos Eduardo Martins Ferreira RA: 2576163
Aluno: Vitor Leandro RA: 2531810 

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUMALUNO 10

// Estrutura tipo_alunos:
typedef struct {
    int RA;
    char nome[50];
    float p1, p2, p3, mf;
} tipo_alunos; 



//Fun√ß√µes
void menu();
tipo_alunos *alocaAluno(int totalalunos);                                   // Fun√ß√£o para alocar dinamicamente um vetor de alunos.
tipo_alunos *realocaAluno(tipo_alunos *Aluno, int totalalunos);             // Fun√ß√£o para realocar dinamicamente um vetor de alunos.
void cadastraAluno(tipo_alunos *Aluno, int *totalalunos, int *totalFlag);   // Fun√ß√£o para cadastrar um n√∫mero indeterminado de alunos.
void maiormediageral(tipo_alunos *Aluno, int totalalunos);                  // Fun√ß√£o para encontrar aluno com a maior m√©dia geral.
void menormediageral(tipo_alunos *Aluno, int totalalunos);                  // Fun√ß√£o para encontrar o aluno com a menor m√©dia geral.
void relatorioAlunos(tipo_alunos *Aluno, int totalalunos);                  // Fun√ß√£o para verificar a situa√ß√£o dos alunos (aprovado ou reprovado).
void mostrarAlunos(tipo_alunos *Aluno, int totalFlag);                      // Fun√ß√£o para exibir na tela os dados do vetor.
void alterarAluno(tipo_alunos *Aluno, int totalalunos);                     // Fun√ß√£o criada pela equipe.



// Fun√ß√£o principal:
int main() {
    
    //Vari√°veis
    int flag = 1, totalalunos, totalFlag = 0;
    tipo_alunos *Aluno;
    totalalunos = NUMALUNO;
    
    //Alocando vetor:
    Aluno = alocaAluno(totalalunos);
    
    //Menu:
    while(flag!=0){
        
        //Menu 
        menu();
        printf("Escolha: ");
        scanf("%d", &flag);
        
        switch(flag){
            case 1:
                //Realoca quando cheio:
    			if(totalalunos == totalFlag){
        
        			Aluno = realocaAluno(Aluno, totalalunos);
        			
        			totalalunos+=NUMALUNO;
    			}
				cadastraAluno(Aluno, &totalalunos, &totalFlag);
                break;
            case 2:
                if(totalFlag==0){
                    printf("\n\n--------------Maior-M√©dia-------------\n");
                    printf("Nenhum aluno cadastrado.\n");
                    printf("--------------------------------------\n");
                }else{
                    maiormediageral(Aluno, totalFlag);
                }
                break;
            case 3:
                if(totalFlag==0){
                    printf("\n\n--------------Menor-M√©dia-------------\n");
                    printf("Nenhum aluno cadastrado.\n");
                    printf("--------------------------------------\n");
                }else{
                    menormediageral(Aluno, totalFlag);
                }
                break;
            case 4:
                if(totalFlag!=0){
					relatorioAlunos(Aluno, totalFlag);
				}else{
					printf("-----------------------------------------------------\n\n");
					printf("Nenhum aluno cadastrado. Cadastre e tente novamente.\n\n");
					printf("-----------------------------------------------------\n");
				}
				break;
            case 5:
                if(totalFlag!=0){
					mostrarAlunos(Aluno, totalFlag);
				}else{
					printf("-----------------------------------------------------\n\n");
					printf("Nenhum aluno cadastrado. Cadastre e tente novamente.\n\n");
					printf("-----------------------------------------------------\n");
				}
                break;
            case 6:
            	if(totalFlag!=0){
					alterarAluno(Aluno, totalFlag);
				}else{
					printf("-----------------------------------------------------\n\n");
					printf("Nenhum aluno cadastrado. Cadastre e tente novamente.\n\n");
					printf("-----------------------------------------------------\n");
				}
				break;
            case 0:
                break;
            default:
                printf("---------------------------\n");
                printf("Tente novamente: \n");
                printf("Escolha: ");
                scanf("%d", &flag);
                printf("---------------------------\n");
                break;
        }
        if(flag!=1&&flag!=4&&flag!=0){
			printf("1- Voltar ao menu\n0- Sair\n");
			printf("Escolha: ");
            scanf("%d", &flag);
            printf("-------------------------------------\n");
            if(flag!=1&&flag!=0){
				do{
					printf("Tente novamente:\n1- Voltar ao menu\n0- Sair\n");
            		printf("Escolha: ");
					scanf("%d", &flag);
            		printf("-------------------------------------\n");
				}while(flag!=1&&flag!=0);
			}
        }
    }
    printf("\n\n---------------------------");
    printf("\nEncerrando...");
    printf("\n---------------------------\n");
    
    
    //Liberando vetor:
    free(Aluno);
    
    return 0;
}



// Fun√ß√µes:

// Fun√ß√£o menu
void menu(){
    printf("\n\n--------------------Menu--------------------\n");
    printf("1- Cadastrar alunos.       \n\n");
    printf("2- Aluno com maior m√©dia.  \n\n");
    printf("3- Aluno com menor m√©dia.  \n\n");
    printf("4- Aprovados/Reprovados.   \n\n");
    printf("5- Mostrar alunos.         \n\n");
    printf("6- Alterar aluno.          \n\n");
    printf("0- Sair.                   \n");
    printf("--------------------------------------------\n");
}

// Fun√ß√£o AlocaAluno
tipo_alunos *alocaAluno(int totalalunos) {
    
    tipo_alunos *Aluno = (tipo_alunos *)malloc(totalalunos * sizeof(tipo_alunos));
    
    if(Aluno == NULL){
		printf("Erro: Falha na aloca√ß√£o de mem√≥ria.\n");
	}
    
    return Aluno;
}

// Fun√ß√£o RealocaAluno
tipo_alunos *realocaAluno(tipo_alunos *Aluno, int totalalunos) {
    
    Aluno = (tipo_alunos *)realloc(Aluno, (totalalunos + NUMALUNO) * sizeof(tipo_alunos));
    
    if(Aluno == NULL){
		printf("Erro: Falha na aloca√ß√£o de mem√≥ria.\n");
	}
    
    return Aluno;
}

// Fun√ß√£o CadastraAluno
void cadastraAluno(tipo_alunos *Aluno, int *totalalunos, int *totalFlag) {
    
    int flag, i, j;
    flag = 1;
    
   
    while(flag==1){    
        //Cadastro:
        printf("\n\n--------------Cadastro--------------\n");
        
        printf("Digite o RA do aluno: \n");
        scanf("%d", &Aluno[*totalFlag].RA);
        
        //Verifica se o RA j√° foi cadastrado:
        for(i=0;i<*totalFlag;i++){
            if(Aluno[i].RA==Aluno[*totalFlag].RA){
                printf("RA j√° cadastrado, tente novamente: \n");
                scanf("%d", &Aluno[*totalFlag].RA);
            }
        }
        
        getchar();
        
        printf("Digite o nome do aluno: \n");
        fgets(Aluno[*totalFlag].nome, sizeof(Aluno[*totalFlag].nome), stdin);
        
        //Tira o \n do fgets:
        for (j=0; Aluno[*totalFlag].nome[j] != '\0'; j++) {
            if (Aluno[*totalFlag].nome[j] == '\n') {
                Aluno[*totalFlag].nome[j] = '\0';
                break;  
            }
        }
        
        printf("Digite a nota da primeira prova: \n");
        scanf("%f", &Aluno[*totalFlag].p1);
        
        //Confere se a nota est√° entre 0 e 10:
        if(Aluno[*totalFlag].p1>10||Aluno[*totalFlag].p1<0){
            do{
                printf("Nota inv√°lida, tente novamente:\n");
                scanf("%f", &Aluno[*totalFlag].p1);
            }while(Aluno[*totalFlag].p1>10);
        }
        
        printf("Digite a nota da segunda prova: \n");
        scanf("%f", &Aluno[*totalFlag].p2);
        
        //Confere se a nota est√° entre 0 e 10:
        if(Aluno[*totalFlag].p2>10||Aluno[*totalFlag].p2<0){
            do{
                printf("Nota inv√°lida, tente novamente:\n");
                scanf("%f", &Aluno[*totalFlag].p2);
            }while(Aluno[*totalFlag].p2>10);
        }
     
        printf("Digite a nota da terceira prova: \n");
        scanf("%f", &Aluno[*totalFlag].p3);
        
        //Confere se a nota est√° entre 0 e 10:
        if(Aluno[*totalFlag].p3>10||Aluno[*totalFlag].p3<0){
            do{
                printf("Nota inv√°lida, tente novamente:\n");
                scanf("%f", &Aluno[*totalFlag].p3);
            }while(Aluno[*totalFlag].p3>10);
        }
     
        // Calcula a m√©dia final do novo aluno
        Aluno[*totalFlag].mf = (Aluno[*totalFlag].p1 + Aluno[*totalFlag].p2 + Aluno[*totalFlag].p3) / 3.0;
        
        *totalFlag += 1;
        
        printf("-------------------------------------\n");
        printf("1- Continuar\n0- Voltar ao menu\nEscolha: ");
        scanf("%d", &flag);
        printf("-------------------------------------\n");
        
        while(flag!=1&&flag!=0){
            printf("------------Tente-Novamente---------\n");
            printf("1- Continuar\n0- Voltar ao menu\nEscolha: ");
            scanf("%d", &flag);
            printf("-------------------------------------\n");
        }
    }
}

//Fun√ß√£o maiormediageral
void maiormediageral(tipo_alunos *Aluno, int totalFlag){
    
    int i;
    float maiormedia = -1;
    
    for(i=0;i<totalFlag;i++){
        if(Aluno[i].mf>maiormedia){
            maiormedia=Aluno[i].mf;
        }
    }
    
    printf("\n\n--------------Maior-M√©dia-------------\n");
    
    for(i=0;i<totalFlag;i++){
        if(Aluno[i].mf==maiormedia){
            printf("RA: %d\n", Aluno[i].RA);
            printf("Nota: %.2f\n", Aluno[i].mf);
            printf("--------------------------------------\n");
        }
    }
}

// Fun√ß√£o menormediageral
void menormediageral(tipo_alunos *Aluno, int totalFlag){
    
    int i;
    float menormedia = 11;
    
    for(i=0;i<totalFlag;i++){
        if(Aluno[i].mf<menormedia){
            menormedia=Aluno[i].mf;
        }
    }
    
    printf("\n\n--------------Menor-M√©dia-------------\n");
    
    for(i=0;i<totalFlag;i++){
        if(Aluno[i].mf==menormedia){
            printf("RA: %d\n", Aluno[i].RA);
            printf("Nota: %.2f\n", Aluno[i].mf);
            printf("--------------------------------------\n");
        }
    }
}

// Fun√ß√£o relatorioAlunos
void relatorioAlunos(tipo_alunos *Aluno, int totalFlag){
    int i, N = 1, AE;
    while(N != 0){
    	AE=0;
        printf("\n\n--------------Relat√≥rio---------------\n");
        printf("1- Aprovados\n2- Reprovados\n0- Voltar ao menu\n");
        printf("--------------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &N);
        if(N!=0){
            for (i = 0; i < totalFlag; i++) {
                if(i==0 && N==1){
                    printf("\n\n--------------Aprovados---------------\n");
                }
                if(i==0 && N==2){
                        printf("\n\n-------------Reprovados---------------\n");
                }
                if (N == 1 && Aluno[i].mf >= 6.0) {
                    printf("Aluno(RA): %d\n", Aluno[i].RA);
                    AE++;
                }else if(N == 2 && Aluno[i].mf < 6.0){
                    printf("Aluno(RA): %d\n", Aluno[i].RA);
                    AE++;
                }
            }
            printf("Total de alunos encontrados: %d", AE);
            printf("\n--------------------------------------\n");
        }
        
        
    }
}

// Fun√ß√£o mostrarAlunos
void mostrarAlunos(tipo_alunos *Aluno, int totalFlag){
    
    int i;
    
    printf("\n------------------Alunos---------------------\n");
    for(i=0;i<totalFlag;i++){
        
        
        printf("RA do aluno:             %d\n", Aluno[i].RA);
     
        printf("Nome do aluno:           %s\n", Aluno[i].nome);
     
        printf("Nota da primeira prova:  %.2f\n", Aluno[i].p1);
     
        printf("Nota da segunda prova:   %.2f\n", Aluno[i].p2);
     
        printf("Nota da terceira prova:  %.2f\n", Aluno[i].p3);
        
        printf("Nota final:              %.2f\n", Aluno[i].mf);
        
        printf("---------------------------------------------\n");
    }
}

// Fun√ß√£o alterarAluno
void alterarAluno(tipo_alunos *Aluno, int totalFlag) {
    int ra, i, j, flag;
    
	printf("\n--------------Alterar Alunos---------------\n");
    
	// Solicitar RA do aluno a ser alterado
    printf("\nDigite o RA do aluno que deseja alterar: ");
    scanf("%d", &ra);
    
    // Procurar o aluno com o RA especificado
    for (i = 0; i < totalFlag; i++) {
        if (Aluno[i].RA == ra) {
            printf("\n---------------Dados Atuais----------------\n\n");
            printf("RA do aluno:             %d\n\n", Aluno[i].RA);
            printf("Nome do aluno:           %s\n\n", Aluno[i].nome);
            printf("Nota da primeira prova:  %.2f\n\n", Aluno[i].p1);
            printf("Nota da segunda prova:   %.2f\n\n", Aluno[i].p2);
            printf("Nota da terceira prova:  %.2f\n\n", Aluno[i].p3);
            printf("--------------------------------------------\n\n");
            
            // Solicitar novos dados
            printf("Insira os novos dados:\n\n");
            
			printf("--------------------------------------------\n\n");
            	
            getchar(); 
            
            printf("Nome do aluno: ");
            fgets(Aluno[i].nome, sizeof(Aluno[i].nome), stdin);
            
            for (j = 0; Aluno[i].nome[j] != '\0'; j++) {
                if (Aluno[i].nome[j] == '\n') {
                    Aluno[i].nome[j] = '\0';
                    break;
                }
            }
         
            printf("Nota da primeira prova: ");
            scanf("%f", &Aluno[i].p1);
         
            printf("Nota da segunda prova: ");
            scanf("%f", &Aluno[i].p2);
        
            printf("Nota da terceira prova: ");
            scanf("%f", &Aluno[i].p3);
            
            printf("----------------------------------------\n\n");
        
            // Recalcular a m√©dia final com os novos dados
            Aluno[i].mf = (Aluno[i].p1 + Aluno[i].p2 + Aluno[i].p3) / 3.0;
        
            printf("\n----------Dados Atualizados------------\n");
            printf("RA do aluno:             %d\n", Aluno[i].RA);
            printf("Nome do aluno:           %s\n", Aluno[i].nome);
            printf("Nota da primeira prova:  %.2f\n", Aluno[i].p1);
            printf("Nota da segunda prova:   %.2f\n", Aluno[i].p2);
            printf("Nota da terceira prova:  %.2f\n", Aluno[i].p3);
            printf("Nova nota final:         %.2f\n", Aluno[i].mf);
            printf("-------------------------------------------\n");
        
            return; 
        }
    }

    // Se o RA n√£o for encontrado
    printf("\nAluno com RA %d n√£o encontrado.\n", ra);
}
/******************************************************************************

Aluno: Carlos Eduardo Martins Ferreira RA: 2576163
Aluno: Vitor Leandro RA: 2531810 

ES42B - Algoritmos 2 - ES21 (2023_02)
Trabalho Final
Profa. Rosangela de F·tima Pereira Marquesone - romarquesone@utfpr.edu.br
Crie uma estrutura (tipo_alunos) representando os alunos do curso de Engenharia de Software
da UTFPR. A estrutura deve conter:
? RA do aluno (inteiro)
? nome do aluno
? nota da primeira prova
? nota da segunda prova
? nota da terceira prova
? mÈdia final
Escreva um programa em Linguagem C que contenha um vetor de alunos, do tipo da estrutura
criada com os dados ao inÌcio da quest„o.
O programa deve contemplar os seguintes itens:
? A alocaÁ„o inicial do vetor de alunos deve conter dimens„o m·xima 10, e a posterior
verificaÁ„o da necessidade de realocaÁ„o de memÛria extra, sempre que este vetor
atingir sua capacidade m·xima.
? A criaÁ„o de uma funÁ„o main(), que realize a chamada das funÁıes.
ApÛs isso, dever· ser desenvolvido as seguintes funÁıes:
1. (1 ponto) FunÁ„o para alocar dinamicamente um vetor de alunos. A funÁ„o recebe a
dimens„o do vetor e retorna o endereÁo de memÛria do vetor alocado.
2. (2 pontos) FunÁ„o para realocar dinamicamente um vetor de alunos. A funÁ„o recebe o
vetor que ser· realocado e seu novo tamanho, e devolve o endereÁo de memÛria do
vetor realocado.
3. (2 pontos) FunÁ„o para cadastrar um n˙mero indeterminado de alunos. A funÁ„o
recebe o vetor de alunos, e a posiÁ„o na qual o novo aluno deve ser cadastrado.
4. (1 ponto) FunÁ„o para encontrar o aluno com maior nota da primeira prova. A funÁ„o
recebe o vetor de alunos, e devolve o RA do aluno encontrado.
5. (1 ponto) FunÁ„o para encontrar o aluno com a menor mÈdia geral. A funÁ„o recebe o
vetor de alunos, e devolve o RA do aluno encontrado.
6. (1 ponto) FunÁ„o para verificar se um aluno foi aprovado ou reprovado, considerando o
valor 6 para aprovaÁ„o. A funÁ„o recebe o vetor de alunos e um valor numÈrico que
indica o que deve ser procurado (1 para aprovados, 2 para reprovados), e devolve o RA
do aluno encontrado.
7. (1 ponto) FunÁ„o para exibir na tela os dados do vetor. A funÁ„o recebe o vetor cujo
conte˙do ser· impresso, e a dimens„o deste vetor.
8. (1 ponto) FunÁ„o criada pela equipe que realize alguma an·lise sobre os dados da
estrutura.
InstruÁıes:
? O trabalho poder· ser desenvolvido em dupla. Insira o nome e RA da dupla no
cabeÁalho do cÛdigo, em formato de coment·rio.
? Qualquer indÌcio de pl·gio do cÛdigo (cÛpia de trabalho, cÛpia da web, chatgpt, Ö) ser·
atribuÌda nota zero.
? A funÁ„o que n„o realizar o que foi solicitado receber· nota zero.
InformaÁıes sobre a entrega:
? Dever· ser entregue um arquivo .c com o cÛdigo desenvolvido.
? A entrega dever· ocorrer atÈ o dia 01/12, ‡s 23h59

*******************************************************************************/