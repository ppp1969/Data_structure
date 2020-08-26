/*
������ �κ�: 

	* ��Ʃ�� �ΰ��IT����������а� �ǿ��� ������ ���� -> https://www.youtube.com/watch?v=98g_cnvbyqA
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

struct node *gp(struct node *n);	//��� ���� �Լ�.

void RB_insert(struct node *z);		//�߰����� �Լ�.
void RB_insert_fixup(struct node *z);

struct node *RB_delete(struct node *z);		//���� ���� �Լ�.
void RB_delete_fixup(struct node *x);

struct node *tree_succesor(struct node *x);		//���� Ʈ�� ���� �Լ�.
struct node *tree_search(int key);
void create_node(int key);
void tree_print(struct node *x);		

void left_rotate(struct node *x);	//ȸ������ �Լ�.
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
	printf("����� �� �ִ� ����� �� 3���� �Դϴ�.\n\n");
	printf("����� ���ĵ� ������ ��µ˴ϴ�. \n\n");
	printf("* : insert (key) \n* : delete (key)\n* : print\n");
	for(;;){
		gets(command);
		if(strstr(command,"insert")){
			sscanf(command,"insert %d",&data);	
			if(!tree_search(data)){
				create_node(data);
			}
			else{
				printf("���� : key���� �ߺ��˴ϴ�. ���Է��Ͻʽÿ�.\n");
				continue;
			}
		}
		else if(strstr(command,"delete")){
			sscanf(command,"delete %d",&data);	
			if(tree_search(data)){
				RB_delete(tree_search(data));
			}
			else{
				printf("���� : key���� Ʈ���� �������� �ʽ��ϴ�. ���Է��Ͻʽÿ�.\n");
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

/*RBƮ���� �߰�(insert�Լ�)�� ����(delete�Լ�)�� ��� ����Ʈ���� �߰�, ���� ������ �����ϴ�. �̴� RBƮ���� ����Ʈ���� Ư���� �����ϰ� �ֱ� �����̴�.
RBƮ���� Ư¡�� color(RED, BLACK)�� �̿��� Ʈ���� ���������� ��� fixup�Լ��� ���� �����ȴ�. fixup�Լ��� case���� �����ϸ�, �� case���� ����Ƚ���� �޶�����.
�־��� ��쿡�� RBƮ���̹Ƿ� log(N)�� ����ð��� ����ȴ�. case���� �ڼ��� ������ ���� ȸ���� ���� �ø� ����. 
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
