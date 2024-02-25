#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StrList.h"


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
        Node *newNode = Node_alloc(data, NULL);
        if (newNode) {
            if (!StrList->_head) {
                StrList->_head = newNode;
            } else {
                Node *current = StrList->_head;
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }

            (StrList->_size)++;
        }
        free(newNode);
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
        }
    }  StrList->_size++;
}

char* StrList_firstData(const StrList* StrList){
    char *firstdata = (char*)StrList->_head->word;
    return firstdata;
}
void StrList_print(const StrList* StrList) {
    if (StrList) {
        Node *current = StrList->_head;
        printf("%s", current->word);
        current = current->next;
        while (current) {
            printf(" %s", current->word);
            current = current->next;
        }
        printf("\n");
    }
}
void StrList_printAt(const StrList* Strlist,int index){
    if (Strlist && index >= 0 && index < Strlist->_size) {
        Node *current = Strlist->_head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        printf("%s\n",current->word);
    } else {
        return;
    }
}
int StrList_printLen(const StrList* Strlist){
    int count = 0;
    if (Strlist) {
        Node *current = Strlist->_head;
        while (current) {
            count = count + strlen(current->word);
            current = current->next;
        }
    }
    return count;
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
    char *data_to_find = (char *)data;
    if(StrList){
        Node *current = StrList->_head;
        Node *prev = NULL;
        while (current != NULL){
            if(strcmp(current->word, data_to_find) == 0){
                if(prev == NULL){
                    StrList->_head = current->next;
                    free((char *)current->word);
                    free(current);
                    current = StrList->_head;
                }else{
                    prev->next = current->next;
                    free((void*)current->word);
                    free(current);
                    current = prev->next;
                }
            StrList->_size--;    
            }else{
                prev = current;
                current = current->next;
            }
        }
    }
}

void StrList_removeAt(StrList* StrList, int index){
    if (StrList && index >= 0 && index < StrList->_size) {
        Node *current = StrList->_head;
        Node *prev = NULL;
        if (index == 0) {
            StrList->_head = StrList->_head->next;
            current->next = NULL;
            free(current);
        }
        else{
            for (int i = 0; i < index; i++){
                prev = current;
                current = current->next;
            }
            prev->next = current->next;
            free((void*)current->word);
            free(current);
            current = prev->next;
        }
        StrList->_size--;   
    }    
}
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1->_size != StrList2->_size){
        return 0;
    }else{
        Node *curr1 = StrList1->_head;
        Node *curr2 = StrList2->_head;
        while (curr1 && curr2){
            char *data1 = (char*)curr1->word;
            char *data2 = (char*)curr2->word;
            if(strcmp(data1, data2) != 0){
                return 0;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    free(curr1);
    free(curr2);    
    }
    return 1;
}

StrList* StrList_clone(const StrList* Strlist){
    if(Strlist == NULL){
        return NULL;
    }
    StrList* newlist = StrList_alloc();
    if(newlist == NULL){
        return NULL;
    }
    const Node* current = Strlist->_head;
    Node** copy = &(newlist->_head);
    newlist->_size = Strlist->_size;

    while (current){
        *copy = Node_alloc(current->word, NULL);
        current = current->next;
        copy = &((*copy)->next);
    }
    free((void*)current);
    return newlist;
}
void StrList_reverse( StrList* StrList){
    Node* prev = NULL;
    Node* curr = StrList->_head;
    Node* next = NULL;

    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    StrList->_head = prev;
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->_head == NULL || StrList->_head->next == NULL) {
        return;
    }

    Node* current = StrList->_head;
    while (current != NULL) {
        Node* nextNode = current->next;
        while (nextNode != NULL) {
            if (strcmp(current->word, nextNode->word) > 0) {
                char* temp = (char*)current->word;
                current->word = nextNode->word;
                nextNode->word = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}
int StrList_isSorted(StrList* StrList){
    if (StrList == NULL || StrList->_head == NULL || StrList->_head->next == NULL) {
        return 1;
    }
    else{
        Node* current = StrList->_head;
        while (current != NULL) {
            Node* nextNode = current->next;
            while (nextNode != NULL) {
                if (strcmp(current->word, nextNode->word) > 0) {
                    return 0;
                }
                nextNode = nextNode->next;
            }
            current = current->next;
        }
    return 1;
    }
}
