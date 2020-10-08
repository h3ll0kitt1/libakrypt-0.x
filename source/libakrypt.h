/* ----------------------------------------------------------------------------------------------- */
/*  Copyright (c) 2014 - 2020 by Axel Kenzo, axelkenzo@mail.ru                                     */
/*                                                                                                 */
/*  Файл libakrypt.h                                                                               */
/* ----------------------------------------------------------------------------------------------- */
#ifndef    __LIBAKRYPT_H__
#define    __LIBAKRYPT_H__

/* ----------------------------------------------------------------------------------------------- */
 #include <libakrypt-base.h>

/* ----------------------------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Попытка доступа к неопределенной опции библиотеки. */
 #define ak_error_wrong_option                (-100)

/*! \brief Неверный тип криптографического механизма. */
 #define ak_error_oid_engine                  (-110)
/*! \brief Неверный режим использования криптографического механизма. */
 #define ak_error_oid_mode                    (-111)
/*! \brief Ошибочное или не определенное имя криптографического механизма. */
 #define ak_error_oid_name                    (-112)
/*! \brief Ошибочный или неопределенный идентификатор криптографического механизма. */
 #define ak_error_oid_id                      (-113)
/*! \brief Ошибочный индекс идентификатора криптографического механизма. */
 #define ak_error_oid_index                   (-114)
/*! \brief Ошибка с обращением к oid. */
 #define ak_error_wrong_oid                   (-115)

/* ----------------------------------------------------------------------------------------------- */
/** \addtogroup test-options Инициализация и настройка параметров библиотеки
 @{ */
/*! \brief Функция инициализации библиотеки. */
 dll_export int ak_libakrypt_create( ak_function_log * );
/*! \brief Функция завершает работу с библиотекой. */
 int ak_libakrypt_destroy( void );
/*! \brief Функция выполняет динамическое тестирование работоспособности криптографических преобразований. */
 dll_export bool_t ak_libakrypt_dynamic_control_test( void );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Функция возвращает номер версии бибилиотеки libakrypt. */
 dll_export const char *ak_libakrypt_version( void );
/*! \brief Функция возвращает общее количества опций библиотеки. */
 dll_export size_t ak_libakrypt_options_count( void );
/*! \brief Функция возвращает имя функции по ее индексу. */
 dll_export char *ak_libakrypt_get_option_name( const size_t );
/*! \brief Функция возвращает значение опции по ее имени. */
 dll_export ak_int64 ak_libakrypt_get_option_by_name( const char * );
/*! \brief Функция возвращает значение опции по ее индексу. */
 dll_export ak_int64 ak_libakrypt_get_option_by_index( const size_t );
/*! \brief Функция устанавливает значение заданной опции. */
 dll_export int ak_libakrypt_set_option( const char * , const ak_int64 );
/*! \brief Функция считывает значения опций библиотеки из файла. */
 dll_export bool_t ak_libakrypt_load_options( void );
/*! \brief Функция выводит текущие значения всех опций библиотеки. */
 dll_export void ak_libakrypt_log_options( void );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Функция устанавливает режим совместимости криптографических преобразований с библиотекой openssl. */
 dll_export int ak_libakrypt_set_openssl_compability( bool_t );
/*! \brief Функция получает домашний каталог библиотеки. */
 dll_export int ak_libakrypt_get_home_path( char * , const size_t );
/*! \brief Функция создает полное имя файла в домашем каталоге библиотеки. */
 dll_export int ak_libakrypt_create_home_filename( char * , const size_t , char * , const int );
/** @} */

/* ----------------------------------------------------------------------------------------------- */
/** \addtogroup oid Идентификаторы криптографических механизмов
 @{ */
/*! \brief Указатель на идентификатор криптографического механизма */
 typedef struct oid *ak_oid;
/*! \brief Функция, возвращающая код ошибки после инициализации объекта (конструктор). */
 typedef int ( ak_function_create_object ) ( ak_pointer );
/*! \brief Функция, возвращающая код ошибки после разрушения объекта (деструктор). */
 typedef int ( ak_function_destroy_object ) ( ak_pointer );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Структура, контролирующая функционирование криптографических объектов библиотеки. */
/*! \details Структура представляет из себя описатель класса, позволяющий создавать и уничтожать
 объекты данного класса, а также вызывать базовые функции чтения и сохранения объектов.            */
/* ----------------------------------------------------------------------------------------------- */
 typedef struct object {
 /*! \brief Размер области памяти для объекта */
  size_t size;
 /*! \brief Конструктор объекта. */
  ak_function_create_object *create;
 /*! \brief Деструктор объекта. */
  ak_function_destroy_object *destroy;
} *ak_object;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип криптографического механизма. */
 typedef enum {
   /*! \brief идентификатор */
     identifier,
   /*! \brief симметричный шифр (блочный алгоритм)  */
     block_cipher,
   /*! \brief симметричный шифр (поточный алгоритм)  */
     stream_cipher,
   /*! \brief схема гибридного шифрования */
     hybrid_cipher,
   /*! \brief функция хеширования */
     hash_function,
   /*! \brief семейство ключевых функций хеширования HMAC */
     hmac_function,
   /*! \brief семейство функций выработки имитовставки согласно ГОСТ Р 34.13-2015. */
     cmac_function,
   /*! \brief семейство функций выработки имитовставки MGM. */
     mgm_function,
   /*! \brief класс всех ключевых функций хеширования (функций вычисления имитовставки) */
     mac_function,
   /*! \brief функция выработки электронной подписи (секретный ключ электронной подписи) */
     sign_function,
   /*! \brief функция проверки электронной подписи (ключ проверки электронной подписи) */
     verify_function,
   /*! \brief генератор случайных и псевдо-случайных последовательностей */
     random_generator,
   /*! \brief механизм идентификаторов криптографических алгоритмов */
     oid_engine,
   /*! \brief неопределенный механизм, может возвращаться как ошибка */
     undefined_engine
} oid_engines_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Режим и параметры использования криптографического механизма. */
 typedef enum {
   /*! \brief собственно криптографический механизм (алгоритм) */
     algorithm,
   /*! \brief данные */
     parameter,
   /*! \brief набор параметров эллиптической кривой в форме Вейерштрасса */
     wcurve_params,
   /*! \brief набор параметров эллиптической кривой в форме Эдвардса */
     ecurve_params,
   /*! \brief набор перестановок */
     kbox_params,
   /*! \brief режим простой замены блочного шифра (ГОСТ Р 34.13-2015, раздел 5.1) */
     ecb,
   /*! \brief режим гаммирования для блочного шифра (ГОСТ Р 34.13-2015, раздел 5.2) */
     counter,
   /*! \brief режим гаммирования для блочного шифра согласно ГОСТ 28147-89 */
     counter_gost,
   /*! \brief режим гаммирования c обратной связью по выходу (ГОСТ Р 34.13-2015, раздел 5.3) */
     ofb,
   /*! \brief режим простой замены с зацеплением (ГОСТ Р 34.13-2015, раздел 5.4) */
     cbc,
   /*! \brief режим гаммирования c обратной связью по шифртексту (ГОСТ Р 34.13-2015, раздел 5.5) */
     cfb,
   /*! \brief режим шифрования XTS для блочного шифра */
     xts,
   /*! \brief режим аутентифицирующего шифрования, согласно Р 1323565.1.028-2019 */
     mgm,
   /*! \brief режим аутентифицирующего шифрования */
     xtsmac,
   /*! \brief режим гаммирования поточного шифра (сложение по модулю 2) */
     xcrypt,
   /*! \brief гаммирование по модулю \f$ 2^8 \f$ поточного шифра */
     a8,
   /*! \brief описатель для типов данных, помещаемых в asn1 дерево */
     descriptor,
   /*! \brief неопределенный режим, может возвращаться как ошибка */
     undefined_mode
} oid_modes_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс для хранения идентификаторов объектов (криптографических механизмов) и их данных. */
/*! OID (Object IDentifier) это уникальная последовательность чисел, разделенных точками.
    OID'ы могут быть присвоены любому криптографическому механизму (алгоритму,
    схеме, протоколу), а также произвольным параметрам этих механизмов.
    Использование OID'в позволяет однозначно определять тип криптографического механизма или
    значения его параметров на этапе выполнения программы, а также
    однозначно связывать данные (как правило ключевые) с алгоритмами, в которых эти данные
    используются.                                                                                  */
/* ----------------------------------------------------------------------------------------------- */
 typedef struct oid {
  /*! \brief Тип криптографического механизма. */
   oid_engines_t engine;
  /*! \brief Режим применения криптографического механизма. */
   oid_modes_t mode;
  /*! \brief Перечень идентификаторов криптографического механизма. */
   const char **id;
  /*! \brief Перечень доступных имен криптографического механизма. */
   const char **name;
  /*! \brief Указатель на данные. */
   ak_pointer data;
  /*! \brief Структура, контролирующая поведение объекта */
   struct object func;
} *ak_oid;

/* ----------------------------------------------------------------------------------------------- */
 #define ak_object_undefined { 0, NULL, NULL }
 #define ak_oid_undefined { undefined_engine, undefined_mode, NULL, NULL, NULL, ak_object_undefined }

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Получение человекочитаемого имени для заданного типа криптографического механизма. */
 dll_export const char *ak_libakrypt_get_engine_name( const oid_engines_t );
/*! \brief Получение человекочитаемого имени режима или параметров криптографического механизма. */
 dll_export const char *ak_libakrypt_get_mode_name( const oid_modes_t );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Создание объекта в оперативной памяти (куче) */
 dll_export ak_pointer ak_oid_new_object( ak_oid );
/*! \brief Удаление объекта из кучи */
 dll_export ak_pointer ak_oid_delete_object( ak_oid , ak_pointer );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Функция возвращает количество идентификаторов библиотеки. */
 dll_export size_t ak_libakrypt_oids_count( void );
/*! \brief Получение OID по его внутреннему индексу. */
 dll_export ak_oid ak_oid_find_by_index( const size_t );
/*! \brief Поиск OID его имени. */
 dll_export ak_oid ak_oid_find_by_name( const char * );
/*! \brief Поиск OID по его идентификатору (строке цифр, разделенных точками). */
 dll_export ak_oid ak_oid_find_by_id( const char * );
/*! \brief Поиск OID по его имени или идентификатору. */
 dll_export ak_oid ak_oid_find_by_ni( const char * );
/*! \brief Поиск OID по указателю на даные */
 dll_export ak_oid ak_oid_find_by_data( ak_const_pointer  );
/*! \brief Поиск OID по типу криптографического механизма. */
 dll_export ak_oid ak_oid_find_by_engine( const oid_engines_t );
/*! \brief Продолжение поиска OID по типу криптографического механизма. */
 dll_export ak_oid ak_oid_findnext_by_engine( const ak_oid, const oid_engines_t );
/*! \brief Проверка соответствия заданного адреса корректному oid. */
 dll_export bool_t ak_oid_check( const ak_oid );
/** @} */

/* ----------------------------------------------------------------------------------------------- */
/** \addtogroup random Генераторы псевдо-случайных чисел
 @{ */
/*! \brief Указатель на класс генератора псевдо-случайных чисел. */
 typedef struct random *ak_random;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Функция, принимающая в качестве аргумента указатель на структуру struct random. */
 typedef int ( ak_function_random )( ak_random );
/*! \brief Функция обработки данных заданного размера. */
 typedef int ( ak_function_random_ptr_const )( ak_random , const ak_pointer, const ssize_t );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс, реализующий произвольный генератор псевдо-случайных чисел.                       */
/* ----------------------------------------------------------------------------------------------- */
 struct random {
  /*! \brief OID генератора псевдо-случайных чисел. */
   ak_oid oid;
  /*! \brief Указатель на функцию выработки следующего внутреннего состояния */
   ak_function_random *next;
  /*! \brief Указатель на функцию инициализации генератора заданным массивом значений */
   ak_function_random_ptr_const *randomize_ptr;
  /*! \brief Указатель на функцию выработки последователности псевдо-случайных байт */
   ak_function_random_ptr_const *random;
  /*! \brief Указатель на функцию освобождения внутреннего состояния */
   ak_function_random *free;
  /*! \brief Объединение, определяющее внутренние данные генератора */
   union {
     /*! \brief Внутреннее состояние линейного конгруэнтного генератора */
       ak_uint64 val;
     /*! \brief Внутреннее состояние xorshift32 генератора */
       ak_uint32 value;
     /*! \brief Файловый дескриптор */
       int fd;
    #ifdef AK_HAVE_WINDOWS_H
     /*! \brief Дескриптор крипто-провайдера */
      HCRYPTPROV handle;
    #endif
     /*! \brief Указатель на произвольную структуру данных. */
       ak_pointer ctx;
   } data;
 };

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация контекста линейного конгруэнтного генератора псевдо-случайных чисел. */
 dll_export int ak_random_create_lcg( ak_random );
 /*! \brief Инициализация контекста генератора, считывающего случайные значения из заданного файла. */
 dll_export int ak_random_create_file( ak_random , const char * );
#if defined(__unix__) || defined(__APPLE__)
/*! \brief Инициализация контекста генератора, считывающего случайные значения из /dev/random. */
 dll_export int ak_random_create_random( ak_random );
/*! \brief Инициализация контекста генератора, считывающего случайные значения из /dev/urandom. */
 dll_export int ak_random_create_urandom( ak_random );
#endif
#ifdef _WIN32
/*! \brief Инициализация контекста, реализующего интерфейс доступа к генератору псевдо-случайных чисел, предоставляемому ОС Windows. */
 dll_export int ak_random_create_winrtl( ak_random );
#endif
/*! \brief Инициализация контекста генератора по заданному OID алгоритма генерации псевдо-случайных чисел. */
 dll_export int ak_random_create_oid( ak_random, ak_oid );
/*! \brief Установка внутреннего состояния генератора псевдо-случайных чисел. */
 dll_export int ak_random_randomize( ak_random , const ak_pointer , const ssize_t );
/*! \brief Выработка псевдо-случайных данных. */
 dll_export int ak_random_ptr( ak_random , const ak_pointer , const ssize_t );
/*! \brief Некриптографическая функция генерации случайного 64-х битного целого числа. */
 dll_export ak_uint64 ak_random_value( void );
/*! \brief Уничтожение данных, хранящихся в полях структуры struct random. */
 int ak_random_destroy( ak_random );
/** @} */

#ifdef __cplusplus
} /* конец extern "C" */
#endif
#endif

/* ----------------------------------------------------------------------------------------------- */
/*                                                                                     libakrypt.h */
/* ----------------------------------------------------------------------------------------------- */
