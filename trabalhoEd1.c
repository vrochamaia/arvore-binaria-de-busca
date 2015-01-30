#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct cliente{

        char nome[50];
        int telefone;
        char rg[15];
        char email[50];
        struct cliente *esq;
        struct cliente *dir;

    } cliente;


    int inserirNo(cliente **raiz, int elemento, char nomeCliente[], char rgCliente[], char email[]){
        if(*raiz == NULL){
            cliente *aux = (cliente *)malloc(sizeof(cliente));
            aux->telefone = elemento;
            aux->dir = NULL;                                //funcao utilizada para inserir um novo no na arvore
            aux->esq = NULL;
            strcpy(aux->nome, nomeCliente);
            strcpy(aux->rg, rgCliente);
            strcpy(aux->email, email);
            *raiz = aux;
            return 1;
        }
        if(elemento < (*raiz)->telefone){
            inserirNo(&(*raiz)->esq, elemento, nomeCliente, rgCliente, email);
            return;
        }
        if(elemento > (*raiz)->telefone){
            inserirNo(&(*raiz)->dir, elemento, nomeCliente, rgCliente, email);
            return;
        }
        printf("\nNumero %d ja esta cadastrado.\n", elemento);
        return 0;
    }

    void busca(cliente **raiz, int elemento){
        if(*raiz == NULL){
            printf("\nNumero nao cadastrado.\n");
            return;
        }                                            //funcao utilizada para buscar um numero na arvore
        else if(elemento < (*raiz)->telefone){
            busca(&(*raiz)->esq, elemento);
            return;
        }
        else if(elemento > (*raiz)->telefone){
            busca(&(*raiz)->dir, elemento);
            return;
        }
        printf("\nTelefone: %d ", (*raiz)->telefone);
        printf("\nCliente: %s ", (*raiz)->nome);
        printf("\nRG: %s", (*raiz)->rg);
        printf("\nEmail: %s\n", (*raiz)->email);
    }

    cliente *filhoDaDireita(cliente **no){
        if((*no)->dir != NULL)
            return filhoDaDireita(&(*no)->dir);
        else{
            cliente *aux1 = *no;        //funcao utilizada para pegar o nó mais a direita da subarvore esquerda do nó que será removido
            if((*no)->esq != NULL)
                *no = (*no)->esq;
            else
                *no = NULL;
        return aux1;
        }
    }

    void removerNo2(cliente **raiz, int elemento){
        int resposta;
        if(*raiz == NULL){
            printf("\nNumero nao existe na arvore.\n");
            return;
        }                                                        /*funcao utilizada para remover um no da arvore, algoritmo
                                                                   muito parecido com o que foi utilizado em sala  */
        if(elemento < (*raiz)->telefone)
            removerNo2(&(*raiz)->esq, elemento);
        else
            if(elemento > (*raiz)->telefone)
                removerNo2(&(*raiz)->dir, elemento);
            else{
                printf("\nCliente: %s\nRG: %s\nEmail: %s", (*raiz)->nome, (*raiz)->rg, (*raiz)->email);
                printf("\n\nDeseja realmente apagar esse cadastro?\n1-Sim\n2-Nao.\n");
                scanf("%d", &resposta);
                if (resposta == 1){
                    cliente *aux2 = *raiz;
                    if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)){
                        free(aux2);
                        (*raiz) = NULL;
                    }
                    else{
                        if ((*raiz)->esq == NULL){
                            (*raiz) = (*raiz)->dir;
                            aux2->dir = NULL;
                            free(aux2);
                            aux2 = NULL;
                        }
                        else{
                            if ((*raiz)->dir == NULL){
                                (*raiz) = (*raiz)->esq;
                                aux2->esq = NULL;
                                free(aux2);
                                aux2 = NULL;
                            }
                        else{
                            aux2 = filhoDaDireita(&(*raiz)->esq);
                            aux2->esq = (*raiz)->esq;
                            aux2->dir = (*raiz)->dir;
                            (*raiz)->esq = NULL;
                            (*raiz)->dir = NULL;
                            free((*raiz));
                            *raiz = aux2;
                            aux2 = NULL;
                        }
                    }
                }
                printf("\nCadastro removido com sucesso\n");
            } else {
                printf("\nNumero nao removido\n");
            }
        }
    }

    void pesquisaPreOrdem(cliente *raiz){
        if(raiz == NULL)
            return;
        printf("\nTelefone: %d ", raiz->telefone);
        printf("\nCliente: %s ", raiz->nome);
        printf("\nRG: %s", raiz->rg);               //funcao utilizada para listar os nos da arvore em preOrdem
        printf("\nEmail: %s\n", raiz->email);
        pesquisaPreOrdem(raiz->esq);
        pesquisaPreOrdem(raiz->dir);
    }

    void pesquisaPosOrdem(cliente *raiz){
        if(raiz == NULL)
            return;
        pesquisaPosOrdem(raiz->esq);             //funcao utilizada para listar os nos da arvore em posOrdem
        pesquisaPosOrdem(raiz->dir);
        printf("\nTelefone: %d ", raiz->telefone);
        printf("\nCliente: %s ", raiz->nome);
        printf("\nRG: %s", raiz->rg);
        printf("\nEmail: %s\n", raiz->email);
    }

    void pesquisaEmOrdem(cliente *raiz){
        if(raiz == NULL)
            return;
        pesquisaEmOrdem(raiz->esq);                 //funcao utilizada para listar os nos da arvore em ordem,do menor para o maior
        printf("\nTelefone: %d ", raiz->telefone);
        printf("\nCliente: %s ", raiz->nome);
        printf("\nRG: %s", raiz->rg);
        printf("\nEmail: %s\n", raiz->email);
        pesquisaEmOrdem(raiz->dir);
    }


int main(){

    cliente *raiz = NULL;
    int i, valor, j;
    int achou, tamanho;
    int num;
    int resp = 1;
    char nomeCliente[50], emailCliente[50], rgCliente[15];
    char cadastro[8];
    while(resp == 1){
        printf("1-Cadastrar numero; \n2-Pesquisar numero; \n3-Remover numero; \n4-Listar cadastros; \n");
        scanf("%i",&num);

        switch(num){
        case 1:
            printf("\nInsira o telefone. \nOBS: Numero do telefone tem que ter 8 digitos e comecar com 3,8 ou 9.\n");
            fflush(stdin);
            gets(cadastro);
            tamanho = strlen(cadastro);
            if(tamanho==8){

                for(i=0;i<1;i++){
                    if(cadastro[0] == '3' || cadastro[0] == '8' || cadastro[0] == '9') {
                        achou = 1;
                        } else {                //verificacao do telefone
                            achou = 0;
                        }
                }
                    valor = atoi(cadastro);
                    if(achou == 1){
                        printf("Digite o nome do cliente:\n");
                        fflush(stdin);
                        gets(nomeCliente);
                        tamanho = strlen(nomeCliente);
                        if(tamanho<=50){
                                printf("Digite o email do cliente:\n");
                                fflush(stdin);
                                gets(emailCliente);
                                tamanho = strlen(emailCliente);
                                if(tamanho<50){
                                        printf("Digite o RG do Cliente:\n");
                                        fflush(stdin);
                                        gets(rgCliente);
                                        tamanho = strlen(rgCliente);
                                        if(tamanho<=15){
                                            int resp = inserirNo(&raiz, valor, nomeCliente, rgCliente, emailCliente);

                                            if(resp == 1) {
                                            printf("\nCadastro feito com sucesso\n");
                                            }
                                        }
                                else
                                     printf("\nDigitos do RG maior/menor que o permitido\n");
                            }
                            else
                                printf("\nEmail maior que 50 caracteres nao pode ser armazenado.\n");
                        }
                        else
                            printf("\nNome do cliente tem que ter no maximo 50 caracteres.\n");
                    } else {
                        printf("\nTelefone nao pode ser armazenado.\n");
                }

            } else {
                printf("\nTelefone nao pode ser armazenado.\n");
            }
            break;
        case 2:
            printf("\nNumero para ser pesquisado: ");
            scanf("%d", &valor);
            busca(&raiz, valor);
            break;
        case 3:
            printf("\nNumero para ser removido: ");
            scanf("%d", &valor);
            removerNo2(&raiz, valor);
            break;
        case 4:
            printf("1-Pesquisa pre-ordem;\n2-Pesquisa em ordem;\n3-Pesquisa pos-ordem.\n");
            scanf("%d", &j);
            switch(j){
            case 1:
                pesquisaPreOrdem(raiz);
                printf("\n");
                break;
            case 2:
                pesquisaEmOrdem(raiz);
                printf("\n");
                break;
            case 3:
                pesquisaPosOrdem(raiz);
                printf("\n");
                break;
            }
            break;
        }

        printf("\nSe voce deseja continuar no programa,tecle '1'\nSe voce deseja encerrar o programa,tecle '0'\n");
        scanf("%i",&resp);

    }
    return 0;
}
