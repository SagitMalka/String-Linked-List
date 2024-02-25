#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

int main() {
    int flag = 1;
    int flagfree = 0;
    int fun = 0;
    int num = 0;
    int index = 0;
    int res = 0;
    char* word = NULL;
    StrList* list = StrList_alloc(); // Use StrList_create() for allocation
    while (flag) {
        scanf(" %d", &fun);

        switch (fun) {
            case 0:
                flag = 0;
                break;
            case 1:
                scanf(" %d", &num);
                for (int i = 0; i < num; i++) {
                    word = (char*)malloc(100 * sizeof(char)); // Allocate memory for word
                    scanf(" %s", word);
                    StrList_insertLast(list, word);
                }
                break;
            case 2:
                scanf(" %d", &index);
                word = (char*)malloc(100 * sizeof(char)); // Allocate memory for word
                scanf("%s", word);
                StrList_insertAt(list, word, index);
                break;
            case 3:
                if (flagfree == 1) {
                    printf("\n");
                    break;
                }
                StrList_print(list);
                break;
            case 4:
                res = StrList_size(list);
                printf("%d\n", res);
                break;
            case 5:
                scanf(" %d", &index);
                StrList_printAt(list, index);
                break;
            case 6:
                res = StrList_printLen(list);
                printf("%d\n", res);
                break;
            case 7:
                word = (char*)malloc(100 * sizeof(char)); // Allocate memory for word
                scanf(" %s", word);
                res = StrList_count(list, word);
                printf("%d\n", res);
                free(word); // Free allocated memory for word
                break;
            case 8:
                word = (char*)malloc(100 * sizeof(char)); // Allocate memory for word
                scanf(" %s", word);
                StrList_remove(list, word);
                free(word); // Free allocated memory for word
                break;
            case 9:
                scanf(" %d", &index);
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                flagfree = 1;
                StrList_free(list); // Free memory using StrList_free
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                res = StrList_isSorted(list);
                if (res == 1) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            default:
                break;
        }
    }
    StrList_free(list);
    return 0;
}
