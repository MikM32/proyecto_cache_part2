#ifndef CACHES_H_INCLUDED
#define CACHES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include "list.hpp"

using namespace std;

typedef unsigned int uint32;

class LineaCache
{
    public:

        bool validez=false;
        uint32 etiqueta;

        bool operator==(LineaCache& l2)
        {
            return (this->etiqueta == l2.etiqueta) && (this->validez == l2.validez);
        }
};

class Cache
{
    protected:
        int nBloques;
        int tamBloques;
        int contador_tiempo=0;
        LineaCache buffer;

    public:

        int getBloquesNum()
        {
            return this->nBloques;
        }

        int getTamBloques()
        {
            return this->tamBloques;
        }

        virtual bool acceso(int direccion)
        {
            cout << "No hace nada"<<endl;
            return false;
        }

};

class CacheDirecta : Cache
{
    private:
        LineaCache* cache;

    public:

        CacheDirecta()
        {

        }

        CacheDirecta(int nBloques, int tamBloques)
        {
            this->nBloques = nBloques;
            this->tamBloques = tamBloques;
            this->cache = new LineaCache[nBloques];
        }

        bool acceso(uint32 direccion)
        {
            uint32 etiqueta;
            uint32 indice;
            uint32 despBloque = log2(this->tamBloques);

            etiqueta = direccion >> despBloque;
            indice = etiqueta % this->nBloques;

            LineaCache linea;
            linea.etiqueta = etiqueta;
            linea.validez = true; //Si el bit de validez es verdadero y las etiquetas coinciden

            if(this->buffer == linea)
            {
                return true;
            }
            else
            {
                if(cache[indice] == linea)
                {
                    return true;
                }
                else
                {
                    cache[indice] = linea;
                }
            }

            return false;
        }

        void prefetch(uint32 direccion)
        {
            uint32 despBloque = log2(this->tamBloques);
            uint32 etiqueta = direccion >> despBloque;

            this->buffer.etiqueta = etiqueta;
            this->buffer.validez = true;
        }
};


class CacheConjuntos : Cache
{
    private:
        List<List<LineaCache>*> cache;
        int nVias;
        int tamConjuntos;

    public:

        CacheConjuntos()
        {

        }

        CacheConjuntos(int numBloques, int tamBloques, int tamConjuntos)
        {

            this->nVias = numBloques / tamConjuntos;
            this->nBloques = numBloques;
            this->tamBloques = tamBloques;
            this->tamConjuntos = tamConjuntos;
            for(int i=0; i< nVias; i++)
            {
                cache.insertAtLast(new List<LineaCache>());
            }
        }

        bool acceso(uint32 direccion)
        {
            direccion = direccion / this->tamBloques;
            uint32 despBloque = log2(this->tamBloques);
            uint32 etiqueta = direccion << despBloque;
            uint32 indiceConjunto = etiqueta % this->nVias;
            bool flag_acierto = false;

            LineaCache linea;
            linea.etiqueta=etiqueta;
            linea.validez=true;



            if(this->buffer == linea)
            {
                flag_acierto = true;
            }
            else
            {
                int ind = this->cache.getValueAtIndex(indiceConjunto)->search(linea);
                if(ind < 0)
                {
                    if(this->cache.getValueAtIndex(indiceConjunto)->getSize() == this->nVias)
                    {
                        this->cache.getValueAtIndex(indiceConjunto)->removeAtFirst();
                    }

                    this->cache.getValueAtIndex(indiceConjunto)->insertAtLast(linea);
                }
                else
                {
                    LineaCache bf  = this->cache.getValueAtIndex(indiceConjunto)->getValueAtIndex(ind);
                    this->cache.getValueAtIndex(indiceConjunto)->removeAtIndex(ind);
                    this->cache.getValueAtIndex(indiceConjunto)->insertAtLast(bf);
                    flag_acierto=true;
                }
            }

            return flag_acierto;


        }

        void prefetch(uint32 direccion)
        {
            int despBloque = log2(this->tamBloques);
            int etiqueta = direccion >> despBloque;

            this->buffer.etiqueta = etiqueta;
            this->buffer.validez = true;
        }

};

class CacheCompAsoc : Cache
{
    private:
        List<LineaCache> cache;
        int nVias;
        int curVias=1;

    public:

        CacheCompAsoc()
        {

        }

        CacheCompAsoc(int nVias, int tamBloques)
        {
            this->nVias = nVias;
            this->tamBloques = tamBloques;
        }

        bool acceso(uint32 direccion)
        {
            int despBloque = log2(this->tamBloques);
            uint32 etiqueta = direccion >> despBloque;
            bool flag_acierto = false;

            LineaCache linea;
            linea.etiqueta=etiqueta;
            linea.validez=true;

            if(linea == this->buffer)
            {
                flag_acierto=true;
            }
            else
            {
                int ind = this->cache.search(linea);
                if(ind < 0)
                {
                    if(this->curVias == this->nVias)
                    {
                        this->cache.removeAtFirst();
                        this->cache.insertAtLast(linea);
                    }
                    else
                    {
                        this->curVias++;
                        this->cache.insertAtLast(linea);
                    }
                }
                else
                {
                    LineaCache bf = this->cache.getValueAtIndex(ind);
                    this->cache.removeAtIndex(ind);
                    this->cache.insertAtLast(bf);
                    flag_acierto=true;
                }
            }



            return flag_acierto;
        }

        void prefetch(int direccion)
        {
            int despBloque = log2(this->tamBloques);
            int etiqueta = direccion >> despBloque;

            this->buffer.etiqueta = etiqueta;
            this->buffer.validez = true;
        }


};

#endif // CACHES_H_INCLUDED
