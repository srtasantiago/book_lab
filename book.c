#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"

Book* head = NULL;

void initializeBookListFromFile() {
    FILE* file = fopen("./book_data.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    while (fscanf(file, "%[^;];%[^\n]\n", title, author) != EOF) {
        Book* newBook = (Book*)malloc(sizeof(Book));
        strcpy(newBook->title, title);
        strcpy(newBook->author, author);
        newBook->next = NULL;
        if (head == NULL) {
            head = newBook;
        } else {
            Book* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newBook;
        }
    }
    fclose(file);
    printf("Lista de livros inicializada com sucesso a partir do arquivo.\n");
}

void saveBooksToFile() {
    FILE* file = fopen("./book_data.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Book* current = head;
    while (current != NULL) {
        fprintf(file, "%s;%s\n", current->title, current->author);
        current = current->next;
    }

    fclose(file);
    printf("Lista de livros salva com sucesso no arquivo.\n");
}

void sortBooksByTitle() {
    if (head == NULL) {
        printf("Não há livros cadastrados.\n");
        return;
    }
    int swapped;
    Book* current;
    Book* last = NULL;
    do {
        swapped = 0;
        current = head;
        while (current->next != last) {
            if (strcmp(current->title, current->next->title) > 0) {
                Book* temp = current->next;
                current->next = temp->next;
                temp->next = current;
                if (current == head) {
                    head = temp;
                } else {
                    Book* previous = head;
                    while (previous->next != current) {
                        previous = previous->next;
                    }
                    previous->next = temp;
                }
                current = temp;
                swapped = 1;
            } else {
                current = current->next;
            }
        }
        last = current;
    } while (swapped);
    printf("Livros ordenados por título.\n");
}

void createBook() {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];

    getchar();
    printf("Digite o título do livro: ");
    fscanf(stdin, "%[^\n]", title);
    getchar();

    printf("Digite o autor do livro: ");
    fscanf(stdin, "%[^\n]", author);
    getchar();

    Book* newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->next = NULL;

    if (head == NULL) {
        head = newBook;
    } else {
        Book* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBook;
    }

    sortBooksByTitle();
    saveBooksToFile();
}

void listBooks() {
    if (head == NULL) {
        printf("Não há livros cadastrados.\n");
        return;
    }

    Book* current = head;
    while (current != NULL) {
        printf("Título: %s, Autor: %s\n", current->title, current->author);
        current = current->next;
    }

    getchar();
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}

void removeBook() {

    if (head == NULL) {
        printf("Não há livros cadastrados.\n");
        return;
    }

    char titleToRemove[MAX_TITLE_LENGTH];
    char authorToRemove[MAX_AUTHOR_LENGTH];

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    printf("Digite o título do livro a ser removido: ");
    fscanf(stdin, "%[^\n]", titleToRemove);
    getchar();

    printf("Digite o autor do livro a ser removido: ");
    fscanf(stdin, "%[^\n]", authorToRemove);
    getchar();

    Book* current = head;
    Book* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->title, titleToRemove) == 0 && strcmp(current->author, authorToRemove) == 0) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);

            saveBooksToFile();
            printf("Livro removido com sucesso.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Livro não encontrado.\n");
}

void updateBook() {
    if (head == NULL) {
        printf("Não há livros cadastrados.\n");
        return;
    }

    char titleToUpdate[MAX_TITLE_LENGTH];
    char authorToUpdate[MAX_AUTHOR_LENGTH];

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    printf("Digite o título do livro a ser atualizado: ");
    fscanf(stdin, "%[^\n]", titleToUpdate);
    getchar();

    printf("Digite o autor do livro a ser atualizado: ");
    fscanf(stdin, "%[^\n]", authorToUpdate);
    getchar();

    char newTitle[MAX_TITLE_LENGTH];
    char newAuthor[MAX_AUTHOR_LENGTH];

    printf("Digite o novo título do livro: ");
    fscanf(stdin, "%[^\n]", newTitle);
    getchar();

    printf("Digite o novo autor do livro: ");
    fscanf(stdin, "%[^\n]", newAuthor);
    getchar();

    Book* current = head;

    while (current != NULL) {

        if (strcmp(current->title, titleToUpdate) == 0 && strcmp(current->author, authorToUpdate) == 0) {
            strcpy(current->title, newTitle);
            strcpy(current->author, newAuthor);
            sortBooksByTitle();
            saveBooksToFile();
            printf("Livro atualizado com sucesso.\n");
            return;
        }
        current = current->next;
    }

    printf("Livro não encontrado.\n");
}