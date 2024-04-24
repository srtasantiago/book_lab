#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

int emailExists(const char *email) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char existingEmail[81];
    char password[81];
    while (fscanf(file, "%80s %80s", existingEmail, password) != EOF) {
        if (strcmp(email, existingEmail) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void createUser(const char *email, const char *password)
{
    if (strchr(email, '@') == NULL) {
        printf("Erro: O email deve conter um '@'.\n\n");
        return;
    }

    if (strlen(email) > 80) {
        printf("Erro: O email deve ter no máximo 80 caracteres.\n\n");
        return;
    }

    if (emailExists(email)) {
        printf("Erro: O email já está cadastrado.\n\n");
        return;
    }

    FILE *file = fopen("users.txt", "a");
    fprintf(file, "%s %s\n", email, password);
    fclose(file);
}

User *findUser(const char *email)
{
    FILE *file = fopen("users.txt", "r");
    User *user = malloc(sizeof(User));
    while (fscanf(file, "%s %s", user->email, user->password) != EOF)
    {
        if (strcmp(user->email, email) == 0)
        {
            fclose(file);
            return user;
        }
    }
    fclose(file);
    free(user);
    return NULL;
}

User *login()
{
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Digite o email: ");
    scanf("%s", email);
    printf("Digite a senha: ");
    scanf("%s", password);
    User *user = findUser(email);

    if (strcmp(user->password, password) == 0)
    {

        return user;
    }
}