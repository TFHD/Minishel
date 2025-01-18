#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 100

// Structure d'un nœud d'arbre binaire
typedef struct Node {
    char *command;      // La commande (par exemple, "ls", "grep", etc.)
    struct Node *left;  // Nœud à gauche (pour une autre commande dans la chaîne de pipe)
    struct Node *right; // Nœud à droite (si présent)
} Node;

// Fonction pour diviser une chaîne en arguments (par exemple, "ls -l" devient ["ls", "-l"])
int parse_args(char *line, char **args) {
    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Le dernier élément doit être NULL pour execvp
    return i;
}

// Fonction pour exécuter une commande
void execute_command(char *command, int input_fd, int output_fd) {
    char *args[MAX_ARGS];
    parse_args(command, args);

    // Création d'un processus fils
    pid_t pid = fork();
    if (pid == 0) {
        // Rediriger l'entrée et la sortie si nécessaire
        if (input_fd != 0) {
            dup2(input_fd, 0); // Redirige l'entrée standard
            close(input_fd);
        }
        if (output_fd != 1) {
            dup2(output_fd, 1); // Redirige la sortie standard
            close(output_fd);
        }

        // Exécuter la commande
        execvp(args[0], args);
        perror("execvp échoué");
        exit(1);
    }
}

// Fonction pour créer un pipe et exécuter les commandes dans l'arbre
void execute_pipe(Node *root) {
    if (root == NULL) return;

    // Si c'est une feuille (une seule commande)
    if (root->left == NULL && root->right == NULL) {
        execute_command(root->command, 0, 1);
        return;
    }

    // Exécuter la commande de gauche
    int pipe_fds[2];
    pipe(pipe_fds);

    execute_command(root->command, 0, pipe_fds[1]);
    close(pipe_fds[1]); // Fermeture de l'écriture du pipe

    // Exécuter la commande de droite avec l'entrée du pipe
    execute_pipe(root->right);

    close(pipe_fds[0]); // Fermeture de la lecture du pipe
}

// Fonction pour ajouter une commande à l'arbre (simplifié ici)
Node *create_node(char *command) {
    Node *new_node = malloc(sizeof(Node));
    new_node->command = strdup(command);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Fonction pour analyser l'entrée de l'utilisateur et créer l'arbre
Node *parse_input(char *input) {
    Node *root = NULL, *current = NULL;
    char *token = strtok(input, "|");
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (root == NULL) {
            root = new_node;
        } else {
            current->right = new_node; // Relier les nœuds
        }
        current = new_node;
        token = strtok(NULL, "|");
    }
    return root;
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    printf("Entrez une commande (| pour pipe, q pour quitter) :\n");

    while (1) {
        printf(">");
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL) {
            break;
        }
        
        // Supprimer le '\n' à la fin de la commande
        input[strcspn(input, "\n")] = 0;

        // Quitter si l'utilisateur entre "q"
        if (strcmp(input, "q") == 0) {
            break;
        }

        // Créer l'arbre à partir de l'entrée de l'utilisateur
        Node *root = parse_input(input);

        // Exécuter les commandes avec pipe
        execute_pipe(root);

        // Attendre la fin des processus fils
        while (wait(NULL) > 0);
    }

    return 0;
}
