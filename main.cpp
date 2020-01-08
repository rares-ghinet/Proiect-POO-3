#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include "Pizzerie.h"
#include <tuple>
ifstream f("date.in");
using namespace std;

float cont_v=0;
float cont_obj=0;

template<class T>
class Meniu
{
private:
    int index;
    vector <T> vect;
public:
    Meniu(int index=0);
    ~Meniu(){this->index=0;}
    Meniu& operator+=(const Meniu& Obj){ Obj.index=Obj.index+1;return *this;}

    int get_index()
    {
        return index;
    }
};

int main()
{

    int n,i;
    Pizza t;
    unordered_map<string, list<Ingredient> > h;
    try
    {
      f>>n;

      if(n<=0){throw n;}
    }
    catch(int n)
    {
        cout<<"Exceptie: Nu se pot citi obiecte din fisier!"<<endl;
        exit(EXIT_FAILURE);
    }

    for(i=0;i<n;i++)
    {
        f>>t;
        h.insert( make_pair(t.get_nume_pizza(),t.p) );
    }

    cout<<"--------------------Pizzeria X--------------------"<<endl;
    cout<<endl;
    cout<<"Produsele sunt:"<<endl<<endl;

    /*
    unordered_set<string>::iterator iter;
    for(auto iter=Obiecte.begin();iter!=Obiecte.end();iter++)
    {
        cout<<(*iter)<<endl<<endl;
    }
    */

    unordered_map<string, list<Ingredient> >::iterator itr;

    for(itr=h.begin();itr!=h.end();itr++)
    {
        cout<<(*itr).first<<":"<<endl;

        list<Ingredient>::iterator i;
        for(i=(*itr).second.begin();i!=(*itr).second.end();i++)
        {
            cout<<(*i).get_nume()<<" ";
        }
        cout<<endl<<endl;

    }

    /*
    Pizza_online<float> z;
    cin>>z;
    cout<<cont_v;

    Pizza_online<int> q;
    z=q;
    */

    return 0;
}
