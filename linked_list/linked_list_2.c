#include <stdio.h>
#include <stdlib.h>    // linked list���� �߰�, ���� �Լ� �����غ���.

typedef struct NODE {     //typedef ���� ���� struct�� ����.
    struct NODE *next;    // ���� ����� �ּҸ� ������ ������
    int data;             
} node;	//NODE���� node�� ��Ī����.

void addNode(node*, int);
void deleteNode(node*);

int main()
{
    node* head = (node*)malloc(sizeof(node));    
	head->next = NULL;

	addNode(head,10);
	addNode(head,20);
	addNode(head,30);

	deleteNode(head);
                             

    node *curr = head->next;    // ���� ����Ʈ ��ȸ�� �����Ϳ� ù ��° ����� �ּ� ����
    while (curr != NULL)               // �����Ͱ� NULL�� �ƴ� �� ��� �ݺ�
    {
        printf("%d\n", curr->data);    // ���� ����� ������ ���
        curr = curr->next;             // �����Ϳ� ���� ����� �ּ� ����
    }


    return 0;
}
//head node �ڿ� ���� ��� �߰��ϴ� ���̱⿡ ���� ������ �������� �տ� ���.
void addNode(node* head, int data){ 
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	newNode->next = head->next;
	head->next = newNode;
	printf("�� : %d �߰�\n",data);
}
//head node ���� ���� ������.

//������ �ٽ��� �Ӹ������ ���� �ּҸ� ���� �� �����ϰ�
//free�� ����� �޸� ������ ������. 
void deleteNode(node* head){
	node* targetNode = head->next;
	head->next = targetNode->next;
	free(targetNode);
	printf("Head��� ���� �� ����\n");
}
