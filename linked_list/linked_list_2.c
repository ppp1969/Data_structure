#include <stdio.h>
#include <stdlib.h>    // linked list에서 추가, 삭제 함수 구현해보기.

typedef struct NODE {     //typedef 으로 이후 struct를 생략.
    struct NODE *next;    // 다음 노드의 주소를 저장할 포인터
    int data;             
} node;	//NODE말고 node로 별칭정함.

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
                             

    node *curr = head->next;    // 연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장
    while (curr != NULL)               // 포인터가 NULL이 아닐 때 계속 반복
    {
        printf("%d\n", curr->data);    // 현재 노드의 데이터 출력
        curr = curr->next;             // 포인터에 다음 노드의 주소 저장
    }


    return 0;
}
//head node 뒤에 값을 계속 추가하는 것이기에 넣은 순서가 늦을수록 앞에 출력.
void addNode(node* head, int data){ 
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	newNode->next = head->next;
	head->next = newNode;
	printf("값 : %d 추가\n",data);
}
//head node 뒤의 값을 삭제함.

//삭제의 핵심은 머리노드의 다음 주소를 삭제 및 변경하고
//free로 노드의 메모리 영역을 해제함. 
void deleteNode(node* head){
	node* targetNode = head->next;
	head->next = targetNode->next;
	free(targetNode);
	printf("Head노드 뒤의 값 삭제\n");
}
