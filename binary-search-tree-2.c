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

int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [?ѹο?] [2018038047] -----]\n");
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
		for( ; node; node = node->left){ // ???? ?ڽĵ??? ???? ?̵?
			push(node); // ???ÿ? ????
		}
		node = pop(); // ???ÿ??? ????
		if(!node) break; // ?????? ?????̸? ????
		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = -1;
	rear = -1;
	if(!ptr) return; /* ????Ʈ???? ???? */
	enQueue(ptr);
	while(1){
		ptr = deQueue(); // ť?? ?????? ???? ?޾ƿ?
		if(ptr){ // ť?? ?????? ?ƴϸ?
			printf(" [%d] ", ptr->key);
			// ?ڽĳ??? ť?? ????
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
	Node* delnode = head->left; // ?????? ????
	Node* prev = head; // ?????? ?????? ?θ?????

	while(delnode != NULL && delnode->key != key){ // ?????? ???? Ž??
		prev = delnode;
		if(delnode->key > key) delnode = delnode->left;
		else delnode = delnode->right;
	}

	/* ???ϴ? ???尡 ???ٸ? delnode == NULL */
	if(!delnode){
		printf("Cannot find the node [%d]\n",key);
		return 0;
	}
	// 1.?????? ???尡 ????????????
	if(delnode->left == NULL && delnode->right == NULL){
		/* ???? ?????? ???带 ????Ű?? ??ũ?? ???? */
		if(prev->left == delnode) prev->left = NULL;
		else prev->right = NULL;
	}
	// 2.?????? ?????? ?ڽ? ???尡 ?ϳ? ?ִٸ?
	else if(delnode->left == NULL || delnode->right == NULL){
		if(prev->left == delnode){ // ???? ?????? ???尡 ?θ??????? ???? ?ڽĳ???
			if(delnode->left != NULL) prev->left = delnode->left; // ???? ???? ?????? ?ڽ? ???尡 ????
			else prev->left = delnode->right; // ???? ???? ?????? ?ڽ? ???尡 ??????
		}
		else{ // ???? ?????? ???尡 ?θ??????? ?????? ?ڽĳ???
			if(delnode->left != NULL) prev->right = delnode->left; // ???? ???? ?????? ?ڽ? ???尡 ????
			else prev->right = delnode->right; // ???? ???? ?????? ?ڽ? ???尡 ??????
		}
	}
	// 3. ?????? ?????? ?ڽ? ???尡 2??????
	else{
		/* ?????? ????Ʈ?????? ???? ???? ???? ã?? */
		Node* stree = delnode->right;
		Node* pstree = delnode;
		while(stree->left != NULL){
			pstree = stree;
			stree = stree->left;
		}
		// ?????? ????Ʈ?????? ???? ???? ?????? ?ڽĳ??? ????
		if(pstree == delnode) // ???? ?????? ?ٷ? ?????? ?ڽĳ??尡 ???? ???? ????????
			pstree->right = stree->right;
		else pstree->left = stree->right;
		// ???? ???? ???? ?ڸ??? ?????? ????Ʈ?????? ã?? ???? ????
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
	if(top == -1) return NULL; // ?????? ?????̸? NULL ????
	else return stack[top--]; // ?????? ?ƴϸ? ž?? ???? ????, ž -1
}

void push(Node* aNode)
{
	stack[++top] = aNode; // ž +1, ???ÿ? ???? ?????? ????
}


Node* deQueue()
{
	if(front == rear) return NULL; // ť?? ?????̸? NULL ????
	else{
		front = (front + 1) % MAX_QUEUE_SIZE; // front?? ?????? ?? ĭ ?̵???Ų??
		return queue[front]; // front?? ???? ????
	}
}

void enQueue(Node* aNode)
{
	rear = (rear +1) % MAX_QUEUE_SIZE; // rear?? ?????? ?? ĭ ?̵???Ų??
	queue[rear] = aNode; // rear?ڸ??? ???? ????
}