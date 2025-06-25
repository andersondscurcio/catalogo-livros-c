#include <stdio.h>     // Inclui biblioteca padrao para entrada e saida (printf, scanf, fopen, etc)
#include <stdlib.h>    // Inclui biblioteca padrao para funcoes utilitarias (malloc, atoi, etc)
#include <string.h>    // Inclui funcoes para manipulacao de strings (strcpy, strcmp, strtok, etc)

#define MAX 100                // Define o numero maximo de livros no catalogo
#define CSV_FILE "C:\\livraria\\livros.csv"  // Define o caminho do arquivo CSV

// Define a estrutura que representa um livro
typedef struct {
    char isbn[20];         // Campo para armazenar o codigo ISBN do livro
    char titulo[100];      // Campo para armazenar o titulo do livro
    char autor[100];       // Campo para armazenar o nome do autor
    char editora[100];     // Campo para armazenar o nome da editora
    int ano;               // Campo para armazenar o ano de publicacao
    int exemplares;        // Campo para armazenar a quantidade de exemplares disponiveis
} Livro;

Livro catalogo[MAX];       // Vetor que armazena os livros cadastrados
int totalLivros = 0;       // Contador para controlar quantos livros estao cadastrados

// Funcao que carrega os livros do arquivo CSV para a memoria
void carregarLivros() {
    FILE *file = fopen(CSV_FILE, "r");   // Abre o arquivo em modo leitura
    if (!file) return;                   // Se nao conseguir abrir, sai da funcao

    // Enquanto conseguir ler uma linha com todos os campos
    while (fscanf(file, " %[^,],%[^,],%[^,],%[^,],%d,%d\n",
           catalogo[totalLivros].isbn,        // Ler  o campo ISBN
           catalogo[totalLivros].titulo,      // Ler o campo titulo
           catalogo[totalLivros].autor,       // Ler o campo autor
           catalogo[totalLivros].editora,     // Ler o campo editora
           &catalogo[totalLivros].ano,        // Ler o campo ano
           &catalogo[totalLivros].exemplares  // Ler o campo exemplares
           ) == 6) {
        totalLivros++;  // Incrementa o contador de livros cadastrados
    }

    fclose(file);  // Fecha o arquivo apos ler
}

// Funcao que salva os livros da memoria para o arquivo CSV
void salvarLivros() {
    FILE *file = fopen(CSV_FILE, "w");  // Abre o arquivo em modo escrita (sobrescreve)
    for (int i = 0; i < totalLivros; i++) {
        // Escreve cada livro no arquivo no formato CSV

        fprintf(file, "%s,%s,%s,%s,%d,%d\n",
                catalogo[i].isbn, // Vetores Prof Marcos
                catalogo[i].titulo,
                catalogo[i].autor,
                catalogo[i].editora,
                catalogo[i].ano,
                catalogo[i].exemplares);
    }
    fclose(file);  // Fecha o arquivo apos salvar
}

// Funcao para inserir um novo livro no catalogo // Aulas Professor Marcos
void inserirLivro() {
    if (totalLivros >= MAX) {  // Verifica se o catalogo esta cheio
        printf("Catalogo cheio.\n");
        return;                // Sai da funcao sem inserir
    }

    Livro l;  // Cria variavel temporaria para o livro - Prof Marcos E Nava

    // Le  os dados inseridos // Prof Marcos e Nava
    printf("ISBN: "); fgets(l.isbn, 20, stdin); strtok(l.isbn, "\n");  // Le o ISBN e remove o \n
    printf("Titulo: "); fgets(l.titulo, 100, stdin); strtok(l.titulo, "\n");  // Le o titulo e remove o \n
    printf("Autor: "); fgets(l.autor, 100, stdin); strtok(l.autor, "\n");    // Le o autor e remove o \n
    printf("Editora: "); fgets(l.editora, 100, stdin); strtok(l.editora, "\n");  // Le a editora e remove o \n
    printf("Ano de publicacao: "); scanf("%d", &l.ano);                      // Le o ano de publicacao
    printf("Exemplares disponiveis: "); scanf("%d", &l.exemplares);          // Le a quantidade de exemplares
    getchar();  // Limpa o \n que ficou no buffer apos o scanf

    catalogo[totalLivros++] = l;  // Adiciona o livro no vetor e incrementa contador
    salvarLivros();               // Salva o catalogo atualizado no arquivo CSV
    printf("Livro inserido com sucesso!\n");
}

// Funcao para buscar um livro pelo ISBN // Prof Marcos
int buscarPorISBN(char *isbn) {
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(catalogo[i].isbn, isbn) == 0)  // Compara o ISBN de cada livro
            return i;  // Retorna o indice do livro encontrado
    }
    return -1;  // Retorna -1 se nao encontrar
}

// Funcao para buscar um livro pelo titulo (busca parcial)
int buscarPorTitulo(char *titulo) {
    for (int i = 0; i < totalLivros; i++) {
        if (strstr(catalogo[i].titulo, titulo))  // Verifica se titulo contem o texto buscado
            return i;  // Retorna o indice do livro encontrado
    }
    return -1;  // Retorna -1 se nao encontrar
}

// Funcao para atualizar os dados de um livro ja cadastrado
void atualizarLivro() {
    char isbn[20];
    printf("Digite o ISBN do livro a atualizar: ");
    fgets(isbn, 20, stdin); strtok(isbn, "\n");  // Le o ISBN e remove o \n

    int i = buscarPorISBN(isbn);  // Busca o indice do livro
    if (i == -1) {
        printf("Livro nao encontrado.\n");
        return;  // Sai se nao achar o livro
    }

    // Le os novos dados do livro
    printf("Novo titulo: "); fgets(catalogo[i].titulo, 100, stdin); strtok(catalogo[i].titulo, "\n");
    printf("Novo autor: "); fgets(catalogo[i].autor, 100, stdin); strtok(catalogo[i].autor, "\n");
    printf("Nova editora: "); fgets(catalogo[i].editora, 100, stdin); strtok(catalogo[i].editora, "\n");
    printf("Novo ano: "); scanf("%d", &catalogo[i].ano);
    printf("Novos exemplares: "); scanf("%d", &catalogo[i].exemplares);
    getchar();  // Limpa o \n do buffer

    salvarLivros();  // Salva as alteracoes no arquivo CSV
    printf("Livro atualizado.\n");
}

// Funcao para remover um livro pelo ISBN
void removerLivro() {
    char isbn[20];
    printf("Digite o ISBN do livro a remover: ");
    fgets(isbn, 20, stdin); strtok(isbn, "\n");  // Le o ISBN e remove o \n

    int i = buscarPorISBN(isbn);  // Busca o indice do livro
    if (i == -1) {
        printf("Livro nao encontrado.\n");
        return;  // Sai se nao achar o livro
    }

    // Move todos os livros apos o livro removido uma posicao para tras
    for (int j = i; j < totalLivros - 1; j++) {
        catalogo[j] = catalogo[j + 1];
    }
    totalLivros--;  // Decrementa o contador de livros cadastrados

    salvarLivros();  // Salva o catalogo atualizado no arquivo CSV
    printf("Livro removido com sucesso.\n");
}

// Funcao para listar todos os livros cadastrados
void listarLivros() {
    printf("CATALOGO DE LIVROS:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("[%d] %s - %s - %s - %s - %d - %d exemplares\n", i + 1,
               catalogo[i].isbn,
               catalogo[i].titulo,
               catalogo[i].autor,
               catalogo[i].editora,
               catalogo[i].ano,
               catalogo[i].exemplares);
    }
}

// Funcao que exibe o menu de opcoes para o usuario
void menu() {
    int opcao;
    do {
        printf("\n----- MENU -----\n");
        printf("1. Inserir Livro\n");
        printf("2. Buscar por ISBN\n");
        printf("3. Buscar por Titulo\n");
        printf("4. Atualizar Livro\n");
        printf("5. Remover Livro\n");
        printf("6. Listar Livros\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o \n apos o scanf

        switch (opcao) {
            case 1: inserirLivro(); break;  // Chama funcao para inserir livro
            case 2: {                      // Busca por ISBN
                char isbn[20];
                printf("ISBN: ");
                fgets(isbn, 20, stdin); strtok(isbn, "\n");
                int i = buscarPorISBN(isbn);
                if (i != -1)
                    printf("Encontrado: %s - %s\n", catalogo[i].isbn, catalogo[i].titulo);
                else
                    printf("Nao encontrado.\n");
                break;
            }
            case 3: {                      // Busca por titulo
                char titulo[100];
                printf("Titulo (ou parte): ");
                fgets(titulo, 100, stdin); strtok(titulo, "\n");
                int i = buscarPorTitulo(titulo);
                if (i != -1)
                    printf("Encontrado: %s - %s\n", catalogo[i].isbn, catalogo[i].titulo);
                else
                    printf("Nao encontrado.\n");
                break;
            }
            case 4: atualizarLivro();
            break;  // Atualiza livro existente
            case 5: removerLivro();
            break;    // Remove livro existente
            case 6: listarLivros();
            break;    // Lista todos os livros
            case 0: printf("Saindo...\n");
            break;  // Sai do programa
            default: printf("Opcao invalida!\n");  // Opcao invalida //Professor Marcos
        }
    } while (opcao != 0);
}

// Funcao  inicial do programa // conforme aula professor Marcos
int main() {
    carregarLivros();  // Carrega os livros salvos no arquivo CSV
    menu();            // Chama o menu principal
    return 0;          // Finaliza o programa
}

// Utilizados Aulas pdf Professor Marcos
//// Utilizados Slides de Logica de Programação Nava
//Ulizado site https://c-basic.readthedocs.io/pt/latest/index.html