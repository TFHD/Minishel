#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_CMD_LENGTH 256

int main() {
    char cmd1[MAX_CMD_LENGTH], cmd2[MAX_CMD_LENGTH];
    char *argv1[20], *argv2[20];
    int pipe_fd[2];  // Table des descripteurs de fichiers pour le pipe
    pid_t pid1, pid2;

    // Demander à l'utilisateur de saisir les deux commandes
    printf("Entrez la première commande : ");
    fgets(cmd1, MAX_CMD_LENGTH, stdin);
    cmd1[strcspn(cmd1, "\n")] = '\0';  // Supprimer le '\n' à la fin

    printf("Entrez la deuxième commande : ");
    fgets(cmd2, MAX_CMD_LENGTH, stdin);
    cmd2[strcspn(cmd2, "\n")] = '\0';  // Supprimer le '\n' à la fin

    // Séparer les arguments des deux commandes (on suppose que les arguments sont séparés par des espaces)
    char *token = strtok(cmd1, " ");
    int i = 0;
    while (token != NULL) {
        argv1[i++] = token;
        token = strtok(NULL, " ");
    }
    argv1[i] = NULL;  // Terminer la liste des arguments par NULL

    token = strtok(cmd2, " ");
    i = 0;
    while (token != NULL) {
        argv2[i++] = token;
        token = strtok(NULL, " ");
    }
    argv2[i] = NULL;  // Terminer la liste des arguments par NULL

    // Créer le pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Création du premier processus
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        // Dans le processus fils 1 (le premier processus)
        
        // Fermer la lecture du pipe dans ce processus
        close(pipe_fd[0]);
        
        // Rediriger la sortie standard (STDOUT) vers l'écriture du pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        
        // Exécuter la première commande
        execvp(argv1[0], argv1);
        perror("execvp");  // Si execvp échoue
        exit(1);
    }

    // Création du deuxième processus
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        // Dans le processus fils 2 (le deuxième processus)
        
        // Fermer l'écriture du pipe dans ce processus
        close(pipe_fd[1]);
        
        // Rediriger l'entrée standard (STDIN) vers la lecture du pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        
        // Exécuter la deuxième commande
        execvp(argv2[0], argv2);
        perror("execvp");  // Si execvp échoue
        exit(1);
    }
    
    // Fermer les deux côtés du pipe dans le processus parent
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Attendre que les processus enfants se terminent
    wait(NULL);
    wait(NULL);

    return 0;
}
