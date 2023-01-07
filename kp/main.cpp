#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <time.h>
#include "./include/allocator_list.h"
#include "./include/allocator_mkk.h"

using namespace std;

// запросы содержат адрес и размер запрашиваемого места
typedef struct request_strucе {
  void* address;
  size_t bytes;
} request;

// char* в число
size_t ToSizeT(const char* string) {
    size_t size = 0;

    while (*string != '\0') {
        if (*string < '0' || *string > '9') return 0;

        size = size * 10 + *string - '0';
        ++string;
    }

    return size;
}

int main(int argument_count, char* argument_vector[]) {
    const size_t REQUEST_QUANTITY = 1000;
    const size_t MAX_BYTES = 5000;
    clock_t first_time, second_time;
    size_t first_index, second_index, third_index;
    size_t argument;
    size_t query = 0;
    size_t total = 0;
    size_t* permute = (size_t*)malloc(sizeof(size_t) * REQUEST_QUANTITY);
    request* requests = (request*)malloc(sizeof(request) * REQUEST_QUANTITY);

    // генератор случайных чисел
    srand((unsigned int)time(0));

    argument = ToSizeT(argument_vector[1]);

    // аллокация списка свободных блоков
    if (!InitializationList(argument)) {
        cout << "Error. No memory\n";
        return 0;
    }
    // аллокация Мак-Кьюзи-Кэрлса
    if (!MKKInitialization(argument)) {
        cout << "Error. No memory\n";
        return 0;
    }

    // псевдослучайные запросы и массив для них
    for (first_index = 0; first_index < REQUEST_QUANTITY; ++first_index) {
        requests[first_index].bytes = 1 + rand() % MAX_BYTES;
        permute[first_index] = first_index;
    }

    for (first_index = 0; first_index < REQUEST_QUANTITY; ++first_index) {
        second_index = rand() % REQUEST_QUANTITY;
        third_index = rand() % REQUEST_QUANTITY;
        argument = permute[second_index];
        permute[second_index] = permute[third_index];
        permute[third_index] = argument;
    }

    cout << "Количество запросов: " << REQUEST_QUANTITY << "\n";
    cout << "Байт: " << MAX_BYTES << "\n\n";
    cout << "Аллокация списка свободных блоков:\n";

    first_time = clock();

    // для каждого запроса ищем свободный блок
    for (first_index = 0; first_index < REQUEST_QUANTITY; ++first_index) {
        requests[first_index].address = malloc_list(requests[first_index].bytes);
    }
        
    second_time = clock();

    printf("Заняло времени: %lf\n", (double)(second_time - first_time) / CLOCKS_PER_SEC);

    // снова счетчики
    query = ListOfRequests();
    total = TotalList();

    for (first_index = 0; first_index < REQUEST_QUANTITY; ++first_index) {
        if (requests[permute[first_index]].address == NULL) continue;
        FreeList(requests[permute[first_index]].address);
    }
        
    first_time = clock();

    printf("Очистка заняла: %lf\n", (double)(first_time - second_time) / CLOCKS_PER_SEC);
    cout << "КПД использованной и запрошенной памяти: " << (long double)query / total << "\n\n";
    cout << "Аллокация Мак-Кьюзи-Кэрлса\n";

    first_time = clock();
        
    for (first_index = 0; first_index < REQUEST_QUANTITY; ++first_index) {
        requests[first_index].address = MKKMalloc(requests[first_index].bytes);
    }
        
    second_time = clock();

    printf("Заняло времени: %lf\n", (double)(second_time - first_time) / CLOCKS_PER_SEC);

    // снова счетчики
    query = MKKRequest();
    total = MKKTotal();

    for (first_index = 0; first_index < REQUEST_QUANTITY; ++first_index) {
        if (requests[permute[first_index]].address == NULL) {
            continue;
        }
        MKKFree(requests[permute[first_index]].address);
    }
        
    first_time = clock();

    printf("Очистка заняла: %lf\n", (double)(first_time - second_time) / CLOCKS_PER_SEC);
    cout << "КПД использования и запрошенной памяти: " << (long double)query / total << "\n";

    Destroy();
    MKKDestroy();

    free(requests);
    free(permute);

    return 0;
}
