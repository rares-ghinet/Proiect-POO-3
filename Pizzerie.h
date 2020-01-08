#ifndef PIZZERIE_H
#define PIZZERIE_H

#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
using namespace std;

extern float cont_v;
extern float cont_obj;

class Ingredient
{
protected:
    string nume_ingredient;
    int pret_ingredient;
    int cantitate;
public:
    Ingredient(string nume_ingredient=" ",int pret_ingredient=0,int cantitate=0);
    Ingredient(const Ingredient& Obj);
    ~Ingredient();
    Ingredient& operator=(const Ingredient&);
    friend istream& operator>>(istream&, Ingredient&);
    friend ostream& operator<<(ostream&, const Ingredient&);

    int get_pret()
    {
        return pret_ingredient;
    }

    string get_nume()
    {
        return nume_ingredient;
    }

};

class Pizza_abstracta
{
protected:
    string nume_pizza;
public:
    Pizza_abstracta(string nume_pizza=" ");
    Pizza_abstracta(const Pizza_abstracta& Obj);
    virtual ~Pizza_abstracta();
    Pizza_abstracta& operator=(const Pizza_abstracta&);

    friend istream& operator>>(istream&, Pizza_abstracta&);

    virtual void calcul_pret()=0;
    virtual void afisare(){cout<<nume_pizza<<" ";}
};

class Pizza:public Pizza_abstracta
{
protected:
    int nr_ingrediente;
    list <Ingredient> p;
    static const int manopera=12;
public:
    friend class Ingredient;
    friend int main();
    Pizza(string nume_pizza=" ",int nr_ingrediente=0):Pizza_abstracta(nume_pizza)
    {
        try
        {
          this->nr_ingrediente=nr_ingrediente;
          if(nr_ingrediente<0){throw nr_ingrediente;}
        }

        catch(int nr_ingrediente)
        {
          cout<<"Exceptie: Numarul de ingrediente nu este valid!"<<endl;
          exit(EXIT_FAILURE);
        }
    }
    Pizza(const Pizza& Obj):Pizza_abstracta(Obj)
    {
       this->nr_ingrediente=Obj.nr_ingrediente;
       list<Ingredient> p(Obj.p);
    };
    virtual ~Pizza();
    Pizza& operator=(const Pizza&);

    friend istream& operator>>(istream&, Pizza&);

    string get_nume_pizza()
    {
        return this->nume_pizza;
    }

    virtual void calcul_pret()
    {
        int sum=0;
        list<Ingredient>::iterator it;
        for(it=p.begin();it!=p.end();it++)
        {
            sum=sum+(*it).get_pret();
        }
        cout<<sum+manopera;
    }

    virtual void afisare()
    {
        cout<<"Pizza se numeste: ";
        cout<<nume_pizza<<endl;
        cout<<"Pretul produsului: ";
        calcul_pret();
        cout<<endl;
        cout<<"Ingredientele sunt: ";
        list<Ingredient>::iterator it;
        for(it=p.begin();it!=p.end();++it)
        {
            cout<<(*it).get_nume()<<" ";
        }
    }

};

template<class T>
class Pizza_online:public Pizza
{
private:
    T kilometri;
public:
    Pizza_online(string nume_pizza=" ",int nr_ingrediente=0,T kilometri=0):Pizza(nume_pizza,nr_ingrediente)
    {
        try
        {
          this->kilometri=kilometri;
          if(kilometri<0){throw kilometri;}
        }
        catch(T kilometri)
        {
          cout<<"Exceptie: Numarul de kilometri nu este valid!"<<endl;
          exit(EXIT_FAILURE);
        }
    }
    Pizza_online(const Pizza_online& Obj):Pizza(Obj)
    {
       this->kilometri=Obj.kilometri;
    };
    ~Pizza_online();
    Pizza_online<T>& operator=(const Pizza_online<T>&);

    friend istream& operator>> (istream& in, Pizza_online<T>& Obj)
    {
       in>>Obj.nume_pizza;
       in>>Obj.kilometri;
       in>>Obj.nr_ingrediente;
       Ingredient x;
       for(int q=0;q<Obj.nr_ingrediente;q++)
       {
          in>>x;
          Obj.p.push_back(x);
       }
       return in;
    }

    T get_kilometri()
    {
        return kilometri;
    }

    void calcul_pret()
    {
        T sum=0;
        list<Ingredient>::iterator it;
        for(it=p.begin();it!=p.end();it++)
        {
            sum=sum+(*it).get_pret();
        }
        sum=sum+(sum*(kilometri/10))/20;
        cont_obj=sum+manopera;
        cout<<sum+manopera;
    }
};

template<>
class Pizza_online<int>:public Pizza
{
public:
    void calc_sum_veg()
    {
        if(get_nume_pizza()=="Vegetariana")
        {
            calcul_pret();
            int(cont_v)=int(cont_v)+int(cont_obj);
        }
    }
};

template<>
class Pizza_online<float>:public Pizza
{
public:
    void calc_sum_veg()
    {
        if(get_nume_pizza()=="Vegetariana")
        {
            calcul_pret();
            cont_v=cont_v+cont_obj;
        }
    }
};

#endif
