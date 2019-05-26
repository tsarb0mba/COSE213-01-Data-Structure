//
//  main.c
//  #assignment3
//
//  Created by TSAR on 25/05/2019.
//  Copyright © 2019 TSAR. All rights reserved.
//

#include <stdio.h>

#define MAX 30


typedef struct edge{
    int vertex_1,vertex_2,edge_cost;
}edge;

typedef struct edgelist{
    edge data[MAX];
    int count;
}edgelist;

edgelist edge_list;

int G[MAX][MAX], num_of_vertex;

edgelist span_list;

void kruskal(void);

int find(int parent[],int i);
void sort(void);//make the list be ascénding sórt of cost
void union1(int parent[], int x, int y);
void print(void);

int main(){
    //int total_cost;
    
    /***    enter number of vertex  ***/
    printf("Enter number of vertices:");
    scanf("%d",&num_of_vertex);
    
    /***    creat graph ***/
    printf("\nEnet the adjacency matrix:\n");
    for(int i=0;i<num_of_vertex;i++){
        for(int j=0;j<num_of_vertex;j++){
            scanf("%d",&G[i][j]);        }
    }
    
    kruskal();
    print();
    return 0;
    }

int find(int parent[],int vertex_NO){
    return(parent[vertex_NO]);
}

void sort(){
    edge temp;
    
    for(int i=0; i<edge_list.count; i++){
        for(int j=0; j<edge_list.count-1; j++){
            if(edge_list.data[j].edge_cost>edge_list.data[j+1].edge_cost){
                temp=edge_list.data[j];
                edge_list.data[j]=edge_list.data[j+1];
                edge_list.data[j+1]=temp;
            }
        }
    }
}

void union1(int parent[],int x, int y){
    for(int i=0; i<num_of_vertex; i++){
        if(parent[i]==y)
            parent[i]=x;
    }
    
}

void kruskal(){
    int parent[MAX];
    edge_list.count=0;
    int  cno1,cno2;
    
    for(int i=1;i<num_of_vertex;i++)
        for(int j=0;j<i;j++)
        {
            if(G[i][j]!=0)
            {
                edge_list.data[edge_list.count].vertex_1=i;
                edge_list.data[edge_list.count].vertex_2=j;
                edge_list.data[edge_list.count].edge_cost=G[i][j];
                edge_list.count++;
            }
        }
    
    sort();
    
    for(int i=0;i<num_of_vertex;i++)
        parent[i]=i;
    
    span_list.count=0;
    
    for(int i=0;i<edge_list.count;i++)
    {
        cno1=find(parent,edge_list.data[i].vertex_1);
        cno2=find(parent,edge_list.data[i].vertex_2);
        
        if(cno1!=cno2)
        {
            span_list.data[span_list.count]=edge_list.data[i];
            span_list.count=span_list.count+1;
            union1(parent,cno1,cno2);
        }
    }
}
    
    void print(){
        int cost=0;
        
        printf("\n");
        
        for(int i=0; i<span_list.count; i++){
            printf("Edge %d:(%d, %d)    cost:%d\n",i,span_list.data[i].vertex_1, span_list.data[i].vertex_2, span_list.data[i].edge_cost);
            cost+=span_list.data[i].edge_cost;
    }
        printf("Minimun cost= %d\n\n",cost);

    
    
}
