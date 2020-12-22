# Libakrypt: mt19937

## Что было изменено в библиотеке и в каких файлах:

### ak_oid.c

написать что добавлено

### ak_random.c

В struct random  в union data  добавлена struct MT для внутреннего состояния mt19937

```c
struct {
   ak_uint32 mt[624];
   int index;
   ak_uint32 value;
} MT;
 ```

Добавлена инициализация контекста mt19937 
 
```c
  dll_export int ak_random_create_mt19937( ak_random );
```

### libakrypt.h

написать что добавлено

### ../examples/test-random01.c

написать что изменено

## Про mt19937, который встраивался:

### Алгоритм:

### Параметры:

## Результаты:
 
Последовательность, полученная с помощью  std::mt19937 из \<random> для C++:
![](MT_test/image.png)

Последовательнось, полученная с помощью функции после встраивания в Libakrypt:
![](MT_test/libacrypt_test_results.jpg)

Вывод: полученные последовательности совпадают. 


