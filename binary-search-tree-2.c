/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [한민우] [2018038047] -----]\n");
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
		scanf(" %c", &command);

		switch(command) {
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

		// case 'p': case 'P':
		// 	printStack();
		// 	break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	while(1){
		for( ; node; node = node->left){
			push(node); // 스택에 삽입
		}
		node = pop(); // 스택에서 삭제
		if(!node) break; // 스택이 공백이면
		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = 0;
	rear = 0;
	if(!ptr) return; /* 공백트리면 리턴 */
	enQueue(ptr);
	while(1){
		ptr = deQueue(); // 큐에 저장된 노드 받아옴
		if(ptr){ // 큐가 공백이 아니면
		printf(" [%d] ", ptr->key);
		// 자식이 공백이 아니면 큐에 삽입
		if(ptr->left) enQueue(ptr->left);
		if(ptr->right) enQueue(ptr->right);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
		/* check pre conditions */
	if(head == NULL){
		printf("Binary search tree is not initialized.\n");
		return 0;
	}
	Node* delnode = head->left;
	Node* prev = head;

	while(delnode != NULL && delnode->key != key){ // 삭제할 노드 탐색
		prev = delnode;
		if(delnode->key > key) delnode = delnode->left;
		else delnode = delnode->right;
	}

	/* 원하는 노드가 없다면 delnode == NULL */
	if(!delnode){
		printf("Cannot find the node [%d]\n",key);
		return 0;
	}
	// 1.삭제할 노드가 리프노드라면
	if(delnode->left == NULL && delnode->right == NULL){
		/* 삭제 대상인 노드를 가리키던 링크를 해제 */
		if(prev->left == delnode) prev->left = NULL;
		else prev->right = NULL;
	}
	// 2.삭제할 노드의 자식 노드가 하나 있다면
	else if(delnode->left == NULL || delnode->right == NULL){
		if(prev->left == delnode){ // 삭제 대상인 노드가 부모노드의 왼쪽 자식노드
			if(delnode->left != NULL) prev->left = delnode->left; // 삭제 대상 노드의 자식 노드가 왼쪽
			else prev->left = delnode->right; // 삭제 대상 노드의 자식 노드가 오른쪽
		}
		else{ // 삭제 대상인 노드가 부모노드의 오른쪽 자식노드
			if(delnode->left != NULL) prev->right = delnode->left; // 삭제 대상 노드의 자식 노드가 왼쪽
			else prev->right = delnode->right; // 삭제 대상 노드의 자식 노드가 오른쪽
		}
	}
	// 3. 삭제할 노드의 자식 노드가 2개라면
	else{
		/* 오른쪽 서브트리에서 가장 작은 노드 찾기 */
		Node* stree = delnode->right;
		Node* pstree = delnode;
		while(stree->left != NULL){
			pstree = stree;
			stree = stree->left;
		}
		// 오른쪽 서브트리에서 가장 작은 노드의 자식노드 연결
		if(pstree == delnode)
			pstree->right = stree->right;
		else pstree->left = stree->right;
		// 삭제 대상 노드 자리에 왼쪽 서브트리에서 찾은 노드 삽입
		stree->left = delnode->left;
		stree->right = delnode->right;
		if(prev->left == delnode) prev->left = stree;
		else prev->right = stree;
	}
	free(delnode);
	return 0;
}


void freeNode(Node* ptr)
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



Node* pop()
{
	if(top == -1) return NULL; // 스택이 공백이면 NULL 리턴
	else return stack[top--]; // 공백이 아니면 탑에 원소 리턴, 탑 -1
}

void push(Node* aNode)
{
	stack[++top] = aNode; // 탑 +1, 스택에 노드 포인터 삽입
}



Node* deQueue()
{
	if(front == rear) return NULL; // 큐가 공백이면 NULL 리턴
	else return queue[front++];
}

void enQueue(Node* aNode)
{
	queue[++rear] = aNode;
}





