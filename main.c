#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "book.h"

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

int main()
{
    while (1)
    {
        printf("1. Login\n2. Registrar\n3. Sair\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            getchar();
            system(CLEAR_SCREEN);
            User *user = login();

            if (user != NULL)
            {
                initializeBookListFromFile();

                while (1)
                {
                    system(CLEAR_SCREEN);
                    printf("Bem-vindo ao Libsystem!\n\n");
                    printf("1. Cadastrar livro\n2. Listar livros\n3. Remover livro\n4. Atualizar livro\n5. Sair\n");
                    int bookChoice;
                    scanf("%d", &bookChoice);
                    switch (bookChoice)
                    {
                    case 1:
                        system(CLEAR_SCREEN);
                        createBook();
                        break;
                    case 2:
                        system(CLEAR_SCREEN);
                        listBooks();
                        break;
                    case 3:
                        system(CLEAR_SCREEN);
                        removeBook();
                        break;
                    case 4:
                        system(CLEAR_SCREEN);
                        updateBook();
                        break;
                    case 5:
                        return 0;
                    }
                }
            }
            else
            {
                printf("Falha na autenticação!\n\n");
            }
            break;
        }
        case 2:
        {
            system(CLEAR_SCREEN);
            char email[MAX_EMAIL_LENGTH];
            char password[MAX_PASSWORD_LENGTH];
            printf("Digite o email: ");
            scanf("%s", email);
            printf("Digite a senha: ");
            scanf("%s", password);
            createUser(email, password);
            system(CLEAR_SCREEN);
            break;
        }
        case 3:
            return 0;
        }
    }
}