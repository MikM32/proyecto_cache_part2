# proyecto_cache_part2
    Integrantes: Miguel Matute y Diego Arias
            C.I: 30.733.549      31.540.642

    Profesor: Jose Canache

    Link del dataset SGY: https://www.kaggle.com/datasets/dengsongmei/marine-oneline

    SO soportados: Windows y Linux.

    Formato de uso:
        Windows:
            caches2.exe [RUTA_DE_ARCHIVO_A_LEER]
        Linux:
            ./caches2 [RUTA_DE_ARCHIVO_A_LEER]
    
    Segunda parte del proyecto de Arquitectura del Computador:

        Cargar un archivo de al menos 100MB a la cache previamente realizada en la parte 1
        e implementarle un algoritmo de prefetching

    Al comparar las velocidades entre la funcion de lectura con mmap y con la que no usa mmap, se pudo ver que con mmap es mas rapido con un tiempo de duracion entre los 1 a 2 minutos mientras que la que no usa mmap tarda mas de 5 minutos
