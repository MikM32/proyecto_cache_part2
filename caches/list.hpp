#pragma once

#ifndef LIST_HEADER
#define LIST_HEADER

#include "node.hpp"
#include <iostream>

using namespace std;

template <typename type>
class List{

    // =======================================================================
    //                  Atributos y Metodos Privados
    // =======================================================================
    protected:
        Node<type>* first;
        Node<type>* last;
        int size;

    private:
        // Metodos privados para el metodo sort ( usa el algoritmo quick sort )
        Node<type>* partition(Node<type>* first, Node<type>* last)
        {
            Node<type>* pivot = last;
            Node<type>* i = first->getPrevious();

            Node<type>* cur = first;
            while(cur != NULL)
            {
                if(cur == last || !last)
                {
                    break;
                }

                if(cur->getValue() < pivot->getValue())
                {
                    if(i)
                    {
                        i = i->getNext();
                    }
                    else
                    {
                        i = first;
                    }

                    type aux = i->getValue();
                    i->setValue(cur->getValue());
                    cur->setValue(aux);
                }

                cur = cur->getNext();
            }


            type aux;


            if(i)
            {
                aux = i->getNext()->getValue();
                i->getNext()->setValue(last->getValue());
                last->setValue(aux);

                i = i->getNext();
            }
            else
            {
                i = first;
                aux = i->getValue();
                i->setValue(last->getValue());
                last->setValue(aux);
            }

            return i;

        }

        void quickSort(Node<type>* first, Node<type>* last)
        {
            if(last != NULL && first != last && first != last->getNext())
            {
                Node<type>* part = partition(first, last);

                if(part)
                {
                    quickSort(first, part->getPrevious());
                    quickSort(part->getNext(), last);
                }

            }
        }

        void swap(Node<type>* a, Node<type>* b)
        {
            type aux = a->getValue();
            a->setValue(b->getValue());
            b->setValue(aux);
        }

    // =======================================================================
    //                  Atributos y Metodos Publicos
    // =======================================================================

    public:
        // constructor y desctructor
        List(): first(NULL), last(NULL), size(0) {}
        ~List()
        {
            if(this->size)
            {
                Node<type>* acum = this->first, *basura;
                while(acum != NULL)
                {
                    basura = acum;
                    acum = acum->getNext();

                    delete basura;
                }
            }
        }

        List(const List<type>& list)
        {
            this->size = 0;
            this->first = NULL;
            this->last = NULL;
            this->copy(list);
        }

        void copy(const List<type>& list)
        {
            this->clear();


            Node<type>* acum = list.first;

            for(int i = 0; i < list.size; i++)
            {
                this->insertAtLast(acum->getValue());
                acum = acum->getNext();
            }

            this->size = list.size;

        }

        bool isEmpty()
        {
            return this->size == 0;
        }

        void clear()
        {
            if(this->size)
            {
                while(this->size)
                {
                    this->removeAtFirst();
                }
            }
        }

        // Metodo ordenar
        void sort()
        {
            this->quickSort(this->first, this->last);
        }

        // getter
        int getSize(){return this->size;}

        // metodos para insertar
        void insertAtIndex(int index, type value){
            Node<type> * pointer = NULL;

            // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
            // Indice fuera del rango de la lista
            if(index < 0 || index > this->size){
                cout << endl << "FUNCION: type removeAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: El indice {";
                cout << index << "} es menor {0} o mayor al tamaño de la lista {";
                cout << this->size << "}." << endl;
                cout << "CONSEJO: El indice debe estar entre 0 y {";
                cout << this->size << "}." << endl;
                cout << "         Si desea agregar al inicio o al final de la lista" << endl;
                cout << "         puede usar los metodos 'insertAtFirst(type value)'" << endl;
                cout << "         y 'insertAtLast(type value)'." << endl << endl;

                return;
            }
            // ----------------------------------------------

            // insertar al inicio de las lista
            if(index == 0){this->insertAtFirst(value);}

            // insertar al final de la lista
            else if(index == this->size) {this->insertAtLast(value);}

            // insetar el cualquier otro lugar de la lista
            else
            {
                // Para disminuir la cantidad de iteraciones se
                // buscar desde el ultimo hasta el indice.
                if(index >= (this->size / 2))
                {
                    pointer = this->last;

                    for(int i = index; i < this->size - 1; i++)
                        pointer = pointer->getPrevious();
                }

                // o se buscar desde el primero hasta el indice.
                else
                {
                    pointer = this->first;

                    for(int i = 0; i < index; i++)
                        pointer = pointer->getNext();
                }

                // insertar y conectar nodos
                Node<type> * node = new Node<type>(value);
                node->setNext(pointer);
                node->setPrevious(pointer->getPrevious());

                pointer->getPrevious()->setNext(node);
                pointer->setPrevious(node);
                this->size++;
            }
        }


        void insertAtFirst(type value){
            Node<type> * newNode = new Node<type>(value);
            newNode->setNext(this->first);
            newNode->setPrevious(NULL);

            if(this->size == 0){
                this->first = newNode;
                this->last = newNode;
            }
            else{
                this->first->setPrevious(newNode);
                this->first = newNode;
            }

            this->size++;
        }

        void insertAtLast(type value){
            Node<type> * newNode = new Node<type>(value);
            newNode->setNext(NULL);
            newNode->setPrevious(this->last);

            if(this->size == 0){
                this->first = newNode;
                this->last = newNode;
            }
            else{
                this->last->setNext(newNode);
                this->last = newNode;
            }

            this->size++;
        }

        // metodos para eliminar
        type removeAtIndex(int index){
            Node<type> * pointer = NULL;
            type value = type();

            // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
            // Lista vacia
            if(this->size == 0){
                cout << endl << "FUNCION: type removeAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: Se esta intentando eliminar un valor en una lista vacia." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;

                return type();
            }

            // Indice fuera del rango de la lista
            if(index < 0 || index >= this->size){
                cout << endl << "FUNCION: type removeAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: El indice {";
                cout << index << "} es menor {0} o mayor o igual al tamaño de la lista {";
                cout << this->size << "}." << endl;
                cout << "CONSEJO: El indice debe estar entre 0 y {";
                cout << this->size - 1 << "}." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;

                return type();
            }
            // ----------------------------------------------

            // Para disminuir la cantidad de iteraciones se
            // buscar desde el ultimo hasta el indice.
            if(index >= (this->size / 2))
            {
                pointer = this->last;

                for(int i = index; i < this->size - 1; i++)
                    pointer = pointer->getPrevious();
            }

            // o se buscar desde el primero hasta el indice.
            else
            {
                pointer = this->first;

                for(int i = 0; i < index; i++)
                    pointer = pointer->getNext();
            }

            // Conectar nodos y eliminar en indice
            // SOLO HAY UN NODO
            if(this->size == 1)
            {
                this->first = NULL;
                this->last = NULL;
            }

            // Hay mas de un nodo
            else
            {
                // caso para el primer nodo
                if(index == 0){
                    this->first = this->first->getNext();
                    this->first->setPrevious(NULL);
                }

                // caso para el ultimo nodo
                else if (index == this->size -1)
                {
                    this->last = this->last->getPrevious();
                    this->last->setNext(NULL);
                }

                // caso para algun otro nodo
                else
                {
                    pointer->getPrevious()->setNext(pointer->getNext());
                    pointer->getNext()->setPrevious(pointer->getPrevious());
                }
            }

            // eliminar nodo y guardar valor
            value = pointer->getValue();
            delete pointer;
            this->size--;

            // retornar valor
            return value;
        }

        type removeAtFirst(){
            if(this->size > 0)
            {
                Node<type> * node = this->first;
                type value = node->getValue();

                // cuando queda un solo nodo
                if(this->size == 1){
                    this->first = NULL;
                    this->last = NULL;
                }

                // cuando quedan mas de un nodo
                else {
                    this->first = this->first->getNext();
                    this->first->setPrevious(NULL);
                }

                this->size--;
                delete node;

                return value;
            }

            else
            {
                // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
                cout << endl << "FUNCION: void removeAtFirst()" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: Se intenta eliminar en lista vacia." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;
                // ----------------------------------------------

                return type();
            }
        }

        type removeAtLast(){
            if(this->size > 0)
            {
                Node<type> * node = this->last;
                type value = node->getValue();

                // cuando queda un solo nodo
                if(this->size == 1){
                    this->first = NULL;
                    this->last = NULL;
                }

                // cuando quedan mas de un nodo
                else {
                    this->last = this->last->getPrevious();
                    this->last->setNext(NULL);
                }

                this->size--;
                delete node;

                return value;
            }

            else
            {
                // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
                cout << endl << "FUNCION: void removeAtFirst()" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: Se intenta eliminar en lista vacia." << endl;
                cout << "CONSEJO: La funcion retornara por defecto el valor {-1}" << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;
                // ----------------------------------------------

                return type();
            }
        }

        type getValueAtIndex(int index){
            Node<type> * pointer = NULL;

            // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
            // Lista vacia
            if(this->size == 0){
                cout << endl <<  "FUNCION: type getValueAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: Se esta solicitando un valor en una lista vacia." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;

                return type();
            }

            // Indice fuera del rango de la lista
            if(index < 0 || index >= this->size){
                cout << endl <<  "FUNCION: type getValueAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: El indice {";
                cout << index << "} es menor {0} o mayor o igual al tamaño de la lista {";
                cout << this->size << "}." << endl;
                cout << "CONSEJO: El indice debe estar entre 0 y {";
                cout << this->size - 1 << "}." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;

                return type();
            }
            // ----------------------------------------------

            // Para disminuir la cantidad de iteraciones se
            // buscar desde el ultimo hasta el indice.
            if(index >= (this->size / 2))
            {
                pointer = this->last;

                for(int i = index; i < this->size - 1; i++)
                    pointer = pointer->getPrevious();
            }

            // o se buscar desde el primero hasta el indice.
            else
            {
                pointer = this->first;

                for(int i = 0; i < index; i++)
                    pointer = pointer->getNext();
            }

            return pointer->getValue();
        }

        type getValueAtFirst()
        {
            type result = type();

            if(this->size)
            {
                result = this->first->getValue();
            }

            return result;
        }

        type getValueAtLast()
        {
            type result = type();

            if(this->size)
            {
                result = this->last->getValue();
            }

            return result;
        }

        type * getPointerToValueAtIndex(int index){
            Node<type> * pointer = NULL;

            // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
            // Lista vacia
            if(this->size == 0){
                cout << endl <<  "FUNCION: type getValueAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: Se esta solicitando un valor en una lista vacia." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;

                return new type();
            }

            // Indice fuera del rango de la lista
            if(index < 0 || index >= this->size){
                cout << endl <<  "FUNCION: type getValueAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: El indice {";
                cout << index << "} es menor {0} o mayor o igual al tamaño de la lista {";
                cout << this->size << "}." << endl;
                cout << "CONSEJO: El indice debe estar entre 0 y {";
                cout << this->size - 1 << "}." << endl;
                cout << "RETORNO: La funcion retornara un valor por defecto." << endl;

                return new type();
            }
            // ----------------------------------------------

            // Para disminuir la cantidad de iteraciones se
            // buscar desde el ultimo hasta el indice.
            if(index >= (this->size / 2))
            {
                pointer = this->last;

                for(int i = index; i < this->size - 1; i++)
                    pointer = pointer->getPrevious();
            }

            // o se buscar desde el primero hasta el indice.
            else
            {
                pointer = this->first;

                for(int i = 0; i < index; i++)
                    pointer = pointer->getNext();
            }

            return pointer->getPointerToValue();
        }

        type * getPointerToFirstValue(){return this->first->getPointerToValue();}

        type * getPointerToLastValue(){return this->last->getPointerToValue();}

        // metodos para modificar
        void ModifyValueAtIndex(int index, type value){
            Node<type> * pointer = NULL;

            // ALERTAS PARA DETECCION DE ERRORES EN EL TALLER
            // Lista vacia
            if(this->size == 0){
                cout << endl <<  "FUNCION: type ModifyValueAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: Se esta solicitando un valor en una lista vacia." << endl;
                return;
            }

            // Indice fuera del rango de la lista
            if(index < 0 || index >= this->size){
                cout << endl <<  "FUNCION: type ModifyValueAtIndex(int index)" << endl;
                cout << "CLASE: List<type>" << endl ;
                cout << "ERROR: El indice {";
                cout << index << "} es menor {0} o mayor o igual al tamaño de la lista {";
                cout << this->size << "}." << endl;
                cout << "CONSEJO: El indice debe estar entre 0 y {";
                cout << this->size - 1 << "}." << endl;
                return;
            }
            // ----------------------------------------------

            // Para disminuir la cantidad de iteraciones se
            // buscar desde el ultimo hasta el indice.
            if(index >= (this->size / 2))
            {
                pointer = this->last;

                for(int i = index; i < this->size - 1; i++)
                    pointer = pointer->getPrevious();
            }

            // o se buscar desde el primero hasta el indice.
            else
            {
                pointer = this->first;

                for(int i = 0; i < index; i++)
                    pointer = pointer->getNext();
            }

            pointer->setValue(value);
        }

        // Busqueda lineal
        int getIndexOfValue(type value)
        {
            Node<type>* acum = this->first;
            for(int i=0; i<this->size; i++)
            {
                if(acum->getValue() == value)
                {
                    return i;
                }

                acum = acum->getNext();
            }

            return -1; // devuelve -1 si no encontro nada
        }

        bool contains(type value)
        {
            Node<type>* acum = this->first;
            bool result = false;

            for(int i=0; i<this->size; i++)
            {
                if(acum->getValue() == value)
                    result = true;

                acum = acum->getNext();
            }

            return result;
        }

        int search(type value)
        {
            Node<type>* acum = this->first;
            int index=0;
            while(acum != NULL)
            {
                if(acum->getValue() == value)
                {
                    return index;
                }
                acum = acum->getNext();
                index++;
            }
            index = -1;

            return index;
        }

        // Metodo reversa
        void reverse()
        {
            Node<type>* left = this->first, *right = this->last;

            for(int i=0; i<this->size/2; i++) // Itera hasta la mitad de la lista ya que la recorre desde ambos extremos (inicio y final)
            {
                swap(left, right);

                left = left->getNext();
                right = right->getPrevious();
            }
        }

        // Metodo concatenar: Concatena el contenido de dos listas
        void concat(List<type> list2)
        {
            for(int i=0; i<list2.getSize(); i++)
            {
                this->insertAtLast(list2.getValueAtIndex(i));
            }
        }

        // Metodo substraer: elimina los elementos de la lista que estan en lista2
        void substract(List<type> list2)
        {
            for(int i=0; i<list2.getSize(); i++)
            {
                int index = this->search(list2.getValueAtIndex(i));
                if(index >= 0)
                {
                    this->removeAtIndex(index);
                }
            }
        }

        // Metodo interseccion: devuelve una lista con los elementos que estan en ambas listas
        List<type> intersect(List<type> list2)
        {
            List<type> res;
            for(int i=0; i<list2.getSize(); i++)
            {
                int index = this->search(list2.getValueAtIndex(i));
                if(index >= 0)
                {
                    res.insertAtLast(this->getValueAtIndex(i));
                }
            }

            return res;
        }

    // =======================================================================
    //                  Sobrecarga de Operadores
    // =======================================================================

    List<type> operator+(List<type> const& list2)
    {
        List<type> res(*this);
        res.concat(list2);

        return res;
    }

    List<type> operator-(List<type> const& list2)
    {
        List<type> res(*this);
        res.substract(list2);

        return res;
    }

};
#endif // LIST_HEADER
