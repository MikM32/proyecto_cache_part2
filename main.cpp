#include <iostream>
#include <string>
#include "caches/caches.h"

/*
    Integrantes: Miguel Matute y Diego Arias
            C.I: 30.733.549      31.540.642

    Profesor: Jose Canache

    Segunda parte del proyecto de Arquitectura del Computador:

        Cargar un archivo de al menos 100MB a la cache previamente realizada en la parte 1
        e implementar un algoritmo de prefetching

*/

using namespace std;

/*
    =============================================
            CODIGO PARA SISTEMAS WINDOWS
    ==============================================
*/
#if defined(__WIN32) || defined(_WIN64) // Si la plataforma es windows

    #include<windows.h>

    std::string GetLastErrorAsString()
    {

        DWORD errorMessageID = ::GetLastError();
        if(errorMessageID == 0) {
            return std::string(); //No error message has been recorded
        }

        LPSTR messageBuffer = nullptr;

        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        std::string message(messageBuffer, size);

        LocalFree(messageBuffer);

        return message;
    }

    int cache_mmap_sgy(string ruta_arch)
    {
        LARGE_INTEGER archivoSize;

        // Abre el archivo en modo de lectura
        HANDLE archivo = CreateFile((LPCSTR)ruta_arch.c_str(),
                                    GENERIC_READ,
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    0);

        if(archivo == INVALID_HANDLE_VALUE)
        {
            cerr << "Error al intentar abrir el archivo: "<< GetLastErrorAsString() << endl;
            return -1;
        }

        if(!GetFileSizeEx(archivo, &archivoSize))
        {
            cerr << "Error al intentar abrir el archivo: "<< GetLastErrorAsString() << endl;
            return -1;
        }

        // Mapeo del archivo en memoria
        HANDLE hMap = CreateFileMapping(archivo,
                                        NULL,           // Mapping attributes
                                        PAGE_READONLY,  // Protection flags
                                        0,              // MaximumSizeHigh
                                        0,              // MaximumSizeLow
                                        NULL);
        if (hMap == 0)
        {
            cerr << "Error al mapear el archivo: " << GetLastErrorAsString() << endl;
            CloseHandle(archivo);
            return -1;
        }

        LPVOID address = MapViewOfFile( hMap,
                                        FILE_MAP_READ,         // dwDesiredAccess
                                        0,                     // dwFileOffsetHigh
                                        0,                     // dwFileOffsetLow
                                        0);                    // dwNumberOfBytesToMap

        if (address == NULL) {
            cerr << "Error al mapear el archivo: " << GetLastErrorAsString() << endl;
            CloseHandle(archivo);
            CloseHandle(hMap);
            return -1;
        }

        char* byteAddr = (char*)address;
        uint32* wordAddr = (uint32*)address;

        double tasa_aciertos=0;
        int nAciertos=0, nFallos=0;
        LONGLONG aSize=archivoSize.QuadPart, cont=0;

        // Cache asociativa por conjuntos de 8 vias por conjunto
        CacheConjuntos cache(128, 32, 8); // 128 bloques y 32 palabras por linea; un mayor tamaño aumenta la tasa de aciertos.

        cout << "Procesando un numero total de accesos de: "<< aSize<< endl;
        cout << "......" <<endl;

        while(cont < aSize)
        {
            //cout << "Procesando: %"<< ((float)cont/aSize)*100 << endl;

            cache.prefetch((uint32)wordAddr+16); // obtiene el byte que esta 16 posiciones mas adelante del actual antes de procesarlo
                                                // luego lo guarda en un buffer dentro de la cache.
                                                // este metodo de prefetching se aprovecha de la localidad espacial para aumentar la tasa de aciertos
            if(cache.acceso((uint32)((wordAddr++))))
            {
                nAciertos++;
            }
            else
            {
                nFallos++;
            }

            cont++;
        }

        tasa_aciertos = ((double)nAciertos / aSize)*100;

        UnmapViewOfFile(address); // Desmapea el archivo
        CloseHandle(hMap);
        CloseHandle(archivo);

        cout << "Numero de aciertos: " << nAciertos << endl;
        cout << "Numero de fallos: " << nFallos << endl;
        if(nAciertos > nFallos)
        {
            cout << "El numero de aciertos es mayor al de fallos" << endl;
        }
        else if(nAciertos < nFallos)
        {
            cout << "El numero de aciertos es menor al de fallos" << endl;
        }
        else
        {
            cout << "El numero de aciertos es igual al de fallos" << endl;
        }
        cout << "Porcentaje de aciertos: " << tasa_aciertos <<"%" <<endl;

        return nAciertos;
    }

/*
    =============================================
        CODIGO PARA SISTEMAS LINUX Y DERIVADOS
    ==============================================
*/
#elif defined(__linux__) // Si es linux o un derivado

    #include <fcntl.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/mman.h>

    int cache_mmap_sgy(string ruta_arch)
    {
        int fd;
        char *byteAddr;
        struct stat statbf;

        fd = open( ruta_arch.c_str() , O_RDONLY ); // Obtiene el file descriptor del fichero

        if( fd == -1 ){
            cout << "No se pudo devolver el descriptor de archivo"<<endl;
            exit(1);
        }

        if( fstat( fd , &statbf ) == -1 ){  // Almacena datos de la estructura en statbf
            cout << "Error al intentar obtener informacion de la estructura de datos."<<endl;
            exit(1);
        }

        byteAddr = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);  // Mapea fichero en memoria

        if( byteAddr == MAP_FAILED ){
            cout << "Hubo un error al mapear el fichero en memoria"<<endl; exit(1);
        }

        float tasa_aciertos=0;
        int nAciertos=0, nFallos=0;
        size_t aSize = statbf.st_size, cont=0;

        // Cache asociativa por conjuntos de 8 vias por conjunto
        CacheConjuntos cache(64, 16, 8); // 64 bloques y 16 palabras por linea; un mayor tamaño aumenta la tasa de aciertos.

        cout << "Procesando un numero total de accesos de: "<< aSize<< endl;
        cout << "......" <<endl;

        while(cont < aSize)
        {
            //cout << "Procesando: %"<< ((float)cont/aSize)*100 << endl;

            cache.prefetch((uint32)wordAddr+16); // obtiene el byte que esta 16 posiciones mas adelante del actual antes de procesarlo
                                                // luego lo guarda en un buffer dentro de la cache.
                                                // este metodo de prefetching se aprovecha de la localidad espacial para aumentar la tasa de aciertos
            if(cache.acceso((uint32)((wordAddr++))))
            {
                nAciertos++;
            }
            else
            {
                nFallos++;
            }

            cont++;
        }

        close(fd);  // Cierra File descriptor

        tasa_aciertos = ((float)nAciertos / aSize)*100;

        cout << "Numero total de accesos: "<< aSize<< endl;
        cout << "Numero de aciertos: " << nAciertos << endl;
        cout << "Numero de fallos: " << nFallos << endl;
        if(nAciertos > nFallos)
        {
            cout << "El numero de aciertos es mayor al de fallos" << endl;
        }
        else if(nAciertos < nFallos)
        {
            cout << "El numero de aciertos es menor al de fallos" << endl;
        }
        else
        {
            cout << "El numero de aciertos es igual al de fallos" << endl;
        }
        cout << "Porcentaje de aciertos: " << tasa_aciertos <<"%" <<endl;

        return nAciertos;
    }


#endif

int main(int argc, const char* argv[])
{
    if(argc > 1)
    {
        cache_mmap_sgy(argv[1]);
    }
    else
    {
        cout << "\tFORMATO DE USO:"<< endl<<endl;
        #if defined(__WIN32) || defined(_WIN64)
        cout << "cache2.exe     [RUTA_DEL_ARCHIVO_A_LEER]"<<endl;
        #elif defined(__linux__)
        cout << "./cache2       [RUTA_DEL_ARCHIVO_A_LEER]"<<endl;
        #endif // defined

    }

    return 0;
}
