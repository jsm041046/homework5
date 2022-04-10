/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x); //postfixStack에 값 추가
char postfixPop(); //postfixStack에서 값 꺼내옴
void evalPush(int x); //evalStack에 값 추가
int evalPop(); //evalStack에서 값 꺼내옴
void getInfix(); //중위 표기법으로 입력받음
precedence getToken(char symbol); //문자 획득
precedence getPriority(char x); //우선순위 획득
void charCat(char* c); //후위 표기법 변수에 문자열 추가
void toPostfix(); //후위 표기법으로 변환
void debug(); //변수 디버그
void reset(); //초기화
void evaluation(); //계산
int Prioritycmp(int ex,int st); //우선순위 비교 함수

int main()
{
	char command;
    printf("[----- 2021041046 전설민 -----]\n"); //학번, 이름 출력
	do{
		printf("----------------------------------------------------------------\n"); //명령어 안내
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어 입력 받음

		switch(command) { //입력된 명령어에 따른 분기
		case 'i': case 'I':
			getInfix(); //중위 표기법으로 입력받음
			break;
		case 'p': case 'P':
			toPostfix(); //후위 표기법으로 전환해서 postfixExp에 저장
			break;
		case 'e': case 'E':
			evaluation(); //postfixExp에 저장된 내용에 따라 연산 후 출력
			break;
		case 'd': case 'D':
			debug(); //변수의 세세한 내용 출력
			break;
		case 'r': case 'R':
			reset(); //초기화
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //안내
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될 때까지 반복

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //스택 천장을 1 높인 후 변수 대입
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //스택이 빈 경우
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //스택 천장을 1 낮춘 후 값 반환
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> "); //안내
    scanf("%s",infixExp); //중위 표기법으로 입력받음
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* 필요한 로직 완성 */
        if(getPriority(*exp) == 1) { //피연산자일 경우
            charCat(exp); //postfixExp에 즉시 해당 값을 추가
        } else {
            if(*exp == '(') //왼쪽 괄호일 경우
            {
                postfixPush(*exp); //왼쪽 괄호는 스택 외부에 있을 때 우선순위가 높으므로 무조건 입력받음
            } else if(*exp == ')') //오른쪽 괄호일 경우
            {
                do { //반복
                    x = postfixPop(); //postfixStack에서 x로 Pop을 함
                    if(x != '(') //왼쪽 괄호가 아닐 경우
                        charCat(&x); //postfixExp에 해당 연산자를 추가
                } while(x != '('); //왼쪽 괄호가 나올 때 까지
            } else { //기타 피연산자의 경우
                while(postfixStackTop != -1 && !Prioritycmp(getPriority(*exp), getPriority(postfixStack[postfixStackTop]))) //스택이 끝나거나, 우선순위가 같거나 낮은 연산자를 만날 때 까지 
                {
                    x = postfixPop();
                    charCat(&x); //스택의 탑에 있는 연산자를 뽑아서 추가
                }
                postfixPush(*exp); //입력 받은 값을 스택에 저장
            }
        }
        exp++; //exp가 가르키는 infixExp문자열의 위치를 한 문자 뒤로 옮김
	}

	/* 필요한 로직 완성 */
    while(postfixStackTop != -1) //스택이 빌 때 까지
    {
        x = postfixPop();
        charCat(&x); //스택 내부의 값을 Pop해서 추가
    }
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //전위 표기법 출력
	printf("postExp =  %s\n", postfixExp);  //후위 표기법 출력
	printf("eval result = %d\n", evalResult);  //계산 결과 출력

	printf("postfixStack : "); //후위 표기법 스택 내용 출력
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //전위 표기법 초기화
	postfixExp[0] = '\0'; //후위 표기법 초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++) //후위 표기법 스택 초기화
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //후위 표기법 스택 초기화
	evalStackTop = -1; //계산 결과용 스택 초기화
	evalResult = 0; //계산 결과 초기화
}

void evaluation()
{
    char *exp = postfixExp; //postfixExp의 문자를 하나씩 읽기 위한 포인터 exp
    int r; //임시 계산결과 저장 변수
    int op[2]; //순서를 맞추기 위한 임시변수

	/* postfixExp, evalStack을 이용한 계산 */
    while(*exp != '\0') //exp가 postfixExp의 끝을 가르킬 때 까지
    {
        if(getPriority(*exp) == 1) { //피연산자일 경우
            evalPush(*exp & 0x0F); //피연산자이므로 바로 입력하고, 숫자는 아스키코드로 0~9가 0x30부터 0x39까지 순서대로 들어가 있으므로 앞의 십의자리 3 부분을 마스크로 지워주면 된다
        } else { //연산자일 경우
            switch (getPriority(*exp))
            {
            case 7: //곱셈일 경우
                r = evalPop() * evalPop(); //스택에서 두개의 피연산자를 꺼내서 계산
                evalPush(r); //계산 후의 피연산자를 다시 스택에 삽입
                break;
            case 6: //나눗셈일 경우
                
                op[0] = evalPop();
                op[1] = evalPop();
                if(op[0] == 0) { //0으로 나누기를 시도할 경우
                    printf("can't divide by 0!\n"); //안내
                    return;
                }
                r = op[1] / op[0]; //스택에서 두개의 피연산자를 꺼내서 계산
                evalPush(r); //계산 후의 피연산자를 다시 스택에 삽입
                break;
            case 5: //덧셈일 경우
                r = evalPop() + evalPop(); //스택에서 두개의 피연산자를 꺼내서 계산
                evalPush(r); //계산 후의 피연산자를 다시 스택에 삽입
                break;
            case 4: //뺄셈일 경우
                op[0] = evalPop();
                op[1] = evalPop();
                r = op[1] - op[0]; //스택에서 두개의 피연산자를 꺼내서 계산
                evalPush(r); //계산 후의 피연산자를 다시 스택에 삽입
                break;
            default: //그 외의 경우
                printf("Error!\n"); //안내
                return;
                break;
            }
        }
        exp++; //exp이 가르키는 postfixExp의 위치를 한 문자씩 뒤로 이동
    }
    evalResult = evalStack[0]; //후위 표기법 연산의 특징에 따라 스택 맨 바닥에 계산 결과가 저장되므로 스택 맨 바닥을 결과값에 저장하면 된다.
}

int Prioritycmp(int ex,int st)
{
    int result = 0;
    if((ex == 5 && st == 4) || (ex == 7 && ex == 6)) //덧셈-뺄셈, 곱셈-나눗셈의 경우는 우선순위가 같으므로 예외처리
        return 0;
    return ex > st; //입력된 피연산자가 스택에 저장된 피연산자보다 우선순위가 높은 경우 1, 아닐경우 0반환
}