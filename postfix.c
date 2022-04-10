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

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixpush(char x); //postfixStack�� �� �߰�
char postfixPop(); //postfixStack���� �� ������
void evalPush(int x); //evalStack�� �� �߰�
int evalPop(); //evalStack���� �� ������
void getInfix(); //���� ǥ������� �Է¹���
precedence getToken(char symbol); //���� ȹ��
precedence getPriority(char x); //�켱���� ȹ��
void charCat(char* c); //���� ǥ��� ������ ���ڿ� �߰�
void toPostfix(); //���� ǥ������� ��ȯ
void debug(); //���� �����
void reset(); //�ʱ�ȭ
void evaluation(); //���
int Prioritycmp(int ex,int st); //�켱���� �� �Լ�

int main()
{
	char command;
    printf("[----- 2021041046 ������ -----]\n"); //�й�, �̸� ���
	do{
		printf("----------------------------------------------------------------\n"); //��ɾ� �ȳ�
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��ɾ� �Է� ����

		switch(command) { //�Էµ� ��ɾ ���� �б�
		case 'i': case 'I':
			getInfix(); //���� ǥ������� �Է¹���
			break;
		case 'p': case 'P':
			toPostfix(); //���� ǥ������� ��ȯ�ؼ� postfixExp�� ����
			break;
		case 'e': case 'E':
			evaluation(); //postfixExp�� ����� ���뿡 ���� ���� �� ���
			break;
		case 'd': case 'D':
			debug(); //������ ������ ���� ���
			break;
		case 'r': case 'R':
			reset(); //�ʱ�ȭ
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�ȳ�
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� �Էµ� ������ �ݺ�

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //���� õ���� 1 ���� �� ���� ����
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //������ �� ���
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //���� õ���� 1 ���� �� �� ��ȯ
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
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
    printf("Type the expression >>> "); //�ȳ�
    scanf("%s",infixExp); //���� ǥ������� �Է¹���
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		/* �ʿ��� ���� �ϼ� */
        if(getPriority(*exp) == 1) { //�ǿ������� ���
            charCat(exp); //postfixExp�� ��� �ش� ���� �߰�
        } else {
            if(*exp == '(') //���� ��ȣ�� ���
            {
                postfixPush(*exp); //���� ��ȣ�� ���� �ܺο� ���� �� �켱������ �����Ƿ� ������ �Է¹���
            } else if(*exp == ')') //������ ��ȣ�� ���
            {
                do { //�ݺ�
                    x = postfixPop(); //postfixStack���� x�� Pop�� ��
                    if(x != '(') //���� ��ȣ�� �ƴ� ���
                        charCat(&x); //postfixExp�� �ش� �����ڸ� �߰�
                } while(x != '('); //���� ��ȣ�� ���� �� ����
            } else { //��Ÿ �ǿ������� ���
                while(postfixStackTop != -1 && !Prioritycmp(getPriority(*exp), getPriority(postfixStack[postfixStackTop]))) //������ �����ų�, �켱������ ���ų� ���� �����ڸ� ���� �� ���� 
                {
                    x = postfixPop();
                    charCat(&x); //������ ž�� �ִ� �����ڸ� �̾Ƽ� �߰�
                }
                postfixPush(*exp); //�Է� ���� ���� ���ÿ� ����
            }
        }
        exp++; //exp�� ����Ű�� infixExp���ڿ��� ��ġ�� �� ���� �ڷ� �ű�
	}

	/* �ʿ��� ���� �ϼ� */
    while(postfixStackTop != -1) //������ �� �� ����
    {
        x = postfixPop();
        charCat(&x); //���� ������ ���� Pop�ؼ� �߰�
    }
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); //���� ǥ��� ���
	printf("postExp =  %s\n", postfixExp);  //���� ǥ��� ���
	printf("eval result = %d\n", evalResult);  //��� ��� ���

	printf("postfixStack : "); //���� ǥ��� ���� ���� ���
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //���� ǥ��� �ʱ�ȭ
	postfixExp[0] = '\0'; //���� ǥ��� �ʱ�ȭ

	for(int i = 0; i < MAX_STACK_SIZE; i++) //���� ǥ��� ���� �ʱ�ȭ
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //���� ǥ��� ���� �ʱ�ȭ
	evalStackTop = -1; //��� ����� ���� �ʱ�ȭ
	evalResult = 0; //��� ��� �ʱ�ȭ
}

void evaluation()
{
    char *exp = postfixExp; //postfixExp�� ���ڸ� �ϳ��� �б� ���� ������ exp
    int r; //�ӽ� ����� ���� ����
    int op[2]; //������ ���߱� ���� �ӽú���

	/* postfixExp, evalStack�� �̿��� ��� */
    while(*exp != '\0') //exp�� postfixExp�� ���� ����ų �� ����
    {
        if(getPriority(*exp) == 1) { //�ǿ������� ���
            evalPush(*exp & 0x0F); //�ǿ������̹Ƿ� �ٷ� �Է��ϰ�, ���ڴ� �ƽ�Ű�ڵ�� 0~9�� 0x30���� 0x39���� ������� �� �����Ƿ� ���� �����ڸ� 3 �κ��� ����ũ�� �����ָ� �ȴ�
        } else { //�������� ���
            switch (getPriority(*exp))
            {
            case 7: //������ ���
                r = evalPop() * evalPop(); //���ÿ��� �ΰ��� �ǿ����ڸ� ������ ���
                evalPush(r); //��� ���� �ǿ����ڸ� �ٽ� ���ÿ� ����
                break;
            case 6: //�������� ���
                
                op[0] = evalPop();
                op[1] = evalPop();
                if(op[0] == 0) { //0���� �����⸦ �õ��� ���
                    printf("can't divide by 0!\n"); //�ȳ�
                    return;
                }
                r = op[1] / op[0]; //���ÿ��� �ΰ��� �ǿ����ڸ� ������ ���
                evalPush(r); //��� ���� �ǿ����ڸ� �ٽ� ���ÿ� ����
                break;
            case 5: //������ ���
                r = evalPop() + evalPop(); //���ÿ��� �ΰ��� �ǿ����ڸ� ������ ���
                evalPush(r); //��� ���� �ǿ����ڸ� �ٽ� ���ÿ� ����
                break;
            case 4: //������ ���
                op[0] = evalPop();
                op[1] = evalPop();
                r = op[1] - op[0]; //���ÿ��� �ΰ��� �ǿ����ڸ� ������ ���
                evalPush(r); //��� ���� �ǿ����ڸ� �ٽ� ���ÿ� ����
                break;
            default: //�� ���� ���
                printf("Error!\n"); //�ȳ�
                return;
                break;
            }
        }
        exp++; //exp�� ����Ű�� postfixExp�� ��ġ�� �� ���ھ� �ڷ� �̵�
    }
    evalResult = evalStack[0]; //���� ǥ��� ������ Ư¡�� ���� ���� �� �ٴڿ� ��� ����� ����ǹǷ� ���� �� �ٴ��� ������� �����ϸ� �ȴ�.
}

int Prioritycmp(int ex,int st)
{
    int result = 0;
    if((ex == 5 && st == 4) || (ex == 7 && ex == 6)) //����-����, ����-�������� ���� �켱������ �����Ƿ� ����ó��
        return 0;
    return ex > st; //�Էµ� �ǿ����ڰ� ���ÿ� ����� �ǿ����ں��� �켱������ ���� ��� 1, �ƴҰ�� 0��ȯ
}