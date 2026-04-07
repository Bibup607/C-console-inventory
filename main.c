#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUCTS 100 // Максимальное кол-во товаров

struct Product {
    char name[50];
    int price;
    int id;
};

// Глобальные переменные для хранения данных
struct Product inventory[MAX_PRODUCTS];
int productCount = 0;

int randid() {
    return 100 + rand() % 900;
}

void createProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("\nИнвентарь переполнен!\n");
        return;
    }

    struct Product NewProduct;

    printf("\n======== Создание нового товара ========\n");
    printf("Введите название товара (без пробелов): ");
    scanf("%s", NewProduct.name);
    printf("Введите цену товара: ");
    scanf("%d", &NewProduct.price);

    NewProduct.id = randid();


    inventory[productCount] = NewProduct;
    productCount++;

    printf("\nТовар создан успешно!\n");

    printf("Название: %s | Цена: %d | ID: %d\n", NewProduct.name, NewProduct.price, NewProduct.id);
}

void showProducts() {
    printf("\n===== Список всех товаров =====\n");
    if (productCount == 0) {
        printf("Здесь пока пусто :(\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        printf("%d. [%d] %s — %d руб.\n", i + 1, inventory[i].id, inventory[i].name, inventory[i].price);
    }
}

void deleteProduct() {
    int idToDelete;
    printf("\nВведите ID товара для удаления: ");
    scanf("%d", &idToDelete);

    int found = -1;
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == idToDelete) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Сдвигаем элементы массива чтобы удалить текущий
        for (int i = found; i < productCount - 1; i++) {
            inventory[i] = inventory[i + 1];
        }
        productCount--;
        printf("Товар с ID %d удален.\n", idToDelete);
    } else {
        printf("Товар с таким ID не найден.\n");
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));

    int choice;

    // Главный цикл программы
    while (1) {
        printf("\n====== Менеджер товаров ======\n");
        printf("1. Управление инвентарем\n");
        printf("0. Выйти\n");
        printf("Ваше действие: ");
        scanf("%d", &choice);

        if (choice == 0) break;
        if (choice != 1) continue;

        // Инвентарь
        int inventChoice;
        while (1) {
            showProducts();
            printf("\n--- Действия ---\n");
            printf("1. Добавить товар\n");
            printf("2. Удалить товар по ID\n");
            printf("0. Назад в главное меню\n");
            printf("Ваше действие: ");
            scanf("%d", &inventChoice);

            if (inventChoice == 1) {
                createProduct();
            } else if (inventChoice == 2) {
                deleteProduct();
            } else if (inventChoice == 0) {
                break; 
            }
        }
    }

    printf("Программа завершена.\n");
    return 0;
}
