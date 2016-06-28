/*
| Materia: Estrutura de Dados B - Trabalho Grafo Cidade
| Autor: Jeferson Cunha
| Info : edu@jefersoncunha.com
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Estradas {
  int cidadeVizinhaId;
  char cidadeVizinhaNome[20];
  int tipoEstrada; // 1 asfalto , 2 estrada de chao
  int distancia; // inteiro apenas para ser mais simples de enviar
  struct Estradas *prox;
} Estradas;

typedef struct Cidades {
  int cidadeId;
  char nome[20];
  Estradas *cidadeVizinha;
  struct Cidades *prox;
} Cidades;

int numCidadesInseridas = 0, geradorCodigo = 1;

void *apontar(Cidades *cids, int de, int para, int dist, int tipest ){
  Cidades *p = cids, *cidde, *cidpara;
  Estradas *eNovo, *eNovo2, *pE;

  while(p){ // percorrer toda struct cidade ate encontrar a ORIGEM E DESTINO
    if (de == p->cidadeId)
      cidde = p;
    if (para == p->cidadeId){
      cidpara = p;
    }
    p = p->prox;
  }

  eNovo = (Estradas *) malloc (sizeof(Estradas)); // cria alocao de memoria para uma nova estrada
  eNovo->cidadeVizinhaId = para; // salva o valor destino
  strncpy(eNovo->cidadeVizinhaNome, cidpara->nome, strlen(cidpara->nome)+1); // salva o nome da cidade destino
  eNovo->distancia = dist; // salva a distancia
  eNovo->tipoEstrada = tipest; // salva o tipo de destrada

  /*
    Verifica se a cidade de origem ja tem alguma estrada para cidades vizinhas
    se SIM: a proxima estrada/aresta aponta pra nulo
    se NAO ja tem alguma vizinha entao ela procura o final da lista e adicona a nova vizinha
  */
  if(cidde->cidadeVizinha == NULL){
    eNovo->prox = NULL; //
    cidde->cidadeVizinha = eNovo;
  }else{
    pE = cidde->cidadeVizinha;
    while(pE->prox){
      pE = pE->prox;
    }
    pE->prox = eNovo;
    eNovo->prox = NULL;
  }

  /*
    Para fazer o apontamento DUPLO, isto eh, (IDA E VOLTA), a cidade de destino tambem ira apontar para a cidade de origem
  */
  eNovo2 = (Estradas *) malloc (sizeof(Estradas));
  eNovo2->cidadeVizinhaId = de;
  strncpy(eNovo2->cidadeVizinhaNome, cidde->nome, strlen(cidde->nome)+1);
  eNovo2->distancia = dist;
  eNovo2->tipoEstrada = tipest;

  if(cidpara->cidadeVizinha == NULL){
    eNovo2->prox = NULL;
    cidpara->cidadeVizinha = eNovo2;
  }else{

    pE = cidpara->cidadeVizinha;
    while(pE->prox){
      pE = pE->prox;
    }
    pE->prox = eNovo2;
    eNovo2->prox = NULL;
  }

}

/*
|   Criar uma nova cidade e adiciona nulo para suas vizinhas, porque ainda nao existiram vizinhos para esta.
*/
Cidades *criarCidade (Cidades *c, char cidnome[20]) {
  Cidades *cNovo;
  cNovo = (Cidades *) malloc (sizeof(Cidades));
  cNovo->cidadeId = geradorCodigo;
  geradorCodigo++;
  strncpy(cNovo->nome, cidnome, strlen(cidnome)+1);
  cNovo->cidadeVizinha = NULL;
  cNovo->prox = c;
  return cNovo;
}

/*
| Buscar o endereco de memoria para uma cidade, dispondo apenas do ID da mesma.
| Atraves do endereco de momoria eh possivel percorrer a struct com facilidade para fazer operacoes de Listagem Seleta, Edicao e Exclusao.
*/

Cidades *buscarPeloId(Cidades * c, int idCidade){
  Cidades *g = c, *cidade;
  while(g){
    if( idCidade == g->cidadeId){
      cidade = g;
    }
    g = g->prox;
  }
  return cidade;
}

/*
| Percorre as cidades, na struct bem como os caminhos(estadas) que a mesma tenha.
| Recebe como parametro tambem a opcao para definir o que sera impresso e ID de busca, para selecao personalizada
| Quando as opcoes sao:
| 1: Entao imprimir todas as cidades e suas respectivas vizinhas
| 2: Entao imprimir todas as cidades sem suas vizinhas
| 3: Entao imprimir uma cidade especifica com todas as suas vizinhas
*/
void percorrerCidades(Cidades *c, int opc, int busca){
  Cidades *g = c, *id;
  Estradas *e;
  if(opc == 3) g = buscarPeloId(c, busca); // se a OPC for 3, entao desejamos saber as informacoes apenas de uma cidade especifica

  while (g) { // percorre a struct CIDADES para fazer impressao dos valores
    printf("\n\nCod %d - %s",g->cidadeId, g->nome); //
    if(opc == 1 || opc == 3){
      e = g->cidadeVizinha;
      printf("\n\nVizinhas");
      while(e){ // percorre a struct ESTRADAS para fazer impressao dos valores
        printf("\n Cod: %d - %s - Dist: %d - Estrada de: ",e->cidadeVizinhaId, e->cidadeVizinhaNome, e->distancia);
        (e->tipoEstrada == 1) ? printf("Asfalto") : printf("Chao"); //operador ternario para simplificar e diminuir o codigo no tipo de impressao de asfalto ou estrada de chao
        e = e->prox;
      }
    }
    if(opc == 3) g = NULL; else g = g->prox; // caso seja 3, n pode andar na struct cidade, para ficar dentro da cidade especifica
  }
  printf("\n\n");
  fflush(stdin);
  printf("pressione enter para continuar\n\n");
  getchar();
}

/*
| Carrega todas as 8 cidades iniciais com os 10 caminhos/estradas iniciais
*/
Cidades *carregacidades(Cidades *cid){
  cid = criarCidade(cid, "Sao Jose");
  cid = criarCidade(cid, "Sao Paulo");
  cid = criarCidade(cid, "Sao Bernado");
  cid = criarCidade(cid, "Sao Sebastiao");
  cid = criarCidade(cid, "Santa Cruz");
  cid = criarCidade(cid, "Mogi Mirim");
  cid = criarCidade(cid, "Washigton");
  cid = criarCidade(cid, "Nova York");
  cid = criarCidade(cid, "Tokio");
  apontar(cid, 1, 2, 74, 1);
  apontar(cid, 1, 3, 51, 1);
  apontar(cid, 2, 5, 31, 2);
  apontar(cid, 2, 7, 131, 1);
  apontar(cid, 2, 9, 301, 1);
  apontar(cid, 3, 4, 81, 2);
  apontar(cid, 4, 5, 92, 1);
  apontar(cid, 7, 6, 101, 1);
  apontar(cid, 7, 8, 232, 2);
  apontar(cid, 9, 6, 122, 1);
  return cid;
}

Cidades *cadastro(Cidades *nova){
  int opc, cod, km, tipo;
  char nomeNovo[20];
  printf("Preencha os dados da nova cidade");
  printf("Nome: ");
  fflush(stdin);
  gets(nomeNovo);
  nova = criarCidade(nova, nomeNovo);
  printf("Tem cidade vizinha? (sim - 1 / nao - 2): ");
  scanf("%d", &opc);
  do{
    system("cls");
    if(opc == 1){
      percorrerCidades(nova, 2, 0);
      printf("Digite o codigo da cidade que sera vizinha: ");
      scanf("%d", &cod);
      printf("Distancia em Km: ");
      scanf("%d", &km);
      printf("Tipo de Estrada (1 - Asfalto | 2 - Chao): ");
      scanf("%d", &tipo);
      apontar(nova, geradorCodigo -1, cod, km, tipo);
    }
    printf("Tera outra cidade vizinha? (sim - 1 / nao - 2): ");
    scanf("%d", &opc);
  }while(opc != 2);
  return nova;
}

void editarCidade(Cidades *cidadeEditar){
  int id, id2, opc, novaDistancia, novaEstrada;
  Cidades *c;
  Estradas *vizinhas, *viz;
  char nomeNovo[20];
  percorrerCidades(cidadeEditar, 2, 0);
  printf("Escolha o cod da cidade a ser editada: ");
  scanf("%d", &id);
  percorrerCidades(cidadeEditar, 3, id);
  printf("1 - Editar nome\n");
  printf("2 - Editar distancia entre cidades vizinhas\n");
  printf("Opcao: ");
  scanf("%d", &opc);
  if(opc == 1){
    printf("Novo Nome: ");
    fflush(stdin);
    gets(nomeNovo);
    c = buscarPeloId(cidadeEditar, id);
    strncpy(c->nome, nomeNovo, strlen(nomeNovo)+1);
    vizinhas = c->cidadeVizinha;
    while(vizinhas){ // renomear todas as vizinhas daquela cidade com o novo nome
      c = buscarPeloId(cidadeEditar, vizinhas->cidadeVizinhaId);
      viz = c->cidadeVizinha;
      while(viz){ // percorre todas as vizinhas, para encontrar o ID, e entao, NELAS alterar o nome tambem
       if (id == viz->cidadeVizinhaId){
          strncpy(viz->cidadeVizinhaNome, nomeNovo, strlen(nomeNovo)+1);
          }
      viz = viz->prox;
      }
      vizinhas = vizinhas->prox;
    }
  }
  if(opc == 2){
    printf("Escolha o cod cidade vizinha\n ");
    scanf("%d", &id2);
    printf("Digite nova distancia: ");
    scanf("%d", &novaDistancia);
    printf("Digite novo tipo de estrada (1- Asfalto | 2- Chao: ");
    scanf("%d", &novaEstrada);
    apontar(cidadeEditar, id, id2, novaDistancia, novaEstrada);
  }

}

Cidades *excluirCidade(Cidades *c, int id){
  Estradas *p, *p1, *ant;
  Cidades *cidadeExcluir, *vizinha, *g = c, *antC;
  int cida, cidb, kma, kmb;

  // pegar o ID enviado por parametro e busco o endereco de memoria da cidade
  cidadeExcluir = buscarPeloId(c, id);
  p = cidadeExcluir->cidadeVizinha; // p receber as cidades vizinhas da cidade que quero excluir

  /*
  | primeiro sera excluido os apontamentos das cidades vizinhas para a cidade inicial (selecionada)
  */
  while(p){ //percore as cidades vizinhas da cidade que sera exclurida
    vizinha = buscarPeloId(c, p->cidadeVizinhaId); // busca o endereco de memoria para cada cidade vizinha encontrada
    p1 = vizinha->cidadeVizinha; //p1 recebe todas as vizinhas da vizinha encontrada acima
    while(p1){ // percorre todas as vinhas desta outra cidade (cidade vizinha)
      if(p1->cidadeVizinhaId == id){ //procura o endereco de memoria q deve ser exclido da cidade vizinha
        if(p1 == vizinha->cidadeVizinha){ // se a vizinha a ser excluida eh a primeira da lista
          if(p1->prox == NULL){ // se o prox for nulo
            vizinha->cidadeVizinha = NULL; // cidade vizinha recebe nulo, (ultima cidade vizinha da lista, n havera mais cidades vizinhas)
            free(p1); // apaga endereco de memoria
          }else{ // se nao for a unica cidade da lista entao ela recebera a proxima e excluira a atual
            vizinha->cidadeVizinha = p1->prox;
            free(p1);  // apaga endereco de memoria
          }
        }else if(p1->prox == NULL){ // caso ela n for a primeira da lista , entao verifica se a proxima depois dela eh nula ( a cidade eh a ultima da lista?)
          ant->prox = NULL;
          free(p1);  // apaga endereco de memoria
        }else{ //caso n for a ultima da lista (cidade entre cidades)
          ant->prox = p1->prox;
          free(p1);  // apaga endereco de memoria
        }
      }
      ant = p1;
      p1 = p1->prox;
    }
    p = p->prox;
  }

  /*
  | Faz reapontamento da cidade a ser excluida, recebendo seus apontamentos para continuar os mesmos nas vizinhas
  | Unindo duas cidades vizinhas, atraves de seus apontamentos, para depois entao, poder ser excluioda
  */
  p = cidadeExcluir->cidadeVizinha;
  p1 = p;
  while(p){ // percorre a struct de cidade fixando uma cidade
    if(cidadeExcluir->cidadeId != p->cidadeVizinhaId){ // verificar se a cidade
      cida = p->cidadeVizinhaId;
      kma = p->distancia;
    }
    while(p1){ // faz a comparacao da mesma com todas as outras cidade
      cidb = p1->cidadeVizinhaId;
      kmb = p1->distancia;
      if(cida != cidb){ //se elas forem diferentes, faz uma apontar para a outra ( as duas vizinhas fazerem o apontamento da que sera excluida)
        apontar(c, cida, cidb,(kma+kmb) , 1);
      }
      p1 = p1->prox;
    }
    p = p->prox;
  }
  /*
  | Agora sera excluido do grafo a cidade selecionada de fato
  */
  while(g){ // percorre tddas as cidades
    if (g == cidadeExcluir){ // se a atual for igual a cidade a ser excluida
      if(g == c){ // verifica se essa cidade eh a primeira cidade da lista
        c = g->prox;
        free(g);
        return c;
      }else if(g->prox != NULL){ // se ela n eh a primeira verifica se ela esta entre outras cidades (no meio da lista)
        antC->prox = g->prox;
        free(g);
        return c;
      }else{ // caso ela for a ultima da lista ...
        antC->prox = NULL; //anterior vira a ultima
        free(g); // ela sai da lista (apagada)
        return c;
      }
    }
    antC = g;
    g = g->prox;
  }
}

int main(){
  Cidades *c = NULL;
  int opc, id;
  c = carregacidades(c);
  do{
    system("cls");
    printf(" ----------------GRAFO PARA CONTROLE DE CIDADES------------------\n");
    printf("-> 1 - CADASTRAR CIDADES\n");
    printf("-> 2 - EDITAR CIDADES\n");
    printf("-> 3 - EXCLUIR CIDADES\n");
    printf("-> 4 - LISTAR CIDADES VIZINHAS DE UMA CIDADE ESPECIFICA\n");
    printf("-> 5 - LISTAR TODAS CIDADES E SUAS CIDADES VIZINHAS\n");
    printf("-> 0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opc);
    system("cls");
    switch(opc){
      case(1):{
        c = cadastro(c);
        break;
      }
      case(2):{
        editarCidade(c);
        break;
      }
      case(3):{
        percorrerCidades(c, 2, 0);
        printf("Escolha o cod da cidade a excluida: ");
        scanf("%d", &id);
        c = excluirCidade(c, id);
        break;
      }
      case(4):{
        percorrerCidades(c, 2, 0);
        printf("Escolha o cod da cidade: ");
        scanf("%d", &id);
        percorrerCidades(c, 3, id);
        break;
      }
      case(5):{
        percorrerCidades(c, 1, 0);
        break;
      }
    }
  }while(opc != 0);
}
