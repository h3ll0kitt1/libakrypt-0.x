# Libakrypt: mt19937

## Что было изменено в библиотеке и в каких файлах:

### ak_oid.c

Библиотека `libakrypt` поддерживает свое собственное дерево идентификаторов, корнем
которого служит последовательность `1.2.643.2.52.1`. Генераторы псевдо-случайных чисел
используют  `1.2.643.2.52.1.1`
  
  Для принятого в бибилиотеке поиска   добавлены с идентификатором `1.2.643.2.52.1.1.5` и именем `mt19937`:
  
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

Добавлена реализация класса rng_mt19937  

Определены функции:
(тело функций в readme не выносилось)

```c
static int ak_random_mt19937_next( ak_random rnd );

static int ak_random_mt19937_randomize_ptr( ak_random rnd, const ak_pointer ptr, const ssize_t size );

static int ak_random_mt19937_random( ak_random rnd, const ak_pointer ptr, const ssize_t size );
```

```c

 int ak_random_create_mt19937( ak_random generator )
 {
     int error = ak_error_ok;
     ak_uint32 dword = (ak_uint32)ak_random_value();

     if(( error = ak_random_create( generator )) != ak_error_ok )
         return ak_error_message( error, __func__ , "wrong initialization of random generator" );

     generator->oid = ak_oid_find_by_name( "mt19937" );
     generator->next = ak_random_mt19937_next;
     generator->randomize_ptr = ak_random_mt19937_randomize_ptr;
     generator->random = ak_random_mt19937_random;

     /* для корректной работы присваиваем какое-то случайное начальное значение */
      ak_random_mt19937_randomize_ptr( generator, &dword, sizeof( ak_uint32 ));
      return error;
 }
```


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


