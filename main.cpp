#include <iostream>
#include <ctime>
#include "segy.h"

#define RUTA "datos.sgy"

using namespace std;

int main(int argc, const char* argv[])
{
    CSegyRead lector;
    unsigned t0, t1;
    t0=clock();
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
    t1 = clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);


    cout << lector.nAciertos << endl;
    cout << "tasa de aciertos: " <<((float)(lector.nAciertos)/(nTrazas*nMuestras))*100 <<"%"<<endl;
    cout << "Tiempo de ejecucion: " << time << endl;


    //cout << lector.GetTraceData(1)[487];

    lector.closeFile();
    t0=clock();
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
    t1 = clock();

    time = (double(t1-t0)/CLOCKS_PER_SEC);

    cout << lector.nAciertos << endl;
    cout << "tasa de aciertos: " <<((float)(lector.nAciertos)/(nTrazas*nMuestras))*100 <<"%"<<endl;
    cout << "Tiempo de ejecucion: " << time << endl;

    //cout << lector.GetTraceData(1)[487];

    lector.closeFile();
    return 0;
}
