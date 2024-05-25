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

class CampoCache
{
    private:
        bool validez = false;
        int dato;
        int etiqueta = 0;
        int tiempo = -1;
    public:

        CampoCache()
        {

        }
        //getters


        int getTiempo()
        {
            return this->tiempo;
        }
        bool getValidez()
        {
            return this->validez;
        }

        int getEtiqueta()
        {
            return this->etiqueta;
        }

        int getDato()
        {
            return this->dato;
        }

        //setters

        void setDato(int d)
        {
            this->dato = d;
        }
        void setTiempo(int t)
        {
            this->tiempo = t;
        }
        void setValidez(bool val)
        {
            this->validez = val;
        }
        void setEtiqueta(int et)
        {
            this->etiqueta = et;
        }

		void cambiar(bool val, int et, int tmp)
		{
			this->setValidez(val);
			this->setEtiqueta(et);
			this->setTiempo(tmp);
		}
};

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
        vector<CampoCache> cache;

    public:

        CacheDirecta()
        {

        }

        CacheDirecta(int nBloques, int tamBloques)
        {
            this->nBloques = nBloques;
            this->tamBloques = tamBloques;
            this->cache = vector<CampoCache>(nBloques, CampoCache());
        }

        bool acceso(int direccion)
        {
            int etiqueta;
            int indice;
            int despBloque = log2(this->tamBloques);

            etiqueta = direccion >> despBloque;
            indice = etiqueta % this->nBloques;
            if(cache[indice].getEtiqueta() == etiqueta && cache[indice].getValidez()) //Si el bit de validez es verdadero y las etiquetas coinciden
            {

                return true;
            }
            else
            {
                cache[indice].setEtiqueta(etiqueta);
                cache[indice].setValidez(true);     // Pone a verdadero el bit de validez

            }
            return false;
        }
};


class CacheConjuntos : Cache
{
    private:
        List<List<LineaCache>*> cache;
        int nVias;
	LineaCache buffer; // Para el prefetch
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

        bool acceso(int direccion)
        {
            int despBloque = log2(this->tamBloques);
            int etiqueta = direccion << despBloque;
            int indiceConjunto = etiqueta % this->nVias;
            bool flag_acierto = false;

            LineaCache linea;
            linea.etiqueta=etiqueta;
            linea.validez=true;

            int ind = this->cache.getValueAtIndex(indiceConjunto)->search(linea);
            if(ind < 0)
            {
                if(!this->cache.getValueAtIndex(indiceConjunto)->isEmpty())
                {
                    this->cache.getValueAtIndex(indiceConjunto)->removeAtFirst();
                }

                this->cache.getValueAtIndex(indiceConjunto)->insertAtLast(linea);
            }
            else
            {
                flag_acierto=true;
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
        LineaCache buffer; // Para el prefetch
        int nVias;
        int curVias=1; // contador de vias validas o utilizadas

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

#endif // CACHES_H_INCLUDED
