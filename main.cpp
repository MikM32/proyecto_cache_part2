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

    int cache_sgy(string ruta_arch)
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

        float tasa_aciertos=0;
        int nAciertos=0, nFallos=0;
        LONGLONG aSize=archivoSize.QuadPart, cont=0;

        // Cache completamente asociativa
        CacheCompAsoc cache(64, 4); // 64 vias y 4 palabras por linea; un mayor tamaño aumenta la tasa de aciertos.

        while(cont < aSize)
        {
            //cout << "Procesando: %"<< ((float)cont/aSize)*100 << endl;

            cache.prefetch(*(byteAddr+16)); // obtiene el byte que esta 16 posiciones mas adelante del actual antes de procesarlo
                                                // luego lo guarda en un buffer dentro de la cache.
                                                // este metodo de prefetching se aprovecha de la localidad espacial para aumentar la tasa de aciertos
            if(cache.acceso((*(byteAddr++))))
            {
                nAciertos++;
            }
            else
            {
                nFallos++;
            }

            cont++;
        }

        tasa_aciertos = ((float)nAciertos / aSize)*100;

        UnmapViewOfFile(address); // Desmapea el archivo
        CloseHandle(hMap);
        CloseHandle(archivo);

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

/*
    =============================================
        CODIGO PARA SISTEMAS LINUX Y DERIVADOS
    ==============================================
*/
#elif defined(__linux__) // Si es linux o un derivado

    #include <fcntl.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/mman.h>
    #include <sys/stat.h>

    int cache_sgy(string ruta_arch)
    {
        //================================================
        //==========                        ==============
        //==========    POR IMPLEMENTAR     ==============
        //==========                        ==============
        //================================================
    }


#endif

int main(int argc, const char* argv[])
{
    if(argc > 1)
    {
        cache_sgy(argv[1]);
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
