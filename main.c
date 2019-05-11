//
//  main.c
//  자료구조 과제1
//
//  Created by TSAR on 02/04/2019.
//  Copyright © 2019 TSAR. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

typedef struct polynomial{
    float coef;
    int expon;
}poly[];//구조채를 만들다.


poly terms;
int sa,fa,sb,fb,avail,sd,fd;/**sx,fx꼴로 각 다항식의 시작위치와 종료위치를 기록.
                             avail은 합인 다항식의 계산때 사용.
                             **/

int COMPARE(int a,int b);//a와 b의 exponential의 크기를 비교. padd에서 사용됨
void padd (int startA, int finishA, int startB, int finishB, int *startD, int *finishD);//a와 b의 덧셈
void attach(float coefficient, int exponent);//합의 다항식을 만드는 용도
void check(int c_p,int p);//input이 내림차수인지 확인

int main(int argc, const char * argv[]) {
    float c;
    int e,c_e;//e는 지수,c_e는 전에 입력한 지수를 저장해서, check에 사용함
    printf("내림차순으로 입력해주세요. 그렇지 않으면 프로그램이 종료됩니다.\n\n");
    
    printf("첫번째 다항식을 입력하세요\n");
    while(1){
        scanf("%f %d",&c,&e);
        terms[fa].coef=c;
        terms[fa].expon=e;
        check(c_e,e);
        if(getchar()=='\n')
            break;
        if(c==0) continue;
        fa++;
        c_e=e;
    }
    sb=fa+1;
    fb=sb;
  
    printf("두번째 다항식을 입력하세요\n");
    while(1){
        scanf("%f %d",&c,&e);
        terms[fb].coef=c;
        terms[fb].expon=e;
        check(terms[fb-1].expon,e);
        if(getchar()=='\n')
            break;
        fb++;
        c_e=e;
    }
    avail=fb+1;
    padd(sa,fa,sb,fb,&sd,&fd);
    
   //합의 다항식 출력
    int i;
    for(i=sd;i<=fd;i++){
        if(i==fd){
            if(terms[i].expon==0)printf("%.3f\n",terms[i].coef);
            else printf("%.3fx^%d\n",terms[i].coef,terms[i].expon);
            break;
        }
        
        else printf("%.3fx^%d+",terms[i].coef,terms[i].expon);
    }

    return 0;
}


int COMPARE(int a,int b){
    if(a<b) return -1;
    else if(a==b) return 0;
    else return 1 ;
}


void padd (int startA, int finishA, int startB, int finishB, int *startD, int *finishD)
{ /* add A(x) and B(x) to obtain D(x) */
    float coefficient;
    
    *startD = avail;
    
    while ( startA <= finishA && startB <= finishB )
        switch ( COMPARE(terms[startA].expon, terms[startB].expon) ){
            case -1: /* a expon < b expon */
                attach( terms[startB].coef, terms[startB].expon );
                startB++;
                break;
            case 0: /* equal exponents */
                coefficient = terms[startA].coef + terms[startB].coef;
                if ( coefficient ) attach ( coefficient, terms[startA].expon );
                startA++;
                startB++;
                break;
            case 1: /* a expon > b expon */
                attach( terms[startA].coef, terms[startA].expon );
                startA++;
        } /* end of switch */
    
    /* add in remaining terms of A(x) */
    for( ; startA <= finishA; startA++ )
        attach( terms[startA].coef, terms[startA].expon );
    
    /* add in remaining terms of B(x) */
    for( ; startB <= finishB; startB++ )
        attach( terms[startB].coef, terms[startB].expon );
    
    *finishD =avail -1;
}

void attach(float coefficient, int exponent)
{
    /* add a new term to the polynomial */
    if (avail >= MAX_TERMS)
    {
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail].expon = exponent;
    avail++;
}

void check(int cp, int p){
    if(cp>0&&cp<=p){
        printf("내림차순으로 입력하지 않았습니다.");
        exit(1);
    }
}
