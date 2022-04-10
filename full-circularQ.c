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


QueueType *createQueue(); //큐를 생성하고 주소를 반환
int freeQueue(QueueType *cQ); //큐에 할당된 메모리를 정리
int isEmpty(QueueType *cQ); //큐가 비어있는지 확인
int isFull(QueueType *cQ); //큐가 꽉 차있는지 확인
void enQueue(QueueType *cQ, element item); //큐에 값을 하나 입력
void deQueue(QueueType *cQ, element* item); //큐에 값을 하나 삭제
void printQ(QueueType *cQ); //큐를 출력
void debugQ(QueueType *cQ); //큐에 대한 디버깅을 시행함
element getElement(); //큐의 원소를 입력받음

int main(void)
{
	QueueType *cQ = createQueue(); //큐를 생성하고 주소를 포인터 cQ에다가 반환
	element data; //큐의 원소를 입력하거나 반환받는 변수
	char command;  //명령을 받는 변수
    printf("[----- 2021041046 전설민 -----]\n"); //학번, 이름 출력
	do{ //반복문
		printf("\n-----------------------------------------------------\n"); //명령에 대한 안내문 출력
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = "); //안내
		scanf(" %c", &command); //명령 입력

		switch(command) { //명령에 따른 스위치 분기
		case 'i': case 'I': //i또는 I를 입력했을 경우
			data = getElement(); //data에 원소를 입력받음
			enQueue(cQ, data); //큐에 값을 하나 입력
			break;
		case 'd': case 'D': //d또는 D를 입력했을 경우
			deQueue(cQ, &data); //큐에 값을 하나 꺼내서 주소 값을 통해 전달된 data 변수에 값을 반환
			break;
		case 'p': case 'P': //p또는 P를 입력했을 경우
			printQ(cQ); //큐를 출력
			break;
		case 'b': case 'B': //b또는 B를 입력했을 경우
			debugQ(cQ); //큐에 대한 디버깅을 시행함
			break;
		case 'q': case 'Q': //q또는 Q를 입력했을 경우
   	        freeQueue(cQ); //큐에 할당된 메모리를 정리
			break;
		default: //그 외의 것을 입력했을 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //안내
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q를 입력하지 않았을 때 까지 반복


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ; //큐의 포인터 선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ에게 큐로 쓸 만큼의 주소를 할당
	cQ->front = 0; 
	cQ->rear = 0; //cQ가 가진 변수 초기화
	return cQ; //포인터 cQ가 가르키는 주소를 반환
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 0; //cQ가 할당되지 않은 경우 제대로 큐의 할당해제가 이루어지지 않기 때문에 0을 반환
    free(cQ); //cQ가 가르키는 주소의 할당을 해제
    return 1; //정상적으로 큐의 할당 해제가 이뤄졌음을 알림
}

element getElement()
{
	element item; //원소를 입력받을 임시 변수 item 선언
	printf("Input element = "); //안내
	scanf(" %c", &item); //원소를 입력 받음
	return item; //입력받은 원소를 반환함
}

int isEmpty(QueueType *cQ)
{
    if(cQ == NULL) return -1; //큐가 할당되지 않은 경우 문제가 생길 수 있으므로 즉시 정상적으로 시행되지 않았다는 신호로 -1을 반환
    else{
        if(cQ->front == cQ->rear) //cQ의 맨 앞부분과 맨 뒷부분이 같을 경우(큐에 원소가 하나라도 있으면 rear는 front와 같을 수 없음)
        {
            return 1; //비었다는 의미로 1을 반환
        } else {
            return 0; //비지 않았다는 의미로 0을 반환
        }
    }
}

int isFull(QueueType *cQ)
{
    if(cQ == NULL) return -1; //큐가 할당되지 않은 경우 문제가 생길 수 있으므로 즉시 정상적으로 시행되지 않았다는 신호로 -1을 반환
    else{
        if((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) //cQ의 다음에 채워넣어야할 원소 위치가 front의 위치일 경우(front는 특성상 공란으로 있어야 함)
        {
            return 1; //큐가 꽉 찼다는 의미로 1을 반환
        } else {
            return 0; //큐가 꽉 차지 않았다는 의미로 1을 반환
        }
    }
}

void enQueue(QueueType *cQ, element item)
{
	if(cQ == NULL) return; //큐가 할당되지 않은 경우 문제가 생길 수 있으므로 즉시 프로시저를 빠져나옴
    else {
        if(isFull(cQ)) //cQ가 꽉 찬 경우
        {
            printf("Queue is full!"); //안내
            return; //큐가 꽉 차면 더이상 원소를 입력할 수 없으므로 즉시 프로시저를 종료함
        } else {
            cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //큐의 맨 뒷부분을 한 칸 뒤로 옮김
            cQ->queue[cQ->rear] = item; //원형큐의 맨 뒷부분에 입력받은 원소를 대입함
        }
    }
}

void deQueue(QueueType *cQ, element *item)
{
    if(cQ == NULL) return; //큐가 할당되지 않은 경우 문제가 생길 수 있으므로 즉시 프로시저를 빠져나옴
    else {
        if(isEmpty(cQ)) //cQ가 꽉 찬 경우
        {
            printf("Queue is empty!"); //안내
            return; //큐가 비면 더이상 원소를 제거할 수 없으므로 즉시 프로시저를 종료함
        } else {
            *item = cQ->queue[cQ->rear]; //매개변수로 입력받은 원소 변수에 큐의 맨 뒤에 있는 원소를 반환함
            cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //원형큐의 맨 앞부분을 한 칸 뒤로 옮김
        }
    }
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first 변수에 큐의 시작점을 입력함
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last 변수에 큐의 종점을 입력함

	printf("Circular Queue : ["); //안내

	i = first; //i에 first변수를 대입함
	while(i != last){ //i가 last와 같아질 때 까지 반복함
		printf("%3c", cQ->queue[i]); //앞의 공란 3칸을 두고 큐를 출력함
		i = (i+1)%MAX_QUEUE_SIZE; //i를 원형큐를 따라 순환하게 만듬

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n"); //안내
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //i를 배열의 처음부터 끝까지 순회
	{
		if(i == cQ->front) { //i가 front를 가르킬 경우
			printf("  [%d] = front\n", i); //배열의 i위치가 front의 위치임을 출력함
			continue; //반복문 즉시 순회
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //해당 배열에 위치하는 원소를 출력함

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front의 위치와 rear의 위치를 출력함
}
