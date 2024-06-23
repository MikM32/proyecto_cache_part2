#include <iostream>
#include "segy.h"

#define RUTA "C:\\Users\\Ines\\Documents\\DarKM32\\caches2\\datos.sgy"

using namespace std;

int main()
{
    CSegyRead lector;
    cout << "Lectura sin mmap"<<endl;
    if(lector.OpenFile(RUTA))
    {
        cout << "ok" <<endl;
    }


    int nTrazas = lector.getTotalTraceNumber();
    int nMuestras = lector.getSamplesNumber();
    for(int i=0; i<nTrazas; i++)
    {
        lector.GetTraceData(i);
    }

    cout << lector.nAciertos << endl;
    cout << "tasa de aciertos: " <<((float)(lector.nAciertos)/(nTrazas*nMuestras))*100 <<"%"<<endl;


    //cout << lector.GetTraceData(1)[487];

    lector.closeFile();

    cout << "Lectura con mmap"<<endl;
    if(lector.OpenFile(RUTA, true))
    {
        cout << "ok" <<endl;
    }


    nTrazas = lector.getTotalTraceNumber();
    nMuestras = lector.getSamplesNumber();

    for(int i=0; i<nTrazas; i++)
    {
        lector.GetTraceData(i);
    }

    cout << lector.nAciertos << endl;
    cout << "tasa de aciertos: " <<((float)(lector.nAciertos)/(nTrazas*nMuestras))*100 <<"%"<<endl;

    //cout << lector.GetTraceData(1)[487];

    lector.closeFile();
    return 0;
}
