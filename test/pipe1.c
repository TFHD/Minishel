#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

void split_commands(char *input, char ***commands, int *num_commands)
{
    char *token;

    token = strtok(input, "|");
    *num_commands = 0;

    // Allocation dynamique de mémoire pour les commandes
    *commands = malloc(MAX_ARGS * sizeof(char *));
    if (*commands == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Séparer la chaîne par "|"
    while (token != NULL)
    {
        (*commands)[*num_commands] = strdup(token);
        if ((*commands)[*num_commands] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        (*num_commands)++;
        token = strtok(NULL, "|");
    }
}

// Fonction pour découper une commande en arguments
int parse_command(char *cmd, char **args)
{
    char *token;
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Terminaison du tableau d'arguments
    return i;
}

int main(void)
{
    char input[MAX_CMD_LEN];
    char **commands = NULL;
    int num_commands = 0;
    int pipefds[2 * (MAX_ARGS - 1)];

    // Demander à l'utilisateur d'entrer une commande
    printf("Entrez une commande (par exemple : 'ls | grep pattern | wc -l') : ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    // Supprimer le saut de ligne à la fin de l'entrée
    input[strcspn(input, "\n")] = 0;

    // Séparer l'entrée en commandes individuelles
    split_commands(input, &commands, &num_commands);
    // Créer les pipes pour chaque paire de commandes
    for (int i = 0; i < num_commands - 1; i++)
    {
        if (pipe(pipefds + i * 2) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Exécuter chaque commande dans un processus fils
    for (int i = 0; i < num_commands; i++)
    {
        char *args[MAX_ARGS];
        pid_t pid;

        // Analyser la commande en arguments
        parse_command(commands[i], args);
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) // Processus fils
        {
            // Si ce n'est pas la première commande, on lit depuis le pipe précédent
            if (i > 0)
            {
                if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Si ce n'est pas la dernière commande, on écrit dans le pipe suivant
            if (i < num_commands - 1)
            {
                if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Fermer tous les descripteurs de pipe dans le processus fils
            for (int j = 0; j < 2 * (num_commands - 1); j++)
            {
                close(pipefds[j]);
            }

            // Exécuter la commande
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Fermer tous les descripteurs de pipe dans le processus père
    for (int i = 0; i < 2 * (num_commands - 1); i++)
    {
        close(pipefds[i]);
    }

    // Attendre la fin de tous les processus fils
    for (int i = 0; i < num_commands; i++)
    {
        wait(NULL);
    }

    // Libérer la mémoire allouée dynamiquement
    for (int i = 0; i < num_commands; i++)
    {
        free(commands[i]);
    }
    free(commands);

    return 0;
}
