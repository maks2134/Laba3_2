#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"

struct CarConfiguration {
    char body_type[50];
    float engine_volume;
    int start_year;
    int end_year;
};

struct CarModel {
    char* model_name;
    struct CarConfiguration* compictation;
    int num_configurations;
};

enum { ADD, OUTPUT, DELETE, SORT, REMOVE, END };

void fillFile(struct CarModel* Car, int num) {
    FILE* fp = fopen("C:\\Users\\Admin\\CLionProjects\\Laba10\\input.txt", "w");
    fprintf(fp, "%d\n", num);
    for (int i = 0; i < num; i++) {
        fprintf(fp, "%d ", Car[i].num_configurations);
        fprintf(fp, "%s ", Car[i].model_name);
        for (int j = 0; j < Car[i].num_configurations; j++) {
            fprintf(fp, "%s %f %d %d\n", Car[i].compictation[j].body_type, Car[i].compictation[j].engine_volume,
                    Car[i].compictation[j].start_year, Car[i].compictation[j].end_year);
        }
    }
    fclose(fp);
}

void addCars(struct CarModel** Car, int* num) {
    (*num)++;
    struct CarModel* tmp = realloc((*Car), sizeof(struct CarModel) * (*num));
    if (tmp != NULL) {
        *Car = tmp;
    } else {
        printf("Ошибка памяти");
        exit(-1);
    }

    struct CarModel carr;
    printf("Введите количество:\n");
    scanf("%d", &carr.num_configurations);

    printf("Введите модель машины:\n");
    char input_model_name[50];
    scanf("%s", input_model_name);
    carr.model_name = malloc(strlen(input_model_name) + 1);
    strcpy(carr.model_name, input_model_name);

    printf("Введите комплектацию:\n");
    carr.compictation = malloc(carr.num_configurations * sizeof(struct CarConfiguration));
    for (int i = 0; i < carr.num_configurations; i++) {
        scanf("%s %f %d %d", carr.compictation[i].body_type, &carr.compictation[i].engine_volume,
              &carr.compictation[i].start_year, &carr.compictation[i].end_year);
    }

    (*Car)[(*num) - 1] = carr;
    fillFile((*Car), (*num));
}

void deleteCar(struct CarModel** Car, int* num, int index) {
    free((*Car)[index].compictation);
    for (int i = index; i < *num - 1; i++) {
        (*Car)[i] = (*Car)[i + 1];
    }
    (*num)--;
    struct CarModel* tmp = realloc(*Car, sizeof(struct CarModel) * (*num));
    if (tmp != NULL) {
        *Car = tmp;
    }
    else {
        printf("Ошибка памяти");
        exit(-1);
    }
    fillFile((*Car), (*num));
}
void result(struct CarModel* Car, int num) {
    for (int i = 0; i < num; i++) {
        printf("%d ", Car[i].num_configurations);
        printf("%s ", Car[i].model_name);
        for (int j = 0; j < Car[i].num_configurations; j++) {
            printf(" %s %.2f %d %d\n", Car[i].compictation[j].body_type, Car[i].compictation[j].engine_volume,
                   Car[i].compictation[j].start_year, Car[i].compictation[j].end_year);
        }
    }

}
void sorting(struct CarModel* Car, int num) {
    struct BodyTypeLifeCycle {
        char body_type[50];
        float life_cycle;
        int count;
    };
    struct BodyTypeLifeCycle type[100];
    int k = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < Car[i].num_configurations; j++) {
            float life_cycle = Car[i].compictation[j].end_year - Car[i].compictation[j].start_year;
            int found = 0;
            for (int r = 0; r < k; r++) {
                if (strcmp(type[r].body_type, Car[i].compictation[j].body_type) == 0) {
                    type[r].life_cycle += life_cycle;
                    type[r].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(type[k].body_type, Car[i].compictation[j].body_type);
                type[k].life_cycle = life_cycle;
                type[k].count = 1;
                k++;
            }
        }
    }
    for (int i = 0; i < k; i++)
        type[i].life_cycle /= type[i].count;

    for (int i = 0; i < k - 1; i++) {
        for (int j = i + 1; j < k; j++) {
            if (type[i].life_cycle < type[j].life_cycle) {
                struct BodyTypeLifeCycle temp = type[i];
                type[i] = type[j];
                type[j] = temp;
            }
        }
    }
    printf("Типы кузовов::\n");
    for (int i = 0; i < k; i++) {
        printf("%s\n", type[i].body_type);
    }
}
void removeModalTask(struct CarModel* Car, int* num) {
    float min_life_cycle = Car[0].compictation[0].end_year - Car[0].compictation[0].start_year;
    for (int i = 0; i < *num; i++) {
        for (int j = 0; j < Car[i].num_configurations; j++) {
            int life_cycle = Car[i].compictation[j].end_year - Car[i].compictation[j].start_year;
            if (life_cycle < min_life_cycle) {
                min_life_cycle = life_cycle;
            }
        }
    }

    for (int i = 0; i < *num; i++) {
        int keep_model = 1;
        for (int j = 0; j < Car[i].num_configurations; j++) {
            int  life_cycle = Car[i].compictation[j].end_year - Car[i].compictation[j].start_year;
            if (life_cycle == min_life_cycle) {
                deleteCar(&Car, num, i);
                break;
            }
        }
    }
    fillFile((Car), (*num));
}

void freeStruct(struct CarModel* Car, int num) {
    for (int i = 0; i < num; i++) {
        free(Car[i].compictation);
        free(Car[i].model_name);
    }
    free(Car);
}

void Interface(struct CarModel* Car,int num) {
    while (1) {
        printf("0-Добавить машину\n1-Вывод файла\n2-Удалить элемент с индексом\n3-Сортировка кузовов\n4-Удаление моделей по жизненному циклу:\n5-Завершить работу программы\n");
        int number;
        scanf("%d", &number);
        switch (number)
        {
            case ADD: {
                addCars(&Car, &num);
                break;
            }
            case OUTPUT: {
                result(Car, num);
                break;
            }
            case DELETE:
            {
                printf("Индекс:\n");
                int index;
                scanf("%d", &index);
                deleteCar(&Car, &num, index - 1);
                break;
            }
            case SORT:
            {
                sorting(Car, num);
                break;
            }
            case REMOVE:
            {
                removeModalTask(Car, &num);
                break;
            }
            case END:
            {
                return;
                break;
            }
            default:
                freeStruct(Car, num);
                break;
        }
    }
}

void solveTask2() {
    FILE* fp = fopen("C:\\Users\\Admin\\CLionProjects\\Laba10\\input.txt", "r");
    if (fp == NULL) {
        printf("Ошибка открытия файла");
        exit(1);
    }

    int num;
    fscanf(fp, "%d", &num);
    struct CarModel* Car = malloc(sizeof(struct CarModel) * num);
    for (int i = 0; i < num; i++) {
        fscanf(fp, "%d", &Car[i].num_configurations);

        char input_model_name[50];
        fscanf(fp, "%s ", input_model_name);

        Car[i].model_name = malloc(strlen(input_model_name) + 1);
        strcpy(Car[i].model_name, input_model_name);

        Car[i].compictation = malloc(Car[i].num_configurations * sizeof(struct CarConfiguration));
        for (int j = 0; j < Car[i].num_configurations; j++) {
            fscanf(fp, "%s %f %d %d\n", Car[i].compictation[j].body_type, &Car[i].compictation[j].engine_volume,
                   &Car[i].compictation[j].start_year, &Car[i].compictation[j].end_year);
        }
    }

    fclose(fp);
    Interface(Car, num);
}