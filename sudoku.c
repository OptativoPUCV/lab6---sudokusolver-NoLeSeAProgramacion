#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
   int i,j,k;
   for(i=0;i<9;i++)
      {
         for(j=0;j<9;j++)
            {
               if(n->sudo[i][j]==0)
               {
                  continue;
               }
               for(k=0;k<9;k++)
                  {
                     if(k!=j)
                     {
                        if(n->sudo[i][j]==n->sudo[i][k])
                           return 0;
                     }
                  }
               for(k=0;k<9;k++)
                  {
                     if(k!=i)
                     {
                        if(n->sudo[i][j]==n->sudo[k][j])
                           return 0;
                     }
                  }
               int x0 = (i/3)*3;
               int y0 = (j/3)*3;
               for(k=0;k<3;k++)
                  {
                     for(int l=0;l<3;l++)
                        {
                           if(k+x0!=i && l+y0!=j)
                           {
                              if(n->sudo[i][j]==n->sudo[k+x0][l+y0])
                              {
                                 return 0;
                              }
                           }
                        }
                  }
            }
      }
   return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list=createList();
    int i,j;
   
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(n->sudo[i][j]==0)
            {
                Node* aux=copy(n);
                aux->sudo[i][j]=1;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=2;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=3;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=4;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=5;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=6;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=7;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=8;
                pushBack(list,aux);
                aux=copy(n);
                aux->sudo[i][j]=9;
                pushBack(list,aux);
            }
        }
    }
    return list;
}


int is_final(Node* n)
{
   int i,j;
   for(i=0;i<9;i++)
      {
         for(j=0;j<9;j++)
            {
               if(n->sudo[i][j]==0)
               {
                  return 0;
               }
            }
      }
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack* S=createStack();
   push(S,initial);
   while(S!=NULL)
      {
         Node* n=top(S);
         pop(S);
         if(is_valid(n)==1 && is_final(n)==1)
         {
            return n;
         }
         List* list=get_adj_nodes(n);
         Node* aux=first(list);
         while(aux!=NULL)
            {
               push(S,aux);
               aux=next(list);
            }
      }
   return S;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/