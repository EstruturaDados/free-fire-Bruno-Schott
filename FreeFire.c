#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// definição da struct Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// variaveis globais
struct Item mochila[10]; // vetor para armazenar até 10 itens
int totalItens = 0;      // contador de itens na mochila

// prototipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void menuPrincipal();
void limparBuffer();

int main() {
    printf("=== SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo ao sistema de gerenciamento de inventário!\n\n");
    
    menuPrincipal();
    return 0;
}


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// funcao para cadastrar um novo item na mochila
void inserirItem() {
    if (totalItens >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRAR NOVO ITEM ===\n");
    
    // nome do item
    printf("Nome do item (max 29 caracteres): ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0'; // Remove \n
    
    // tipo do item
    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0'; // Remove \n
    
    // quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();
    
    // validar quantidade
    if (mochila[totalItens].quantidade <= 0) {
        printf("❌ Quantidade inválida! Item não cadastrado.\n");
        return;
    }
    
    totalItens++;
    printf("✅ Item '%s' cadastrado com sucesso!\n", mochila[totalItens-1].nome);
}

// remover um item da mochila
void removerItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOVER ITEM ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; 
    
    // sequencial pelo item
    int indice = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        return;
    }
    
    // item que será removido
    printf("🗑️  Item encontrado:\n");
    printf("   Nome: %s\n", mochila[indice].nome);
    printf("   Tipo: %s\n", mochila[indice].tipo);
    printf("   Quantidade: %d\n", mochila[indice].quantidade);
    
    // remoção
    printf("Tem certeza que deseja remover este item? (s/n): ");
    char confirmacao;
    scanf("%c", &confirmacao);
    limparBuffer();
    
    if (confirmacao == 's' || confirmacao == 'S') {
        // remover item movendo os elementos subsequentes
        for (int i = indice; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("✅ Item '%s' removido com sucesso!\n", nomeBusca);
    } else {
        printf("Operação cancelada.\n");
    }
}

// listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("\n📭 Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }
    
    printf("\n=== LISTA DE ITENS NA MOCHILA ===\n");
    printf("Total de itens: %d/10\n\n", totalItens);
    
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("   🏷️  Nome: %s\n", mochila[i].nome);
        printf("   📋 Tipo: %s\n", mochila[i].tipo);
        printf("   🔢 Quantidade: %d\n", mochila[i].quantidade);
        printf("   --------------------\n");
    }
    
    // estatísticas
    int armas = 0, municoes = 0, curas = 0, ferramentas = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].tipo, "arma") == 0) armas++;
        else if (strcmp(mochila[i].tipo, "municao") == 0) municoes++;
        else if (strcmp(mochila[i].tipo, "cura") == 0) curas++;
        else if (strcmp(mochila[i].tipo, "ferramenta") == 0) ferramentas++;
    }
    
    printf("\n📊 Estatísticas do inventário:\n");
    printf("   🔫 Armas: %d\n", armas);
    printf("   💊 Munições: %d\n", municoes);
    printf("   🩹 Kits de cura: %d\n", curas);
    printf("   🛠️  Ferramentas: %d\n", ferramentas);
}

// busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCAR ITEM ===\n");
    char nomeBusca[30];
    
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; 
    
    // busca sequencial
    int encontrados = 0;
    printf("\n🔍 Resultados da busca por '%s':\n", nomeBusca);
    
    for (int i = 0; i < totalItens; i++) {
        if (strstr(mochila[i].nome, nomeBusca) != NULL) {
            printf("\n   Item encontrado na posição %d:\n", i + 1);
            printf("      🏷️  Nome: %s\n", mochila[i].nome);
            printf("      📋 Tipo: %s\n", mochila[i].tipo);
            printf("      🔢 Quantidade: %d\n", mochila[i].quantidade);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("❌ Nenhum item encontrado com o nome '%s'.\n", nomeBusca);
    } else {
        printf("\n✅ Total de itens encontrados: %d\n", encontrados);
    }
}

// menu principal
void menuPrincipal() {
    int opcao;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. 🎒 Listar itens da mochila\n");
        printf("2. ➕ Cadastrar novo item\n");
        printf("3. 🗑️  Remover item\n");
        printf("4. 🔍 Buscar item por nome\n");
        printf("5. 🚪 Sair do sistema\n");
        printf("\nDigite sua opção (1-5): ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                listarItens();
                break;
            case 2:
                inserirItem();
                break;
            case 3:
                removerItem();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\n🎮 Obrigado por usar o Sistema de Inventário!\n");
                printf("Até a próxima missão!\n");
                break;
            default:
                printf("❌ Opção inválida! Digite um número entre 1 e 5.\n");
        }
        
        
        if (opcao != 5) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while (opcao != 5);
}
