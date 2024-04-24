#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100

typedef struct Book {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    struct Book* next;
} Book;

void initializeBookListFromFile();

void saveBooksToFile();

void sortBooksByTitle();

void createBook();

void listBooks();

void removeBook();

void updateBook();

#endif