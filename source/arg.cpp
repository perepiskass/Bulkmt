#include "version_lib.h"
#include <iostream>
#include <string>

/**
 * @brief Функция для проверки введенных аргументов программы.
 */
size_t checkArg(int argc,char** argv)
{

    if ( argc > 1)
    {
        std::string version = "-version";
        if (argv[1] == version)
        {
            std::cout << "version: " << version_major()<< '.'<< version_minor() << '.' << version_patch() << std::endl;
            exit(0);
        }
        else
        {
            if (atoi(argv[1]) > 0)  return atoi(argv[1]);
            else  
            {

                std::cout << "Enter correct bulk size"<< std::endl;
                exit(0);
            }
        }
    }
    else 
    {
      std::cout << "Enter bulk size or -version" << std::endl;
      exit(0);
    }
    
}