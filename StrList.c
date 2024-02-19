#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "StrList.h"


struct _node{
    const char *word;
    struct _node *next; 
};
typedef struct _node Node;

struct _StrList{
    Node *_head;
    size_t _size;
};
typedef struct _StrList StrList;

Node* Node_alloc(const char *word, Node* next){
    Node *p = (Node*)malloc(sizeof(Node));
    if(p){
        p->word = word;
        p->next = next;
    }
    return p;
}
void Node_free(Node* node){
    free(node);
}

StrList* StrList_alloc(){
    StrList *p = (StrList*)malloc(sizeof(StrList));
    p->_head = NULL;
    p->_size = 0;
    return p;
}

void StrList_free(StrList* StrList){
    if (StrList==NULL) return;
	Node* p1= StrList->_head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->next;
		Node_free(p2);
	}
	free(StrList);
}

size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}

void StrList_insertLast(StrList* StrList, const char* data){
    if (StrList) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        if (newNode) {
            newNode->word = strdup(data); // Duplicate the string to store in the list
            newNode->next = NULL;

            if (!StrList->_head) {
                StrList->_head = newNode;
            } else {
                Node *current = StrList->_head;
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }

            StrList->_size++;
        }
    }
}

void StrList_insertAt(StrList* StrList, const char* data, int index){
    if(StrList && index >= 0 && index <= StrList->_size){
        Node *new_node = Node_alloc(data, NULL);

        if(index == 0){
            new_node->next = StrList->_head;
            StrList->_head = new_node;
        }else{
            Node *current = StrList->_head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
            // Node_free(current);
        }
    }  StrList->_size++;
}

char* StrList_firstData(const StrList* StrList){
    char *firstdata = (char*)StrList->_head->word;
    return firstdata;
}
void StrList_print(const StrList* StrList) {
    if (StrList) {
        printf("StrList Contents:\n");
        Node *current = StrList->_head;
        while (current) {
            printf("%s\n", current->word);
            current = current->next;
        }
    }
}
void StrList_printAt(const StrList* Strlist,int index){
    if (Strlist && index >= 0 && index < Strlist->_size) {
        Node *current = Strlist->_head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        printf("String at index %d: %s\n", index, current->word);
    } else {
        printf("Invalid index.\n");
    }
}
int StrList_count(StrList* StrList, const char* data){
    int count = 0;
    if(StrList){
        Node *current = StrList->_head;
        while (current){
            if(strcmp(current->word, data) == 0){
            count++;
            }
            current = current->next;
        }
    }
    return count;
}
void StrList_remove(StrList* StrList, const char* data){
    if(StrList){
        Node *current = StrList->_head;
        while (current){
            if(strcmp(current->word, data) == 0){
                Node *tmp = current;
                
            }
            current = current->next;
        }
    }
}

int main() {
    StrList *list = StrList_alloc();
    StrList_insertLast(list, "Hello");
    StrList_insertLast(list, "World");
    StrList_insertLast(list, "!");
    StrList_insertAt(list, "sababa", 1);
    char *firstdata = StrList_firstData(list);
    StrList_insertLast(list, "?");
    StrList_print(list);
    StrList_printAt(list, 1);
    int res = StrList_count(list, "Hello");
    printf("StrList_count= %d\n", res);
    StrList_free(list);
    return 0;
}