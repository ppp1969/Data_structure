/*
참고한 부분: 

	* 유튜브 부경대IT융합응용공학과 권오흠 교수님 강의 -> https://www.youtube.com/watch?v=98g_cnvbyqA
	* https://ict-nroo.tistory.com/73 , https://ict-nroo.tistory.com/71?category=698685
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 1
#define RED 0

struct node{
	int key;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *gp(struct node *n);	//노드 관계 함수.

void RB_insert(struct node *z);		//추가관련 함수.
void RB_insert_fixup(struct node *z);

struct node *RB_delete(struct node *z);		//삭제 관련 함수.
void RB_delete_fixup(struct node *x);

struct node *tree_succesor(struct node *x);		//이진 트리 구현 함수.
struct node *tree_search(int key);
void create_node(int key);
void tree_print(struct node *x);		

void left_rotate(struct node *x);	//회전관련 함수.
void right_rotate(struct node *x);

struct node *ROOT;
struct node *NILL;

int main(void){
	NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;
	NILL->left = NULL;
	NILL->right = NULL;
	ROOT = NILL;

	char command[15];
	int data;
	printf("------------RED BLACK TREE------------\n\n");
	printf("사용할 수 있는 명령은 총 3가지 입니다.\n\n");
	printf("출력은 정렬된 값으로 출력됩니다. \n\n");
	printf("* : insert (key) \n* : delete (key)\n* : print\n");
	for(;;){
		gets(command);
		if(strstr(command,"insert")){
			sscanf(command,"insert %d",&data);	
			if(!tree_search(data)){
				create_node(data);
			}
			else{
				printf("오류 : key값이 중복됩니다. 재입력하십시오.\n");
				continue;
			}
		}
		else if(strstr(command,"delete")){
			sscanf(command,"delete %d",&data);	
			if(tree_search(data)){
				RB_delete(tree_search(data));
			}
			else{
				printf("오류 : key값이 트리에 존재하지 않습니다. 재입력하십시오.\n");
				continue;
			}
		}
		else{
			tree_print(ROOT);
			printf("\n");
		}
	}

	return 0;
}

struct node *gp(struct node *n){
    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;
}

void create_node(int key){
	struct node *z;
	z = malloc(sizeof(struct node));

	z->key = key;

	RB_insert(z);
}

/*RB트리의 추가(insert함수)와 삭제(delete함수)는 모두 이진트리의 추가, 삭제 구현과 유사하다. 이는 RB트리도 이진트리의 특성을 유지하고 있기 때문이다.
RB트리의 특징인 color(RED, BLACK)을 이용한 트리의 균형유지는 모두 fixup함수에 의해 구현된다. fixup함수는 case별로 실행하며, 각 case마다 실행횟수가 달라진다.
최악의 경우에도 RB트리이므로 log(N)의 실행시간이 보장된다. case마다 자세한 설명은 추후 회지에 같이 올릴 예정. 
*/

void RB_insert(struct node *z){
	struct node *x, *y;

	x = ROOT;
	y = NILL;

	while(x != NILL){
		y = x;
		if(z->key <= x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == NILL){
		ROOT = z;
	}
	else if(z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}
	z->left = NILL;
	z->right = NILL;
	z->color = RED;

	RB_insert_fixup(z);
}

void RB_insert_fixup(struct node *z){
	while(z->parent->color == RED){

		if(z->parent == gp(z)->left){

			if(gp(z)->right != NULL && gp(z)->right->color == RED){
				z->parent->color = BLACK;
				gp(z)->right->color = BLACK;
				gp(z)->color = RED;
				z = gp(z);
			}

			else{

				if(z == z->parent->right){
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				gp(z)->color = RED;
				right_rotate(gp(z));
			}
		}

		else{
			
			if(gp(z)->left != NULL && gp(z)->left->color == RED){
				z->parent->color = BLACK;
				gp(z)->left->color = BLACK;
				gp(z)->color = RED;
				z = gp(z);
			}

			else{

				if(z == z->parent->left){
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				gp(z)->color = RED;
				left_rotate(gp(z));
			}
		}
	}

	ROOT->color = BLACK;
}

void left_rotate(struct node *x){
	struct node *y;
	
	y = x->right;
	x->right = y->left;

	if(y->left != NILL){
		y->left->parent = x;
	}

	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void right_rotate(struct node *x){
	struct node *y;

	y = x->left;
	x->left = y->right;

	if(y->right != NILL){
		y->right->parent = x;
	}

	y->parent = x->parent;

	if(y->parent == NILL){
		ROOT = y;
	}

	else if(x == x->parent->left){
		x->parent->left = y;	
	}

	else{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

struct node *tree_search(int key){
	struct node *x;
	x = ROOT;

	while(x != NILL && x->key != key){

		if(key < x->key){
			x = x->left;
		}

		else{
			x = x->right;
		}
	}
	if(x==NILL){
		return 0;
	}
	return x;
}

void tree_print(struct node *x){
	if(x != NILL){
		tree_print(x->left);
		printf("%d   ", x->key);
		tree_print(x->right);
	}
}

struct node *tree_succesor(struct node *x)
{
	struct node *y;
	y = x->parent;

    if(x->right!=NILL){

		while(y->left==NILL){
			y = y->left;
		}

		return y;
	}

	while((y!=NULL)&&(x==y->right)){
		x = y;
		y = y->parent;
	}

	return y;
}
struct node *RB_delete(struct node *z){
	struct node *x, *y;

	if((z->left==NILL)||(z->right==NILL)){
		y = z;
	}

	else{
		y = tree_succesor(z);
	}

	if(y->left != NILL){
		x = y->left;
	}

	else{
		x = y->right;
	}

	x->parent = y->parent;

	if(y->parent == NILL){
		ROOT = x;
	}

	else if(y == y->parent->left){
		y->parent->left = x;
	}

	else{
		y->parent->right = x;
	}

	if(y != z){
		z->key = y->key;
	}

	if(y->color == BLACK){
		RB_delete_fixup(x);
	}

	return y;
}
void RB_delete_fixup(struct node *x){
	struct node *w;	

	while(x != ROOT && x->color == BLACK){

		if(x == x->parent->left){
			w = x->parent->right;

			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}

			if(w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			}
			else if(w->right->color == BLACK){
					w->color = RED;
					w->left->color = BLACK;
					right_rotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(x->parent);
				x = ROOT;		
			}
		else{
			w = x->parent->left;

			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent);
				w = x->parent->left;
			}

			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x = x->parent;
			}

			else if(w->left->color == BLACK){
					w->color = RED;
					w->right->color = BLACK;
					left_rotate(w);
					w = x->parent->left;
				}

			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->left->color = BLACK;
			right_rotate(x->parent);
			x = ROOT;
		}
	}
	x->color = BLACK;
}
