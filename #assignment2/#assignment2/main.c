//
//  main.c
//  #assignment2
//
//  Created by TSAR on 11/04/2019.
//  Copyright © 2019 TSAR. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define MALLOC(p, s) \
if (!((p) = malloc(s))) { \
fprintf(stderr, "  **Insufficient memory"); \
exit(EXIT_FAILURE); \
}
//node
typedef enum{head,entry} tagfield;
typedef struct matrixNode *matrixPointer;
typedef struct entryNode{
    int row,col,value;
}entryNode;
typedef struct matrixNode{
    matrixPointer down;
    matrixPointer right;
    int terms;
    tagfield tag;
    union{
        matrixPointer next;
        entryNode entry;
    }u;
}matrixNode;
matrixPointer hdnode[MAX_SIZE];


matrixPointer newNode() {
    matrixPointer pointer = NULL;
    MALLOC(pointer, sizeof(*pointer));
    return pointer;
}

 matrixPointer one,two,result;

//to input the matrix
matrixPointer mread(void);
//to print the matrix
void mwrite(matrixPointer m);
//to add the first matrix and second matrix
matrixPointer madd(matrixPointer first, matrixPointer second);
//to multiply the first matirx and second matrix
matrixPointer mmul(matrixPointer first, matrixPointer second);
//to transpose the first matrix
matrixPointer mtranspose(matrixPointer first);
//to remove the matrix
void mwrite(matrixPointer node);
//3 menu
void menu_1(void);
void menu_2(void);
void menu_3(void);
void end(){
    printf("\n\n*****아무 키나 눌러서 종료하세요*****");
    getchar();
    if(getchar()!='\0')exit(0);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("*******************************************************\n");
    printf("                  자료구조 #assignment2                  \n");
    printf("                               컴퓨터학과 2018320211 진지과\n");
    printf("*******************************************************\n");
    printf("\n");
    menu_1();
    printf("\n");
    menu_2();
    printf("\n");
    menu_3();
    return 0;

}

matrixPointer mread(void){
    int numRows,numCols,numTerms,numHeads,i;
    int row,col,value,currentRow = 0;
    matrixPointer temp = NULL,last = NULL,node;
    
    printf("\n** 행/열/0이 아닌 값의 개수를 순서대로 입력하세요.-->>");
    scanf("%d/%d/%d",&numRows,&numCols,&numTerms);
    printf("\n");
    numHeads=(numCols>numRows)?numCols:numRows;
    
    node=newNode();
    node->tag=entry;
    node->u.entry.row=numRows;
    node->u.entry.col=numCols;
    node->terms=numTerms;
    
    if(!numHeads)   node->right=node;
    else{
        for(i=0;i<numHeads;i++){
            temp=newNode();
            hdnode[i]=temp;
            hdnode[i]->tag=head;
            hdnode[i]->right=temp;
            hdnode[i]->u.next=temp;
        }
        currentRow=0;
        last=hdnode[0];
        for(i=1;i<=numTerms;i++){
            printf("**%d번쩨 행/열/값을 입력하세요.-->>",i );
            scanf("%d/%d/%d",&row,&col,&value);
            if(row>currentRow){
                last->right=hdnode[currentRow];
                currentRow=row;
                last=hdnode[row];
            }
            MALLOC(temp,sizeof(*temp));
            temp->tag=entry;
            temp->u.entry.row=row;
            temp->u.entry.col=col;
            temp->u.entry.value=value;
            last->right=temp;
            last=temp;
            hdnode[col]->u.next->down=temp;
            hdnode[col]->u.next=temp;
        }
        
        last->right=hdnode[currentRow];
        
        for(i=0;i<numCols;i++)  hdnode[i]->u.next->down=hdnode[i];
        
        for(i=0;i<numHeads-1;i++)   hdnode[i]->u.next=hdnode[i+1];
        hdnode[numHeads-1]->u.next=node;
        node->right=hdnode[0];
    }
    return node;
}

void mwrite(matrixPointer node){
    int i;
    matrixPointer temp,head=node->right;
    
    printf("\n**입력한 행렬 <행의 수 =%d, 열의 수= %d>",node->u.entry.row,node->u.entry.col);
    printf("\n\n**입력하신(또는 연산) 행렬의 행와 열 그리고 값:\n");
    for(i=0;i<node->u.entry.row;i++){
        for(temp=head->right;temp!=head;temp=temp->right)
            printf("%5d%5d%5d\n",temp->u.entry.row,temp->u.entry.col,temp->u.entry.value);
        head=head->u.next;
    }
}

void merase(matrixPointer *node){
    matrixPointer x,y,head=(*node)->right;
    
    int i;//numHeads;
    for(i=0;i<(*node)->u.entry.row;i++){
        y=head->right;
        while(y!=head){
            x=y;
            y=y->right;
            free(x);
        }
        x=head;
        head=head->u.next;
        free(x);
    }
    y=head;
    while(y!=*node){
        x=y;y=y->u.next;free(x);
    }
    free(*node);
    *node=NULL;
}

matrixPointer madd(matrixPointer first, matrixPointer second) {
    if (first->u.entry.col != second->u.entry.col || first->u.entry.row != second->u.entry.row) {
        printf("\n**두 행렬을 더할 수 없습니다.\n");
        end();
        
    }
    int numRows=first->u.entry.row, numCols=first->u.entry.col, numHeads, i;
    int row, col, value;
    matrixPointer temp, last, node;
    matrixPointer frist_head = first->right, second_head = second->right;
    matrixPointer first_temp, second_temp;
    
    //mread와 같이 노드 만들기
    numHeads = (numRows > numCols) ? numRows : numCols;
    
    node = newNode();
    node->tag = entry;
    node->u.entry.row = first->u.entry.row;
    node->u.entry.col = first->u.entry.col;
   
    for (i = 0; i < numHeads; i++) {
        //Make head nodes and connect them.
        temp = newNode();
        hdnode[i] = temp;
        hdnode[i]->tag = head;
        hdnode[i]->right = temp;
        hdnode[i]->u.next = temp;
    }
    last = hdnode[0];
    
    first_temp = frist_head->right;
    second_temp = second_head->right;
    
    //더하기
    for(i = 0; i < numRows; i++) {
        first_temp = frist_head->right;
        second_temp = second_head->right;
        
        if (first_temp == frist_head && second_temp == second_head);
        else if (second_temp == second_head) {
            last = hdnode[first_temp->u.entry.row];
            for (; first_temp != frist_head; first_temp = first_temp->right) {
                row = first_temp->u.entry.row;
                col = first_temp->u.entry.col;
                value = first_temp->u.entry.value;
                temp = newNode();
                temp->tag = entry;
                temp->u.entry.row = row;
                temp->u.entry.col = col;
                temp->u.entry.value = value;
                last->right = temp;
                last = temp;
                hdnode[col]->u.next->down = temp;
                hdnode[col]->u.next = temp;
            }
            last->right = hdnode[row];
        }
        
        else if (first_temp == frist_head) {
            last = hdnode[second_temp->u.entry.row];
            for (; second_temp != second_head; second_temp = second_temp->right) {
                row = second_temp->u.entry.row;
                col = second_temp->u.entry.col;
                value = second_temp->u.entry.value;
                temp = newNode();
                temp->tag = entry;
                temp->u.entry.row = row;
                temp->u.entry.col = col;
                temp->u.entry.value = value;
                last->right = temp;
                last = temp;
                hdnode[col]->u.next->down = temp;
                hdnode[col]->u.next = temp;
            }
            last->right = hdnode[row];
        }
        else if (first_temp->u.entry.row == second_temp->u.entry.row) {
            last = hdnode[first_temp->u.entry.row];
            
            while (first_temp != frist_head || second_temp != second_head) {
                {
                if (second_temp == second_head) {
                    col = first_temp->u.entry.col;
                    value = first_temp->u.entry.value;
                    first_temp = first_temp->right;
                }
                else if (first_temp == frist_head||first_temp->u.entry.col > second_temp->u.entry.col) {
                    row = second_temp->u.entry.row;
                    col = second_temp->u.entry.col;
                    value = second_temp->u.entry.value;
                    second_temp = second_temp->right;
                }
                else if (first_temp->u.entry.col < second_temp->u.entry.col) {
                    row = first_temp->u.entry.row;
                    col = first_temp->u.entry.col;
                    value = first_temp->u.entry.value;
                    first_temp = first_temp->right;
                }
                else if (first_temp->u.entry.col == second_temp->u.entry.col) {
                    row = first_temp->u.entry.row;
                    col = first_temp->u.entry.col;
                    value = first_temp->u.entry.value + second_temp->u.entry.value;
                    first_temp = first_temp->right;
                    second_temp = second_temp->right;
                }
            }
                if (value) {//read처럼
                    temp = newNode();
                    temp->tag = entry;
                    temp->u.entry.row = row;
                    temp->u.entry.col = col;
                    temp->u.entry.value = value;
                    last->right = temp;
                    last = temp;
                    hdnode[col]->u.next->down = temp;
                    hdnode[col]->u.next = temp;
                    last->right = hdnode[row];
                }
            }
        }
        frist_head = frist_head->u.next;
        second_head = second_head->u.next;
    }
    //read처럼!
    for (i = 0; i < numCols; i++)
        hdnode[i]->u.next->down = hdnode[i];
    for (i = 0; i < numHeads - 1; i++)
        hdnode[i]->u.next = hdnode[i + 1];
 
    hdnode[numHeads - 1]->u.next = node;
    node->right = hdnode[0];
    
    return node;
}

matrixPointer mmul(matrixPointer first, matrixPointer second) {
    if (first->u.entry.col != second->u.entry.row) {
        printf("\n**두 행렬을 곱할 수 없습니다.\n");
        end();
    }
    int numRows=first->u.entry.row, numCols=second->u.entry.col, numHeads, i;
    int row, col, value;
    matrixPointer temp, last, node;
    matrixPointer first_head = first->right, second_head = second->right;
    matrixPointer first_temp, second_temp;

    numHeads = (numRows > numCols) ? numRows : numCols;
    
    node = newNode();
    node->tag = entry;
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;
    for (i = 0; i < numHeads; i++) {
        temp = newNode();
        hdnode[i] = temp;
        hdnode[i]->tag = head;
        hdnode[i]->right = temp;
        hdnode[i]->u.next = temp;
    }
    last = hdnode[0];
    
    first_temp = first_head->right;
    second_temp = second_head->right;
    
    //곱
    for (int j = 0; j < numRows; j++) {
        last = hdnode[j];
        first_temp = first_head->right;
        second_temp = second_head->down;
        for (i = 0; i < numCols; i++) {
            value = 0;
            while (first_temp != first_head && second_temp != second_head) {
                if (first_temp->u.entry.col == second_temp->u.entry.row) {
                    value += (first_temp->u.entry.value * second_temp->u.entry.value);
                    row = first_temp->u.entry.row;
                    col = second_temp->u.entry.col;
                    first_temp = first_temp->right;
                    second_temp = second_temp->down;
                }
                
                else if (first_temp->u.entry.col > second_temp->u.entry.row)
                    second_temp = second_temp->down;
                
                else if (first_temp->u.entry.col < second_temp->u.entry.row)
                    first_temp = first_temp->right;
            }
            if (value) {
                temp = newNode();
                temp->tag = entry;
                temp->u.entry.row = row;
                temp->u.entry.col = col;
                temp->u.entry.value = value;
                last->right = temp;
                last = temp;
                hdnode[col]->u.next->down = temp;
                hdnode[col]->u.next = temp;
                last->right = hdnode[row];
            }
            first_temp = first_head->right;
            second_head = second_head->u.next;
            second_temp = second_head->down;
        }

        first_head = first_head->u.next;
        second_head = second->right;
        last->right = hdnode[j];
    }
    for (i = 0; i < numCols; i++)
        hdnode[i]->u.next->down = hdnode[i];
    for (i = 0; i < numHeads - 1; i++)
        hdnode[i]->u.next = hdnode[i + 1];
    hdnode[numHeads - 1]->u.next = node;
    node->right = hdnode[0];
  

    return node;
}


matrixPointer mtranspose(matrixPointer f){
    int numRows,numCols,numHeads,i;//for the new node
    int row,col,value,currentRow=0;
    matrixPointer temp,last,node,first_temp;
    matrixPointer first_head=f->right;
    
    numRows=f->u.entry.row;
    numCols=f->u.entry.col;
    numHeads=(numCols>numRows)?numCols:numRows;
    //mread와 같은 방법으로 새로운 노드를 만든다
    node=newNode();
    node->tag=entry;
    node->u.entry.row=numRows;
    node->u.entry.col=numCols;
    
    for(i=0;i<numHeads;i++){
        temp=newNode();
        hdnode[i]=temp;
        hdnode[i]->tag=head;
        hdnode[i]->right=temp;
        hdnode[i]->u.next=temp;
    }
    
    currentRow=0;
    last=hdnode[0];
    
    //역 구하기
    for(i=0;i<numCols;i++){
        last=hdnode[i];
        for(first_temp=first_head->down;first_temp
            !=first_head;first_temp=first_temp->down){
            col=first_temp->u.entry.col;
            row=first_temp->u.entry.row;
            value=first_temp->u.entry.value;
            
            temp=newNode();
            temp->tag = entry;
            temp->u.entry.row = col;
            temp->u.entry.col = row;
            temp->u.entry.value = value;
            last->right = temp;
            last = temp;
            hdnode[col]->u.next->down = temp;
            hdnode[col]->u.next = temp;
            last->right = hdnode[row];
        }
        first_head=first_head->u.next;
        last->right=hdnode[i];
    }
    for(i=0;i<numRows;i++)  hdnode[i]->u.next->down=hdnode[i];
    for(i=0;i<numHeads-1;i++)    hdnode[i]->u.next=hdnode[i+1];
    
    hdnode[numHeads-1]->u.next=node;
    node->right=hdnode[0];
    
    return node;
}

void menu_1(){
    int c;
    printf("-------------------------메뉴선택-------------------------\n");
    printf("                [1]희소행렬 입력하기 [2]나가기                \n");
    printf("--------------------------------------------------------\n");
    printf("<원하는 메뉴번호를 입력해주세요>--->>");
    scanf("%d",&c);
    switch(c){
        case 1:
            one=mread();
            mwrite(one);
            break;
        default:
            exit(0);
    }
}

void menu_2(){
    int c;
    printf("-------------------------메뉴선택-------------------------\n");
    printf("   [1]두번째 희소행렬 입력 [2]첫 희소행렬의 역행렬 구하기 [3]나가기   \n");
    printf("--------------------------------------------------------\n");
    printf("<원하는 메뉴번호를 입력해주세요>--->>");
    scanf("%d",&c);
    switch(c){
        case 1:
            two=mread();
            mwrite(two);
            break;
        case 2:
            result=mtranspose(one);
            mwrite(result);
            end();
        default:
            exit(0);
    }
}

void menu_3(){
    int c;
    printf("-------------------------메뉴선택-------------------------\n");
    printf("           [1]두 행렬 더하기 [2]두 행렬 곱하기 [3]나가기         \n");
    printf("--------------------------------------------------------\n");
    printf("<원하는 메뉴번호를 입력해주세요>--->>");
    scanf("%d",&c);
    switch (c) {
        case 1:
            result=madd(one,two);
            mwrite(result);
            end();
            
        case 2:
            result=mmul(one, two);
            mwrite(result);
            end();
        default:
            exit(0);
    }
}

