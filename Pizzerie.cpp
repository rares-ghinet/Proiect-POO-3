#include "Pizzerie.h"
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
using namespace std;

///Ingredient

Ingredient::Ingredient(string nume_ingredient,int pret_ingredient,int cantitate)
{
    this->nume_ingredient=nume_ingredient;
    try
    {
     this->pret_ingredient=pret_ingredient;
     this->cantitate=cantitate;

     if(pret_ingredient<0){throw pret_ingredient;}
     if(cantitate<0){throw cantitate;}
    }

    catch(int pret_ingredient)
    {
        cout<<"Exceptie: Date necorespunzatoare->Ingredient"<<endl;
        exit(EXIT_FAILURE);
    }
    catch(int cantitate)
    {
        cout<<"Exceptie: Date necorespunzatoare->Ingredient"<<endl;
        exit(EXIT_FAILURE);
    }

}

Ingredient::Ingredient(const Ingredient& Obj)
{
    this->nume_ingredient=Obj.nume_ingredient;
    this->pret_ingredient=Obj.pret_ingredient;
    this->cantitate=Obj.cantitate;
}

Ingredient::~Ingredient()
{
    this->nume_ingredient=" ";
    this->pret_ingredient=0;
    this->cantitate=0;
}

Ingredient& Ingredient::operator=(const Ingredient& Obj)
{
    if(this==&Obj){return *this;}
    nume_ingredient=Obj.nume_ingredient;
    pret_ingredient=Obj.pret_ingredient;
    cantitate=Obj.cantitate;
    return *this;
}

istream& operator>>(istream& in, Ingredient& Obj)
{
    in>>Obj.nume_ingredient;
    in>>Obj.pret_ingredient;
    in>>Obj.cantitate;

    return in;
}

ostream& operator<<(ostream& out, const Ingredient& Obj)
{
    out<<Obj.nume_ingredient<<" "<<Obj.pret_ingredient<<" "<<Obj.cantitate;
    return out;
}


///Pizza_abstracta
Pizza_abstracta::Pizza_abstracta(string nume_pizza)
{
    this->nume_pizza=nume_pizza;
}

Pizza_abstracta::Pizza_abstracta(const Pizza_abstracta& Obj)
{
    this->nume_pizza=Obj.nume_pizza;
}

Pizza_abstracta::~Pizza_abstracta()
{
    this->nume_pizza=" ";
}

Pizza_abstracta& Pizza_abstracta::operator=(const Pizza_abstracta& Obj)
{
    if(this==&Obj){return *this;}
    nume_pizza=Obj.nume_pizza;
    return *this;
}

istream& operator>>(istream& in, Pizza_abstracta& Obj)
{
    in>>Obj.nume_pizza;
    return in;
}

///Pizza

Pizza::~Pizza()
{
    this->nr_ingrediente=0;
}

Pizza& Pizza::operator=(const Pizza& Obj)
{
    if(this==&Obj){return *this;}
    nr_ingrediente=Obj.nr_ingrediente;
    list<Ingredient> p(Obj.p);
    return *this;
}

istream& operator>>(istream& in, Pizza& Obj)
{
    in>>Obj.nume_pizza;
    in>>Obj.nr_ingrediente;
    Ingredient x;
    for(int q=0;q<Obj.nr_ingrediente;q++)
    {
        in>>x;
        Obj.p.push_back(x);
    }
    return in;
}

///Pizza_online
template<class T>
Pizza_online<T>::~Pizza_online()
{
    this->kilometri=0;
}

template<class T>
Pizza_online<T>& Pizza_online<T>::operator=(const Pizza_online<T>& Obj)
{
    if(this==&Obj){return *this;}
    kilometri=Obj.kilometri;
    list<Ingredient> p(Obj.p);
    return *this;
}

/*
template<class T>
istream& operator>> (istream& in, Pizza_online<T>& Obj)
{
    in>>Obj.nume_pizza;
    in>>Obj.nr_ingrediente;
    Ingredient x;
    for(int q=0;q<Obj.nr_ingrediente;q++)
    {
        in>>x;
        Obj.p.push_back(x);
    }
    in>>Obj.kilometri;
    return in;
}
*/

template class Pizza_online<int>;
template class Pizza_online<float>;





