/* Тестовый пример для получения псевдослучайной последоватлеьность
   генераторов псевдо-случайных чисел mt19937

   test-random01.c
*/

 #include <time.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <libakrypt.h>


/* mt19937 тестирующая функция */
 void  test_function( ak_function_random create )
{
 struct random generator;
 ak_uint32 seed[1] = {5489}; /* seed */
 int i = 0;
 ak_uint32 buffer[9]; /* массив сгенерированных значений по 32 бита */

 /* создаем генератор */
  create( &generator );
  printf( "%s: ", generator.oid->name[0] ); fflush( stdout );

 /* инициализируем seed */
  if( generator.randomize_ptr != NULL )
    ak_random_randomize( &generator, &seed, sizeof( seed ));

 /* теперь вырабатываем необходимый тестовый объем данных */
  ak_random_ptr( &generator, buffer, 9 );

 /* выводим полученный значения */
  for( i = 0; i < 9; i++ )
  {
      printf( "%u ", buffer[i] );
  }
  printf( "  \n" );

  ak_random_destroy( &generator );
}


 int main( void )
{
     int error = EXIT_SUCCESS;

     printf("random generators for libakrypt, version %s\n", ak_libakrypt_version( ));
     if( !ak_libakrypt_create( NULL )) return ak_libakrypt_destroy();

     test_function( ak_random_create_mt19937 );

     ak_libakrypt_destroy();

     return error;
}
