#include <stdio.h>
#include <stdlib.h>


typedef struct node {  //구조체
	int key;  //데이터 변수
	struct node *left;
	struct node *right;
} Node;

//스택
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

//큐
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;


//함수
int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  
int insert(Node* head, int key);     
int freeBST(Node* head);


void iterativeInorder(Node* ptr);    
void levelOrder(Node* ptr);	         
int deleteNode(Node* head, int key);  
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);



void printStack();



int main()
{
    printf("김민서 2022040010");	
	char command;
	int key;
	Node* head = NULL;  //헤드 초기화

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //명령 문자 입력

		switch(command) {  //케이스에 따른 함수 실행 
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {  //bst-2초기화

	if(*h != NULL)  //트리가 NULL이 아니면 메모리 할당 해제
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node));  //헤드에 메모리 할당
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)  //오름차순 재귀
{
	if(ptr) {
		recursiveInorder(ptr->left);  //재귀 왼쪽 출력
		printf(" [%d] ", ptr->key);  //최상위 노드 출력
		recursiveInorder(ptr->right);  //재귀 오른쪽 출력
	}
}


void iterativeInorder(Node* node)  //오름차순 (스택)
{
	for(;;)  //무한반복
	{
		for(; node; node = node->left)
			push(node);  //작으면 push
		node = pop();

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}


void levelOrder(Node* ptr)  //최상위에서 하위로 (큐)
{

	if(!ptr) return;

	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key)  //노드 삽입
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //메모리 할당
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		if(ptr->key == key) return 1;

		parentNode = ptr;  //부모노드 계속 추적

		if(ptr->key < key)  //비교해서 크면 오른쪽 작으면 왼쪽
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)  //노드 삭제
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;



	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;	
			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	if(ptr->left == NULL && ptr->right == NULL)  //leaf 일때
	{
		if(parent != NULL) { 
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {

			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	if ((ptr->left == NULL || ptr->right == NULL))  //한쪽만 하위 노드가 있을 때
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {

			root = child;
		}

		free(ptr);
		return 1;
	}


	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;


	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)  //메모리 해제
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()  //pop 함수
{
	if (top < 0) return NULL;
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top] = aNode;
}


void printStack()  //스택 출력
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()  
{
	if (front == rear) {

		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {

		return;
	}

	queue[rear] = aNode;
}
