/**
*      author  : Yash Shukla
*      created : 2020-09-10 15:20:35
**/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define forn(n) for (int i = 0; i < n; i++)
#define forkn(i, k, n) for (int i = k; i < n; i++)
#define forin(n) for (int i = n - 1; i >= 0; i--)
#define input(x) scanf("%d", &x);
#define ScanArr(arr) forn(sizeof(arr) / sizeof(arr[0])) input(arr[i]);
#define print(x) printf("%d ", x);
#define PrintArr(arr) forn(sizeof(arr) / sizeof(arr[0])) print(arr[i]);
#define endline printf("\n");
#define SIZE 100

typedef struct Trie {
    struct Trie* alp_row[26];
    int word_end;
} Trie;

void Insert(Trie* root, char str[], int len) {
    int j = 0;
    Trie* ptr = root;
    while (1) {
        int i = str[j] - 'a';
        if (ptr->alp_row[i] == NULL) {
            break;
        }
        if (j == len) {
            break;
        }
        ptr = ptr->alp_row[i];
        j++;
    }
    if (j != len) {
        while (j < len) {
            int i = str[j++] - 'a';
            ptr->alp_row[i] = Insert_New_Row();
            ptr = ptr->alp_row[i];
        }
    }
    ptr->word_end = 1;
}

Trie* Insert_New_Row() {
    Trie* obj = (Trie*)malloc(sizeof(Trie));
    for (int i = 0; i < 26; i++) {
        obj->alp_row[i] = NULL;
    }
    return obj;
}

void Print_Trie(Trie* ptr, char Main_String[], int pos) {
    char Print_Trie[SIZE];
    strcpy(Print_Trie, Main_String);
    for (int i = 0; i < 26; i++) {
        if (ptr->alp_row[i] != NULL) {
            Print_Trie[pos] = i + 'a';
            Print_Trie(ptr->alp_row[i], Print_Trie, pos + 1);
        }
    }
    if (ptr->word_end) {
        Print_Trie[pos] = '\0';
        printf("%s \n", Print_Trie);
    }
}

int Search_Trie(Trie* ptr, char str[], int len) {
    for (int i = 0; i < len; i++) {
        if (ptr->alp_row[str[i] - 'a'] == NULL) {
            return 0;
        }
        ptr = ptr->alp_row[str[i] - 'a'];
    }
    if (ptr->word_end) {
        return 1;
    }
    return 0;
}

void Delete_Trie(Trie* ptr, char* str, int len) {
    if (!Search_Trie(ptr, str, len)) {
        printf("Input a valid Word!\n");
        return;
    }
    Trie* ar[len];
    for (int i = 0; i < len; i++) {
        ar[i] = ptr;
        ptr = ptr->alp_row[str[i] - 'a'];
    }
    ptr->word_end = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (ar[i]->word_end) {
            return;
        }
        for (int i = 0; i < 26; i++) {
            if (i != str[i] - 'a' && ar[i] != NULL) {
                return;
            }
        }
        Trie* tmp = ar[i];
        ar[i] = NULL;
        free(tmp);
    }
}

int main() {
    Trie* root = Insert_New_Row();
    root->word_end = 1;
    printf("Yash\n");
    printf("Input number of Words to Insert :: ");
    int N;
    input(N);

    printf("Input The Words :: \n");

    char ch = getchar();

    for (int i = 0; i < N; i++) {
        char str[SIZE] = "";
        scanf("%s", str);
        Insert(root, str, strlen(str));
    }

    char String[SIZE] = "";
    printf("Printing all the Words in Trie after Insertion\n");
    Print_Trie(root, String, 0);

    printf("Input the number of Words to Search :: ");
    input(N);

    printf("Input the Word :: ");

    for (int i = 0; i < N; i++) {
        char temp[SIZE] = "";
        scanf(" %s", temp);

        if (Search_Trie(root, temp, strlen(temp)))
            printf("%s Word exists in Trie!\n", temp);
        else
            printf("Word does not exist in Trie!!\n");
    }

    printf("Input the number of Words to Delete :: ");
    input(N);

    printf("Input the Words :: ");

    for (int i = 0; i < N; i++) {
        char temp[SIZE] = "";
        scanf(" %s", temp);
        Delete_Trie(root, temp, strlen(temp));
    }

    printf("Printing all the Words in Trie after Deletions\n\n");
    Print_Trie(root, String, 0);

    return 0;
}