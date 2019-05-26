//
//  main.c
//  #assignment3
//
//  Created by TSAR on 25/05/2019.
//  Copyright © 2019 TSAR. All rights reserved.
//

#include <stdio.h>

#define MAX 30

int G[MAX][MAX], num_of_vertex;

typedef struct edge{
    int vertex_1,vertex_2,edge_cost;//두 점과 cost값 저장
}edge;

typedef struct edgelist{
    edge data[MAX];
    int count;//정리때 카운트하기 위해서...
}edgelist;

edgelist edge_list;//인접matrix에서 cost가 0인 것을 지운 것을 리스트로 정리. 그냥 변들을 정리한 리스트.
edgelist output_list;//출력용 리스트. edge_list을 축약함.

void kruskal(void);
void print(void);//출력용

int find(int parent[],int i);//parent[i]의 값을 찾는 용도
void sort(void);//cost에 대한 오름차순으로 정리
void union1(int parent[], int x, int y);//parent값을 수정.

int main(){
    
    /*** vertex개수 입력    ***/
    printf("Enter number of vertices:");
    scanf("%d",&num_of_vertex);
    
    /***    인접그래프 입력    ***/
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
    
    for(int i=0; i<edge_list.count; i++){//정렬을 그 개수만큼 하는 것.
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
    int parent[MAX];//union1과 코드111~116줄을 사용해서, 이 점이 지난적이 있나 없나는 확인
    edge_list.count=0;//count초기화
    int  cno1,cno2;//이 점을 지났는지를 확인하기 위해서
    
    //인접matrix를 사용해서 edge_list를 만들기.
    for(int i=1;i<num_of_vertex;i++){
        for(int j=0;j<i;j++)//대칭이라서 굳이 다 볼필요없이, 반토막내서 보자
        {
            if(G[i][j]!=0)
            {
                edge_list.data[edge_list.count].vertex_1=i;
                edge_list.data[edge_list.count].vertex_2=j;
                edge_list.data[edge_list.count].edge_cost=G[i][j];
                edge_list.count++;
            }
        }
        
    }
    
    sort();
    
    for(int i=0;i<num_of_vertex;i++)    parent[i]=i;//parent 초기화
    
    output_list.count=0;
    
    //이미 지났는지 확인
    for(int i=0;i<edge_list.count;i++)
    {
        cno1=find(parent,edge_list.data[i].vertex_1);
        cno2=find(parent,edge_list.data[i].vertex_2);
        
        if(cno1!=cno2)
        {
            output_list.data[output_list.count]=edge_list.data[i];
            output_list.count=output_list.count+1;
            union1(parent,cno1,cno2);
        }
    }
}
    
    void print(){
        int cost=0;//총 cost개산을 위한 초기화
        
        printf("\n");
        
        for(int i=0; i<output_list.count; i++){
            printf("Edge %d:(%d, %d)    cost:%d\n",i,output_list.data[i].vertex_1, output_list.data[i].vertex_2, output_list.data[i].edge_cost);
            cost+=output_list.data[i].edge_cost;//cost 누적
    }
        printf("Minimun cost= %d\n\n",cost);

    
    
}
