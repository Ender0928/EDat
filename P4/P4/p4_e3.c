#include <stdio.h>
#include <stdlib.h>
#include "search_queue.h"
#include "file_utils.h"

// Función auxiliar para calcular la media de las calificaciones
float calculate_mean(SearchQueue *queue) {
    size_t size = search_queue_size(queue);
    if (size == 0) return 0.0;

    float sum = 0.0;
    SearchQueue *temp_queue = search_queue_new(float_print, float_cmp);
    while (!search_queue_isEmpty(queue)) {
        float *grade = (float *)search_queue_pop(queue);
        sum += *grade;
        search_queue_push(temp_queue, grade);
    }

    while (!search_queue_isEmpty(temp_queue)) {
        float *grade = (float *)search_queue_pop(temp_queue);
        search_queue_push(queue, grade);
    }
    search_queue_free(temp_queue);

    return sum / size;
}

// Función auxiliar para calcular la mediana de las calificaciones
float calculate_median(SearchQueue *queue) {
    size_t size = search_queue_size(queue);
    if (size == 0) return 0.0;

    float median = 0.0;
    SearchQueue *temp_queue = search_queue_new(float_print, float_cmp);
    size_t mid = size / 2;
    size_t index = 0;

    while (!search_queue_isEmpty(queue)) {
        float *grade = (float *)search_queue_pop(queue);
        if (size % 2 == 0 && (index == mid - 1 || index == mid)) {
            median += *grade / 2.0; // Promedio de los dos valores centrales
        } else if (size % 2 != 0 && index == mid) {
            median = *grade; // Valor central
        }
        search_queue_push(temp_queue, grade);
        index++;
    }

    while (!search_queue_isEmpty(temp_queue)) {
        float *grade = (float *)search_queue_pop(temp_queue);
        search_queue_push(queue, grade);
    }
    search_queue_free(temp_queue);

    return median;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int num_grades;
    if (fscanf(file, "%d", &num_grades) != 1) {
        fprintf(stderr, "Error reading the number of grades\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    SearchQueue *queue = search_queue_new(float_print, float_cmp);
    if (!queue) {
        fprintf(stderr, "Error creating SearchQueue\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    float grade;
    while (fscanf(file, "%f", &grade) == 1) {
        float *grade_ptr = malloc(sizeof(float));
        if (!grade_ptr) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            search_queue_free(queue);
            return EXIT_FAILURE;
        }
        *grade_ptr = grade;
        search_queue_push(queue, grade_ptr);
    }
    fclose(file);

    printf("Ordered grades: ");
    search_queue_print(stdout, queue);

    float mean = calculate_mean(queue);
    printf("Mean: %.2f\n", mean);

    float median = calculate_median(queue);
    printf("Median: %.2f\n", median);

    printf("Lowest grades: ");
    for (int i = 0; i < 3 && !search_queue_isEmpty(queue); i++) {
        float *lowest = (float *)search_queue_pop(queue);
        printf("%.2f ", *lowest);
        free(lowest);
    }
    printf("\n");

    printf("Highest grades: ");
for (int i = 0; i < 3 && !search_queue_isEmpty(queue); i++) {
    float *highest = (float *)search_queue_popBack(queue);
    if (highest) {
        printf("%.2f ", *highest);
        search_queue_pop(queue);
        free(highest);
    }
}
printf("\n");

    search_queue_free(queue);

    return EXIT_SUCCESS;
}