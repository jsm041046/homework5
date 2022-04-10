/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue(); //ť�� �����ϰ� �ּҸ� ��ȯ
int freeQueue(QueueType *cQ); //ť�� �Ҵ�� �޸𸮸� ����
int isEmpty(QueueType *cQ); //ť�� ����ִ��� Ȯ��
int isFull(QueueType *cQ); //ť�� �� ���ִ��� Ȯ��
void enQueue(QueueType *cQ, element item); //ť�� ���� �ϳ� �Է�
void deQueue(QueueType *cQ, element* item); //ť�� ���� �ϳ� ����
void printQ(QueueType *cQ); //ť�� ���
void debugQ(QueueType *cQ); //ť�� ���� ������� ������
element getElement(); //ť�� ���Ҹ� �Է¹���

int main(void)
{
	QueueType *cQ = createQueue(); //ť�� �����ϰ� �ּҸ� ������ cQ���ٰ� ��ȯ
	element data; //ť�� ���Ҹ� �Է��ϰų� ��ȯ�޴� ����
	char command;  //����� �޴� ����
    printf("[----- 2021041046 ������ -----]\n"); //�й�, �̸� ���
	do{ //�ݺ���
		printf("\n-----------------------------------------------------\n"); //��ɿ� ���� �ȳ��� ���
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = "); //�ȳ�
		scanf(" %c", &command); //��� �Է�

		switch(command) { //��ɿ� ���� ����ġ �б�
		case 'i': case 'I': //i�Ǵ� I�� �Է����� ���
			data = getElement(); //data�� ���Ҹ� �Է¹���
			enQueue(cQ, data); //ť�� ���� �ϳ� �Է�
			break;
		case 'd': case 'D': //d�Ǵ� D�� �Է����� ���
			deQueue(cQ, &data); //ť�� ���� �ϳ� ������ �ּ� ���� ���� ���޵� data ������ ���� ��ȯ
			break;
		case 'p': case 'P': //p�Ǵ� P�� �Է����� ���
			printQ(cQ); //ť�� ���
			break;
		case 'b': case 'B': //b�Ǵ� B�� �Է����� ���
			debugQ(cQ); //ť�� ���� ������� ������
			break;
		case 'q': case 'Q': //q�Ǵ� Q�� �Է����� ���
   	        freeQueue(cQ); //ť�� �Ҵ�� �޸𸮸� ����
			break;
		default: //�� ���� ���� �Է����� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�ȳ�
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� Q�� �Է����� �ʾ��� �� ���� �ݺ�


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ; //ť�� ������ ����
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ���� ť�� �� ��ŭ�� �ּҸ� �Ҵ�
	cQ->front = 0; 
	cQ->rear = 0; //cQ�� ���� ���� �ʱ�ȭ
	return cQ; //������ cQ�� ����Ű�� �ּҸ� ��ȯ
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 0; //cQ�� �Ҵ���� ���� ��� ����� ť�� �Ҵ������� �̷������ �ʱ� ������ 0�� ��ȯ
    free(cQ); //cQ�� ����Ű�� �ּ��� �Ҵ��� ����
    return 1; //���������� ť�� �Ҵ� ������ �̷������� �˸�
}

element getElement()
{
	element item; //���Ҹ� �Է¹��� �ӽ� ���� item ����
	printf("Input element = "); //�ȳ�
	scanf(" %c", &item); //���Ҹ� �Է� ����
	return item; //�Է¹��� ���Ҹ� ��ȯ��
}

int isEmpty(QueueType *cQ)
{
    if(cQ == NULL) return -1; //ť�� �Ҵ���� ���� ��� ������ ���� �� �����Ƿ� ��� ���������� ������� �ʾҴٴ� ��ȣ�� -1�� ��ȯ
    else{
        if(cQ->front == cQ->rear) //cQ�� �� �պκа� �� �޺κ��� ���� ���(ť�� ���Ұ� �ϳ��� ������ rear�� front�� ���� �� ����)
        {
            return 1; //����ٴ� �ǹ̷� 1�� ��ȯ
        } else {
            return 0; //���� �ʾҴٴ� �ǹ̷� 0�� ��ȯ
        }
    }
}

int isFull(QueueType *cQ)
{
    if(cQ == NULL) return -1; //ť�� �Ҵ���� ���� ��� ������ ���� �� �����Ƿ� ��� ���������� ������� �ʾҴٴ� ��ȣ�� -1�� ��ȯ
    else{
        if((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) //cQ�� ������ ä���־���� ���� ��ġ�� front�� ��ġ�� ���(front�� Ư���� �������� �־�� ��)
        {
            return 1; //ť�� �� á�ٴ� �ǹ̷� 1�� ��ȯ
        } else {
            return 0; //ť�� �� ���� �ʾҴٴ� �ǹ̷� 1�� ��ȯ
        }
    }
}

void enQueue(QueueType *cQ, element item)
{
	if(cQ == NULL) return; //ť�� �Ҵ���� ���� ��� ������ ���� �� �����Ƿ� ��� ���ν����� ��������
    else {
        if(isFull(cQ)) //cQ�� �� �� ���
        {
            printf("Queue is full!"); //�ȳ�
            return; //ť�� �� ���� ���̻� ���Ҹ� �Է��� �� �����Ƿ� ��� ���ν����� ������
        } else {
            cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //ť�� �� �޺κ��� �� ĭ �ڷ� �ű�
            cQ->queue[cQ->rear] = item; //����ť�� �� �޺κп� �Է¹��� ���Ҹ� ������
        }
    }
}

void deQueue(QueueType *cQ, element *item)
{
    if(cQ == NULL) return; //ť�� �Ҵ���� ���� ��� ������ ���� �� �����Ƿ� ��� ���ν����� ��������
    else {
        if(isEmpty(cQ)) //cQ�� �� �� ���
        {
            printf("Queue is empty!"); //�ȳ�
            return; //ť�� ��� ���̻� ���Ҹ� ������ �� �����Ƿ� ��� ���ν����� ������
        } else {
            *item = cQ->queue[cQ->rear]; //�Ű������� �Է¹��� ���� ������ ť�� �� �ڿ� �ִ� ���Ҹ� ��ȯ��
            cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //����ť�� �� �պκ��� �� ĭ �ڷ� �ű�
        }
    }
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first ������ ť�� �������� �Է���
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last ������ ť�� ������ �Է���

	printf("Circular Queue : ["); //�ȳ�

	i = first; //i�� first������ ������
	while(i != last){ //i�� last�� ������ �� ���� �ݺ���
		printf("%3c", cQ->queue[i]); //���� ���� 3ĭ�� �ΰ� ť�� �����
		i = (i+1)%MAX_QUEUE_SIZE; //i�� ����ť�� ���� ��ȯ�ϰ� ����

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n"); //�ȳ�
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //i�� �迭�� ó������ ������ ��ȸ
	{
		if(i == cQ->front) { //i�� front�� ����ų ���
			printf("  [%d] = front\n", i); //�迭�� i��ġ�� front�� ��ġ���� �����
			continue; //�ݺ��� ��� ��ȸ
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //�ش� �迭�� ��ġ�ϴ� ���Ҹ� �����

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front�� ��ġ�� rear�� ��ġ�� �����
}
