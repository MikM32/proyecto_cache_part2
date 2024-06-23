#ifndef MAP_FILE_H_INCLUDED
#define MAP_FILE_H_INCLUDED

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

    char* getMmapPtr(const char* ruta_arch)
    {
        LARGE_INTEGER archivoSize;

        // Abre el archivo en modo de lectura
        HANDLE archivo = CreateFile((LPCSTR)ruta_arch,
                                    GENERIC_READ,
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL,
                                    0);

        if(archivo == INVALID_HANDLE_VALUE)
        {
            cerr << "Error al intentar abrir el archivo: "<< GetLastErrorAsString() << endl;
            return NULL;
        }

        if(!GetFileSizeEx(archivo, &archivoSize))
        {
            cerr << "Error al intentar abrir el archivo: "<< GetLastErrorAsString() << endl;
            return NULL;
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
            return NULL;
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
            return NULL;
        }

        char* byteAddr = (char*)address;

        return byteAddr;


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

    char* getMmapPtr(const char* ruta_arch)
    {
        int fd;
        char *byteAddr;
        struct stat statbf;

        (FILE*)fd = fopen(ruta_arch, O_RDONLY);

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

        return byteAddr;

    }


#endif

#endif // MAP_FILE_H_INCLUDED
