#include <bits/stdc++.h>
using namespace std;
const int ROZMIAR_STOSU=1e4;
const int BLAD=INT_MAX;
enum tryb{STATYCZNY,DYNAMICZNY,LISTA};
const int wybrany_tryb=STATYCZNY;
const int ILE_LICZB=10;
class stos_statyczny{
    private:
        int zawartosc[ROZMIAR_STOSU];
        int indeks_szczytu;
    public:
        void init(){
            indeks_szczytu=-1;
        }
        void destroy(){
            indeks_szczytu=-1;
        }
        bool empty(){
            if(indeks_szczytu==-1)return true;
            return false;
        }
        bool full(){
            if(indeks_szczytu==ROZMIAR_STOSU-1)return true;
            return false;
        }
        void push(int dokladana_liczba){
            if(full()){
                cerr<<"Brakuje miejsca na stosie, aby dodac element\n";
                return;
            }
            ++indeks_szczytu;
            zawartosc[indeks_szczytu]=dokladana_liczba;
        }
        void pop(){
            if(empty()){
                cerr<<"Nie mozna usunac elementu, poniewaz stos jest pusty\n";
                return;
            }
            --indeks_szczytu;
        }
        int top(){
            if(empty()){
                cerr<<"Nie mozna pobrac elementu, poniewaz stos jest pusty\n";
                return BLAD;
            }
            return zawartosc[indeks_szczytu];
        }
};
class stos_dynamiczny{
    private:
        int* zawartosc;
        int indeks_szczytu;
        int rozmiar;
    public:
        void init(int rozmiar_stosu){
            indeks_szczytu=-1;
            zawartosc=new int[rozmiar_stosu];
            rozmiar=rozmiar_stosu;
        }
        void destroy(){
            indeks_szczytu=-1;
            delete [] zawartosc;
        }
        bool empty(){
            if(indeks_szczytu==-1)return true;
            return false;
        }
        bool full(){
            if(indeks_szczytu==rozmiar-1)return true;
            return false;
        }
        void push(int dokladana_liczba){
            if(full()){
                cerr<<"Brakuje miejsca na stosie, aby dodac element\n";
                return;
            }
            ++indeks_szczytu;
            zawartosc[indeks_szczytu]=dokladana_liczba;
        }
        void pop(){
            if(empty()){
                cerr<<"Nie mozna usunac elementu, poniewaz stos jest pusty\n";
                return;
            }
            --indeks_szczytu;
        }
        int top(){
            if(empty()){
                cerr<<"Nie mozna pobrac elementu, poniewaz stos jest pusty\n";
                return BLAD;
            }
            return zawartosc[indeks_szczytu];
        }
};
class stos_lista{
    private:
        struct lista{
            int aktualna_liczba;
            struct lista* poprzedni;
        };
        int aktualny_rozmiar;
        int max_rozmiar;
        struct lista* head;
    public:
        void init(int rozmiar_stosu){
            aktualny_rozmiar=0;
            max_rozmiar=rozmiar_stosu;
            head=NULL;
        }
        bool empty(){
            if(head==NULL)return true;
            return false;
        }
        bool full(){
            if(aktualny_rozmiar==max_rozmiar)return true;
            return false;
        }
        void push(int dokladana_liczba){
            if(full()){
                cerr<<"Brakuje miejsca na stosie, aby dodac element\n";
                return;
            }
            else{
                lista* nowy=new lista;
                nowy->aktualna_liczba=dokladana_liczba;
                nowy->poprzedni=head;
                ++aktualny_rozmiar;
                head=nowy;
            }
        }
        void pop(){
            if(empty()){
                cerr<<"Nie mozna usunac elementu, poniewaz stos jest pusty\n";
                return;
            }
            lista* tmp=head->poprzedni;
            delete head;
            head=tmp;
            --aktualny_rozmiar;
        }
        void destroy(){
            while(!empty()){
                pop();
            }
        }
        int top(){
            if(empty()){
                cerr<<"Nie mozna pobrac elementu, poniewaz stos jest pusty\n";
                return BLAD;
            }
            return head->aktualna_liczba;
        }

};

template<typename T>
void wczytaj_dane(T& st){
    for(int i=0;i<ILE_LICZB;++i){
        int x;
        cin>>x;
        st.push(x);
    }
}
template<typename T>
void odwroc_i_wyswietl(T& pierwszy, T& drugi,bool czy_wyswietlac){
    while(!pierwszy.empty()){
        int wierzch=pierwszy.top();
        if(czy_wyswietlac)cout<<wierzch<<" ";
        drugi.push(wierzch);
        pierwszy.pop();
    }
}
void program_statyczny(){
    stos_statyczny pierwszy,drugi;
    pierwszy.init();
    drugi.init();
    wczytaj_dane(pierwszy);
    odwroc_i_wyswietl(pierwszy,drugi,false);
    odwroc_i_wyswietl(drugi,pierwszy,true);
    pierwszy.destroy();
    drugi.destroy();
}
void program_dynamiczny(){
    stos_dynamiczny pierwszy,drugi;
    pierwszy.init(ILE_LICZB);
    drugi.init(ILE_LICZB);
    wczytaj_dane(pierwszy);
    odwroc_i_wyswietl(pierwszy,drugi,false);
    odwroc_i_wyswietl(drugi,pierwszy,true);
    pierwszy.destroy();
    drugi.destroy();
}
void program_lista(){
    stos_lista pierwszy,drugi;
    pierwszy.init(ILE_LICZB);
    drugi.init(ILE_LICZB);
    wczytaj_dane(pierwszy);
    odwroc_i_wyswietl(pierwszy,drugi,false);
    odwroc_i_wyswietl(drugi,pierwszy,true);
    pierwszy.destroy();
    drugi.destroy();
}
int main(){
    srand(time(NULL));
    cout<<"Podaj 10 liczb\n";
    switch(wybrany_tryb){
        case STATYCZNY:program_statyczny();break;
        case DYNAMICZNY:program_dynamiczny();break;
        case LISTA:program_lista();break;
    }
    return 0;
}
