# Libakrypt: mt19937

## Что было изменено в библиотеке и в каких файлах:

### ak_oid.c

Библиотека `libakrypt` поддерживает свое собственное дерево идентификаторов, корнем
  которого служит последовательность `1.2.643.2.52.1`.
  Данные значения используются в случае, когда идентификаторы алгоритмов не определены
  ни рекомендациями ТК 26, ни существующими реализациями других производителей
  программного обеспечения.

  Поддеревья алгоритмов и их параметров определяются следующим образом.

  - `1.2.643.2.52.1.1` генераторы псевдо-случайных чисел,
  
  Для принятого в бибилиотеке поиска   добавлены:
  
  ```c
  static const char *asn1_mt19937_n[] =     { "mt19937", NULL };
  static const char *asn1_mt19937_i[] =     { "1.2.643.2.52.1.1.5", NULL };
  
  ```
  
  ```c
  { random_generator, algorithm, asn1_mt19937_i, asn1_mt19937_n, NULL,
  {{ sizeof( struct random ), (ak_function_create_object *)ak_random_create_mt19937,
                             (ak_function_destroy_object *)ak_random_destroy, NULL, NULL, NULL },
                                                               ak_object_undefined, NULL, NULL }}
  ```

### libakrypt.h 

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

### ak_random.c

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


