//se verifica que SO se está utilizando
#ifdef _WIN32
  #include<windows.h>
#else 
  #include <unistd.h>
#endif  
//Dependiendo de donde se implemente el codigo, se limpia la consola.
void scrClean()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}


void waitSec(){
  sleep(1);
}