/*
Laboratório de informática(ES31C): Trabalho Final - Projeto (Controle Financeiro de Vendas).
Alunos: Carlos Eduardo Martins Ferreira / Luccas Maia Hessel.  Turma: ES11B
Professor: Francisco Pereira Junior (Thesko).             
Última alteração: 26/06/2023.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Constantes (ATENÇÃO: A constante "dias" representa o número de dias dobrado, sendo posições impáres do vetor o valor de custo e pares o de venda).
#define dias 60 
#define vendedores 10

//Matriz principal e Variáveis muito utilizadas
int m[vendedores][dias], soma, flag, i, j;

//Vendedores 
char nome_vendedor[vendedores][35];

//Menu
int menu(void) {
    int opc;
    printf("\n\n  ____________________MENU____________________\n");
    printf(" |            Revenda do Sr.Joaquim:          |\n |--------------------------------------------|\n");
    printf(" |1 - Tabela de valor diário de venda.        |\n |--------------------------------------------|\n");
    printf(" |2 - Salário dos vendedores.                 |\n |--------------------------------------------|\n");
    printf(" |3 - Vendedor campeão de vendas(volume-R$).  |\n |--------------------------------------------|\n");
    printf(" |4 - Vendedor campeão de lucratividade.      |\n |--------------------------------------------|\n");
    printf(" |5 - Melhor venda do mês.                    |\n |--------------------------------------------|\n");
    printf(" |6 - Vendedores.                             |\n |--------------------------------------------|\n");
    printf(" |7 - Dias do mês.                            |\n |--------------------------------------------|\n");
    printf(" |8 - Ranking dos vendedores.                 |\n |--------------------------------------------|\n");
    printf(" |9 - Consultar lucro e reposição.            |\n |--------------------------------------------|\n");
    printf(" |0 - Para sair.                              |\n |--------------------------------------------|\n");
    printf(" |Digite o que deseja consultar:              |\n |____________________________________________|\n");
    printf(" Número: ");
    scanf("%d", &opc);
    return opc;
}

//Valor diário das vendas (1)
void valor_diario_vendas (void){
    int valor[dias], cada_dia[dias/2];
    int k=0, l=0, menor, maior=0;
    float media;
    
    //Somando venda dos vendedores durante o mês: 
    soma=0;
    for(j=0;j<dias;j++){
        if(j%2!=0){
            for(i=0;i<vendedores;i++){
                soma=soma+m[i][j];
            }
        }
        valor[j]=soma;
        soma=0;
    }
    
    //Colocando a soma em um vetor "cada dia":
    j=0;
    for(i=0;i<dias;i++){
        if(i%2!=0){
            cada_dia[j]=valor[i];
            j++;
        }
    }
    
    //Maior e menor montante de vendas:
    for(i=0;i<dias/2;i++){
        if(maior<cada_dia[i]){
            maior=cada_dia[i];
            k=i;
        }
        if(i==0){
            menor=cada_dia[i];
        }else if(menor>cada_dia[i]){
            menor=cada_dia[i];
            l=i;
        }
    }
    
    //Média de vendas do mês:
    soma=0;
    for(i=0;i<dias/2;i++){
        soma= soma+cada_dia[i];
    }
    media=soma/(dias/2);
    
    //Tabela dos montantes durante os dias:
    printf    ("\n\nTabela de vendas diárias:\n _________________________________________________________ \n");
    for(i=0;i<dias/2;i++){
        if(i==k){  
            printf("| Dia %d | R$%d |  Dia com MAIOR montante em venda.  \n", i + 1, cada_dia[i]);
            printf("|--------------------------------------------------------\n");
        }else if(i==l){
            printf("| Dia %d | R$%d |  Dia com MENOR montante em venda.  \n", i + 1, cada_dia[i]);
            printf("|--------------------------------------------------------\n");
        }else if(cada_dia[i]<media){
            printf("| Dia %d | R$%d |  Dia com montante ABAIXO da média.\n", i + 1, cada_dia[i]);
            printf("|--------------------------------------------------------\n");
        }else if(cada_dia[i]>media){
            printf("| Dia %d | R$%d |  Dia com montante ACIMA da média.  \n", i + 1, cada_dia[i]);
            printf("|--------------------------------------------------------\n");
        }else{
            printf("| Dia %d | R$%d |  Dia com montante na média.  \n", i + 1, cada_dia[i]);
            printf("|--------------------------------------------------------\n");
        }
    }
    printf("|Média : %.0f                                         \n",media);
    printf("|_________________________________________________________\n\n");
}

//Comissão Vendedores Geral com Ranking e Campeão de Lucratividade (2) (4) (8) (9)
float comissao_campeao_de_lucratividade (int opc){
    int custo[vendedores], venda[vendedores], diferenca[vendedores];
    float porcentagem[vendedores], salario[vendedores], aux, total_comissao = 0;
    char nome_aux[20];
    
    //Somando preço de venda:
    soma=0;
    for(i=0;i<vendedores;i++){
        for(j=0;j<dias;j++){
            if (j%2!=0){
                soma=soma+m[i][j];
            }
            venda[i]=soma;
        }
        soma=0;
    }
    
    //Somando preço de custo:
    soma=0;
    for(i=0;i<vendedores;i++){
        for(j=0;j<dias;j++){
            if (j%2==0){
                soma=soma+m[i][j];
            }
            custo[i]=soma;
        }
        soma=0;
    }
    
    //Tirando a diferença de venda e custo (Lucro):
    for(i=0;i<vendedores;i++){
        diferenca[i] = venda[i]-custo[i];
    }
    
    //Calculando a porcentagem:
    for(i=0;i<vendedores;i++){
        porcentagem[i] = (float) diferenca[i]/custo[i];
        porcentagem[i] = porcentagem[i]*100;
    }
    
    //Caso seja a opção 2:
    if(opc == 2 || opc == 8 || opc == 9){
        
        //Conferindo o direito a comissão:
        for(i=0;i<vendedores;i++){
            if(porcentagem[i]<=10.0){
                salario[i]= (float) venda[i]*0.005;
            }
            if(porcentagem[i]>10.0&&porcentagem[i]<=20.0){
                salario[i]= (float) venda[i]*0.015;
            }
            if(porcentagem[i]>20.0&&porcentagem[i]<=30.0){
                salario[i]= (float) venda[i]*0.02;
            }
            if(porcentagem[i]>30.0&&porcentagem[i]<=50.0){
                salario[i]= (float) venda[i]*0.025;
            }
            if(porcentagem[i]>50.0){
                salario[i]= (float) venda[i]*0.05;
            }
        }
        
        //Apresentando os salários:
        
        if(opc == 2){
            for(i=0;i<vendedores;i++){
            printf(" Vendedor %s: %.2f\n",nome_vendedor[i],salario[i]);
            }
        }
        
        
        //Construindo ranking:
        if(opc == 8){
            for(i=0;i<vendedores;i++){
                for(j=0;j<vendedores;j++){
                    if(salario[i]>salario[j]){
                        aux = salario [i];
                        salario[i] = salario[j];
                        salario[j] = aux;
                        strcpy(nome_aux,nome_vendedor[i]);
                        strcpy(nome_vendedor[i],nome_vendedor[j]);
                        strcpy(nome_vendedor[j],nome_aux);
                    }
                }
            }
            for(i=0;i<vendedores;i++){
                printf("\n%dº: %s - %.2f\n", i + 1, nome_vendedor[i], salario[i]);
            }
        }
        
        //Total de comissão
        if(opc == 9){
            for(i=0;i<vendedores;i++){
                total_comissao = total_comissao + salario[i];
            }
            return total_comissao;
        }
        
    }
    
    //Caso seja opção 4:
    if(opc == 4){
        
        //Descobrindo média de cada vendedor:
        for(i=0;i<vendedores;i++){
            porcentagem[i] = porcentagem[i]/(dias/2);
        }
        j=0;
        
        //Procurando vendedor com mais lucro:
        for(i=0;i<vendedores;i++){
            if(porcentagem[i]>porcentagem[j]){
                j=i;
            }
        }
        //Apresentando dados:
        printf("\n\nVendedor: %s.\nVendeu: R$%d.\nPercentual de lucratividade: %.2f por cento.\n\n", nome_vendedor[j],venda[j],porcentagem[j] * (dias/2));
    }
}

//Vendedor campeão em vendas (3)
void vendedor_campeao (void){
    int maior_montante=0, venda[vendedores];
    flag=0;
    
    //Somando as vendas:
    soma=0;
    for(i=0;i<vendedores;i++){
        for(j=0;j<dias;j++){
            if (j%2!=0){
                soma=soma+m[i][j];
            }
            venda[i]=soma;
        }
        soma=0;
    }
    
    //Descobrindo o maior montante:
    for(i=0;i<vendedores;i++){
        if(venda[i]>maior_montante){
            maior_montante=venda[i];
            flag=i;
        }
    }
    
    //Apresentando o vendedor com maior montante e o valor do montante:
    printf("\nVendedor campeão de vendas: %s\nMontante vendido: R$%d.\n",nome_vendedor[flag],maior_montante);
}

//Melhor venda em lucratividade (5)
void melhor_venda_lucratividade (){
    int k=0,l=0, md=0, venda, custo, lucro, vendedor;
    int diferenca[dias/2];
    float percentualmd, percentualv;
    flag=0;
    
    //Descobre as diferenças, em seguida marca a maior, o custo, o dia, e o vendedor:
    for(i=0;i<vendedores;i++){
        for(j=0;j<dias;j++){
            if(j%2==0){
                diferenca[k]=m[i][j + 1]-m[i][j];
                if(diferenca[k]>md){
                    md=diferenca[k];
                    l=k;
                    vendedor=i;
                    flag=m[i][j];
                }
                k++;
            }
        }
        k=0;
    }
    
    //Percentual da maior diferença:
    percentualmd= (float) md/flag;
    percentualmd= percentualmd*100;
    
    //Percentual do vendedor
    
    //Somando preço de venda:
    soma=0;
    for(j=0;j<dias;j++){
        if (j%2!=0){
            soma=soma+m[vendedor][j];
        }
        venda=soma;
    }

    //Somando preço de custo:
    soma=0;
    for(j=0;j<dias;j++){
        if (j%2==0){
            soma=soma+m[vendedor][j];
        }
        custo=soma;
    }
    
    //Tirando a diferença de venda e custo (Lucro):
    lucro = venda-custo;
    
    //Calculando a porcentagem:
    percentualv = (float) lucro/custo;
    percentualv = percentualv*100;
    
    
    printf("\nVendedor: %s.\nDia: Dia %d.\nValor vendido: R$%d.\nPercentual de lucratividade da venda no dia %d: %.2f por cento.\nPercentual de lucratividade do vendedor (mensal): %.2f por cento.\n", nome_vendedor[vendedor],l + 1,m[vendedor][l * 2 + 1], l + 1, percentualmd, percentualv);
}
    
//Busca por nome do vendedor (6)
void busca_por_nome (){
    int tv,tl,tc;
    float porcentagem, porcentagem_m, comissao, soma_aux;
    char nome_buscado[35];
    flag = 1000;
    printf("\n\nDigite o nome do vendedor que deseja consultar: \n\n");
    for (i=0; i<vendedores;i++){
        printf("%s",nome_vendedor[i]);
        if(i == (vendedores- 1)/2){
            printf("\n");
        }else if(i!=vendedores - 1){
            printf(" - ");
        }else{
            printf("\n\nVendedor: ");
        }
    }
    do{
        scanf("%s", nome_buscado);
        
        //Achar vendedor na matriz:
        for(i=0;i<vendedores;i++){
            if(strcmp(nome_vendedor[i],nome_buscado) == 0){
                flag=i;
            }
        }
        if (flag != 1000){
            //Total em vendas desse vendedor (tv):
            soma=0;
            for(i=0;i<dias;i++){
                if(i%2!=0){
                    soma=soma+m[flag][i];
                }
            }
            tv=soma;
            
            //Total de lucros desse vendedor:
            soma=0;
            for(i=0;i<dias;i++){
                if(i%2==0){
                    soma=soma+m[flag][i];
                }
            }
            tc=soma;
            tl=tv-tc;
            
            //Comissão percentual de lucratividade:
            porcentagem = (float) tl/tc;
            porcentagem = porcentagem*100;
            if(porcentagem<=10.0){
                comissao= (float) tv*0.005;
            }
            if(porcentagem>10.0&&porcentagem<=20.0){
                comissao= (float) tv*0.015;
            }
            if(porcentagem>20.0&&porcentagem<=30.0){
                comissao= (float) tv*0.02;
            }
            if(porcentagem>30.0&&porcentagem<=50.0){
                comissao= (float) tv*0.025;
            }
            if(porcentagem>50.0){
                comissao= (float) tv*0.05;
            }
            
            //Média percentual de lucratividade:
            soma_aux=0;
            for(i=0;i<dias;i++){
                if(i%2==0){
                    porcentagem_m = m[flag][i + 1] - m[flag][i];
                    porcentagem_m = porcentagem_m/m[flag][i];
                    porcentagem_m = porcentagem_m*100;
                    soma_aux=soma_aux+porcentagem_m;
                }
            }
            porcentagem_m = (float) soma_aux/(dias/2);
            
            //Apresentar dados:
            printf("\n\n Vendedor: %s.\n Total em vendas: R$%d.\n Total em lucros: R$%d.\n Total a receber: R$%.2f.\n Percentual de lucratividade (mensal): %.2f por cento.\n Média de percentual de lucratividade(por dia): %.2f por cento.\n \n",nome_vendedor[flag],tv,tl,comissao,porcentagem, porcentagem_m);
        }else{
            printf("\n\nVendedor não encontrado. Verifique os vendedores registrados e digite novamente: \n\n");
        }
    }while(flag ==1000);
}

//Busca por dia do mês (7)
void busca_por_dia (){
    int d, k,tv=0, tc=0, tl=0, diferenca[vendedores], venda[vendedores], custo[vendedores];
    float salario=0, ts=0, mpl=0, porcentagem[vendedores]; 
    printf("\n\nDigite o dia que deseja consultar: \n");
    scanf("%d", &d);
    
    //Calcular total de venda, de custo e de lucro:
    flag=0;
    i=0;
    do{
        flag++;
        if(flag==d){
            for(j=0;j<vendedores;j++){
                tv=tv+m[j][i + 1];
                tc=tc+m[j][i];
                tl=tv-tc;
                k=i;
            }
        }
    i = i + 2;
    }while(flag!=d);
    
    //Calculando total de comissão:
    for(j=0;j<vendedores;j++){
        venda[j]=m[j][k + 1];
        custo[j]=m[j][k];
        diferenca[j]=venda[j]-custo[j];
        porcentagem[j] = (float) diferenca[j]/custo[j];
        porcentagem[j] = porcentagem[j]*100;
    }
    for(i=0;i<vendedores;i++){
        if(porcentagem[i]<=10.0){
            salario= (float) venda[i]*0.005;
        }
        if(porcentagem[i]>10.0&&porcentagem[i]<=20.0){
            salario= (float) venda[i]*0.015;
        }
        if(porcentagem[i]>20.0&&porcentagem[i]<=30.0){
            salario= (float) venda[i]*0.02;
        }
        if(porcentagem[i]>30.0&&porcentagem[i]<=50.0){
            salario= (float) venda[i]*0.025;
        }
        if(porcentagem[i]>50.0){
            salario= (float) venda[i]*0.05;
        }
        ts=ts+salario;
        salario=0;
    }
    
    //Média percentual de lucratividade:
    for(i=0;i<vendedores;i++){
        mpl = mpl + porcentagem[i];
    }
    mpl = mpl/vendedores;
    
    //Apresentar dados:
    printf("\n\n      __________________________- Dia%d -__________________________\n\n       Total de vendas: R$%d\n       Total de lucro: R$%d\n       Total de comissao: R$%.2f\n       Média percentual de lucratividade do dia: %.2f por cento. \n      ____________________________________________________________\n", d, tv, tl, ts, mpl);
}

//Valor que voltará para revenda (Investimento) (9)
void valor_investir (int opc){
    int venda = 0, custo = 0;
    float lucro = 0, comissoes=0, investimento=0, aux=0;
    comissoes = comissao_campeao_de_lucratividade (opc);
    //Valor total de venda do mês
    for(j=0;j<dias;j++){
        if(j%2!=0){
            for(i=0;i<vendedores;i++){
                venda=venda+m[i][j];
            }
        }
    }
    
    //Valor total de custo do mês
    for(j=0;j<dias;j++){
        if(j%2==0){
            for(i=0;i<vendedores;i++){
                custo=custo+m[i][j];
            }
        }
    }
    
    //Lucro total do mês
    lucro = (float) venda - custo;
    
    //Tirando as comissões
    lucro = lucro - comissoes;
    
    //Apresentando dados:
    printf("\n\nDeseja investir parte do lucro em seu estabelecimento? (Lucro: R$%.2f)\n1-Sim\n2-Não\n", lucro);
    do{
        scanf("%d", &opc);
        if(opc==1){
            printf("\nQuantos por cento do lucro deseja investir?\n");
            scanf("%f",&aux);
            //Calculo do investimento de acordo com o percentual digitado pelo usuário
            investimento = aux * lucro;
            investimento = investimento / 100;
            printf("\nInvestimento: R$%.2f\nRetorno para loja(sem investimento): R$%d\nTotal de comissão a pagar: R$%.2f\nLucro restante: R$%.2f\n",investimento,custo,comissoes,lucro-investimento);
        }else if(opc==2){
            printf("\n\nRetorno para loja: R$%d\nComissão a pagar(geral): R$%.2f\nLucro restante: R$%.2f\n",custo,comissoes,lucro);
        }else{
            printf("\nOpção inválida, tente novamente:\n");
        }
    }while(opc!=1&&opc!=2);
}

//Função principal
int main() {
    int v, opc;

    //Rand para matriz principal
    for(i=0;i<vendedores;i++){
        for(j=0;j<dias;j++){
            if(j % 2 == 0){
                m[i][j] = (rand() % 10000) + 10000;
                do{
                    v = (rand() % 10000) + 10000;
                }while(v<=m[i][j]);
                m[i][j+ 1]= v;
            }
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    
    //Nome dos vendedores
    printf("\n\n\n\n\n\nDigite o nome de cada vendedor:\n");
    for(i=0;i<vendedores;i++){
        scanf("%s",nome_vendedor[i]);
    }
    
    //Chamando as funções
    do{
        opc =menu();
        
         //Valor diário de venda, dia de maior montante, e menor montante: 
        switch (opc){
            case 1:
                valor_diario_vendas();
            break;
            
            
         // Comissão dos vendedores: 
            case 2:
                comissao_campeao_de_lucratividade(opc);
            break;
            
            
         //Vendedor campeao em vendas (R$)
            case 3:
            vendedor_campeao();
            break;
            
            
         //Vendedor campeao de lucratividade (Média dos lucros nas vendas)
            case 4:
                comissao_campeao_de_lucratividade(opc);
            break;
            
            
         //Melhor venda em lucratividade
            case 5:
                melhor_venda_lucratividade();
            break;
            
            
         //Buscar vendedores (por nome)    
            case 6:    
                busca_por_nome();
            break;
            
            
         //Buscar dia 
            case 7:
                busca_por_dia();
            break;
            
            
         //Ranking dos vendedores
            case 8:
                comissao_campeao_de_lucratividade(opc);
            break;
            
            
         //Valor que voltará a revenda / Investir 
            case 9:
                valor_investir(opc);
            break;
            
            
         //Sair:
            case 0:
                printf("\nDeseja sair do programa?");
            break;
            
            
         //Opção inválida
            default:
                printf("\nOpção inválida. Tente novamente:\n\n");
        }
        
        printf("\n1 - Para voltar ao menu.\n0 - Para sair.\n");
        scanf("%d", &opc);
        
    }while(opc!=0);
    
    printf("\n\nAté logo!");
     
    return 0;
}











