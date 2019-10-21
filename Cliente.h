#ifndef PROJ1_CLIENTE_H
#define PROJ1_CLIENTE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> splitIds(string ids);

class Cliente {
    string nome;
    int nif;
    vector<int> ids;
public:
    Cliente(){}
    Cliente(string n):nome(n){}
    void setNome(string n) {
        for (int i = 0; i < n.length(); i++)
            if (!isalpha(n[i]) && n[i] != ' ')
                throw logic_error("Erro ao criar este cliente no atributo Nome!");
        nome = n;
    }
    void setNif(string n) {nif = stoi(n);}
    void setIds(string ids){
        if(ids != "-")
            this->ids = splitIds(ids);
    }
    string getNome() const{return nome;}
    int getNif() const{return nif;}
    vector<int> getIds() const{return ids;}
    void assocHabit(int id){ids.push_back(id);}
    void desassociarHabit(int id){
        int ind = 0;
        for(int i = 0; i < ids.size(); i++) {
            if (ids[i] == id)
                ind = i;
        }
        ids.erase(ids.begin() + ind);
    }
    bool existe(int id){return binary_search(ids.begin(), ids.end(), id);}
    int pagarMen(){
        string aux;
        cout << "Introduza o ID do pacote: ", getline(cin, aux);
        vector<int>::iterator it = find(ids.begin(), ids.end(), stoi(aux));
        if(it == ids.end())
            throw logic_error("O cliente " + nome + " nao possui nenhuma habitacao com o ID: " + aux);
        return *it;
    }
    void imprime() const{
        cout << "Nome......................: " << nome
             << "\nNif.......................: " << nif
             << "\nHabitacoes Adquiridas(Ids): ";
        if(ids.size() == 0)
            cout << "-";
        else {
            for (int i = 0; i < ids.size(); i++)
                if(i != ids.size() - 1)
                    cout << ids[i] << "; ";
                else
                    cout << ids[i];
        }
    }
    bool operator==(const Cliente &c){
        return nome == c.nome;
    }
};


#endif //PROJ1_CLIENTE_H
