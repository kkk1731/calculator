//累乗を追加しました
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int tokenKind;
int tokenValue;
int chr;

int stack[30];
int stackNum = 0;

void Push(int a);
int Pop();
void Plus();
void Minus();
void Multiply();
void Divide();
void Power();
void error();

int getToken();
int getFormula();
void Formula();//式
void Term(); //項
void Factor();//因子
void P();

void Push(int a){
  stack[stackNum++]=a;
}
int Pop(){
  return stack[--stackNum];
}

void Plus(){
  int b=Pop();
  int a=Pop();
  Push(a+b);
}
void Minus(){
  int b=Pop();
  int a=Pop();
  Push(a-b);
}
void Multiply(){
  int b=Pop();
  int a=Pop();
  Push(a*b);
}
void Divide(){
  int b=Pop();
  int a=Pop();
  Push(a/b);
}
void Power(){
  int b=Pop();
  int a=Pop();
  Push(pow(a,b));
}

void error(){
  printf("\nwrong expression");
  exit(1);
}

void Formula(){
  Term();

  while(tokenKind == '+' || tokenKind == '-'){
    if(tokenKind == '+'){
      getToken();
      Term();
      Plus();
    }
    else{
      getToken();
      Term();
      Minus();
    }
  }
}

void Term(){
  P();

  while(tokenKind == '*' || tokenKind == '/'){
    if(tokenKind == '*'){
      getToken();
      P();
      Multiply();
    }
    else{
      getToken();
      P();
      Divide();
    }
  }
}

void P(){
  Factor();
  while(tokenKind == '^'){
    getToken();
    P();
    Power();
  }
}

void Factor(){
  if(tokenKind == -1){//token::=number
    Push(tokenValue);
    getToken();

  }
  else if(tokenKind == '('){
    getToken();

    Formula();
    if(tokenKind == ')'){
      getToken();
    }
    else error();
  }
  else{
    error();
  }
}



int getToken(){
  /*skip "space" and "tab"*/
  while(chr == ' ' || chr == '\t'){
    chr = getchar();
  }
  /*end*/
  if(chr == '\n' || chr == EOF){
    return -1;
  }
  /*token::=number*/
  if(isdigit(chr)){
      tokenKind = -1;
      tokenValue = chr - '0';
      while(isdigit(chr=getchar())){
        tokenValue *= 10;
        tokenValue += chr - '0';
      }
      return 0;
    }
    /*token::=symbol*/
  switch(chr){
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '^':
      tokenKind = chr;
      chr = getchar();
      return 0;
  }
  return -1;
}

int main(){

  printf(">");
  chr=getchar();

  while(getToken() >= 0){//　>の後の標準入力がEnterなら終了
    Formula();
    printf("%d\n", Pop());
    printf(">");

    chr=getchar();

  }
  return 0;
}


/*
//字句解析
int getFormula(){
  chr = getchar();
  if(getToken() < 0){
    return -1;
  }
  else{
    if (tokenKind == -1) printf("%d", tokenValue);
    else printf("%c", tokenKind);
  }
  while(getToken() >= 0){
    printf(",");
    if (tokenKind == -1) printf("%d", tokenValue);
    else printf("%c", tokenKind);
  }
  return 0;
}
*/
