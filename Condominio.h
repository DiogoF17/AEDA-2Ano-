#ifndef PROJ1_CONDOMINIO_H
#define PROJ1_CONDOMINIO_H

#include <vector>
#include "Cliente.h"
#include "Habitacao.h"
#include <iostream>
#include <algorithm>

using namespace std;

int Opcao(bool zero, int num);

class Condominio {
    vector<Habitacao*> habitacoes;
    vector<Cliente> clientes;
    //std::vector<Servicos> servicos;
public:
    string nomeFicheiro;
    bool update;
    Condominio(){}
    ~Condominio(){
        for(vector<Habitacao*>::iterator it = habitacoes.begin(); it != habitacoes.end(); it++)
            delete *it;
    }
    void imprimeTodosClientes() const{
        for(int i = 0; i < clientes.size(); i++) {
            clientes[i].imprime();
            cout << endl << endl;
        }
    }
    void imprimeCliente() const{
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o nome do Cliente: ", getline(cin, aux);
        int ind = -1;
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].getNome() == aux)
                ind = i;
        }
        if(ind == -1)
            throw logic_error("Nao existe nenhum cliente com o nome: "  + aux);
        else
            clientes[ind].imprime();
    }
    void verTodosHabitacoes() const{
        for(int i = 0; i < habitacoes.size(); i++)
            habitacoes[i]->imprime();
    }
    void verHabitacaoEsp()const{
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o ID do pacote: ", getline(cin, aux);
        int ind=-1;
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == stoi(aux)){
                ind = i;
                break;
            }
        }
        if(ind == -1)
            throw logic_error("Nao existe nenhuma  habitacao com o ID: "  + aux);
        else{
            cout << endl;
            habitacoes[ind]->imprime();
        }
    }
    void readFile();
    void writeFile();
    void addCliente(Cliente &c){
        clientes.push_back(c);
        cout << "\nCliente adicionado com sucesso!";
    }
    void alterarCliente(){
        imprimeTodosClientes();
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o nome do cliente: ", getline(cin, aux);
        int ind=-1;
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].getNome() == aux){
                ind = i;
                break;
            }
        }
        if(ind == -1)
            throw logic_error("Nao existe nenhum cliente com o nome: "  + aux);
        std::cout << "\n\t\tPARAMETRO A ALTERAR\n\n"
                  << "1) Nome;\n2) Nif;\n3) Ids;";
        int param = Opcao(false, 3);
        cin.ignore(1000, '\n');
        switch (param) {
            case 1:
                std::cout << "\nIntroduza o novo nome: ", getline(std::cin, aux);
                clientes[ind].setNome(aux);
                break;
            case 2:
                std::cout << "\nIntroduza o novo NIF: ", getline(std::cin, aux);
                verifyNif(aux);
                clientes[ind].setNif(aux);
                break;
            case 3:
                std::cout << "\nIntroduza os novos IDS('-' para nenhum): ", getline(std::cin, aux);
                vector<int> ids = splitIds(aux);
                bool existe;
                for(int i = 0; i < ids.size(); i++){
                    existe = false;
                    for(int j = 0; j < habitacoes.size(); j++){
                        if(ids[i] == habitacoes[j]->getId()) {
                            existe = true;
                            break;
                        }
                    }
                    if(existe == false)
                        throw logic_error("Nao existe nenhuma habitacao com o ID: " + ids[i]);
                }
                clientes[ind].setIds(aux);
                break;
        }
        cout << "\nHabitacao alterada com sucesso!";
    }
    void removerCliente(){
        imprimeTodosClientes();
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o nome do Cliente: ", getline(cin, aux);
        Cliente c(aux);
        vector<Cliente>::iterator it = find(clientes.begin(), clientes.end(), c);
        if(it == clientes.end())
            throw logic_error("Nao existe nenhum cliente com o nome: "  + aux);
        clientes.erase(it);
        cout << "\nCliente removido com sucesso!";
    }
    void associarHabit(){
        imprimeTodosClientes();
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o nome do Cliente: ", getline(cin, aux);
        Cliente c(aux);
        vector<Cliente>::iterator it = find(clientes.begin(), clientes.end(), c);
        if(it == clientes.end())
            throw logic_error("Nao existe nenhum cliente com o nome: "  + aux);
        vector<int> disp;
        cout << endl;
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getDisponivel() == true) {
                disp.push_back(habitacoes[i]->getId());
                habitacoes[i]->imprime();
            }
        }
        string id;
        cout << "Introduza o ID do pacote que pretende associar: ", getline(cin, id);
        bool existe = binary_search(disp.begin(), disp.end(), stoi(id));
        if(existe == false)
            throw logic_error("Nao existe atualmente nenhuma habitacao disponivel com o ID " + id + " para adquirir!");
        it->assocHabit(stoi(id));
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == stoi(id)){
                habitacoes[i]->setDisponibilidade("nao");
            }
        }
        cout << "Habitacao adquirida com sucesso!";
    }
    void desassociarHabit(){
        imprimeTodosClientes();
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o nome do Cliente: ", getline(cin, aux);
        Cliente c(aux);
        vector<Cliente>::iterator it = find(clientes.begin(), clientes.end(), c);
        if(it == clientes.end())
            throw logic_error("Nao existe nenhum cliente com o nome: "  + aux);
        vector<int> ids = it->getIds();
        cout << endl;
        for(int i = 0; i < habitacoes.size(); i++){
            if(it->existe(habitacoes[i]->getId()))
                habitacoes[i]->imprime();
        }
        string id;
        cout << "Introduza o ID da Habitacao: ", getline(cin, id);
        bool existe = it->existe(stoi(id));
        if(existe == false)
            throw logic_error("Nao existe nenhum pacote com o ID " + id + " para desassociar!");
        it->desassociarHabit(stoi(id));
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == stoi(id)) {
                habitacoes[i]->setDisponibilidade("sim");
                break;
            }
        }
        cout << "\nHabitacao desassociada com sucesso!";
    }
    void addHabitacao(Habitacao *h){
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == h->getId())
                throw logic_error("Ja existe um pacote com o ID: " + h->getId());
        }
        habitacoes.push_back(h);
        cout << "\nHabitacao adicionada com sucesso!";
    }
    void alterarHabitacao(){
        verTodosHabitacoes();
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o ID do pacote: ", getline(cin, aux);
        int ind=-1;
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == stoi(aux)){
                ind = i;
                break;
            }
        }
        if(ind == -1)
            throw logic_error("Nao existe nenhuma  habitacao com o ID: "  + aux);
        std::cout << "\n\t\tPARAMETRO A ALTERAR\n\n"
                  << "1) ID;\n2) Morada;\n3) Valor Base;\n4) Area Habitacional;";
        if(habitacoes[ind]->getTipo() == "Vivenda")
            std::cout << "\n5) Area Exterior;\n6) Piscina;\n7) Pago;\n8) Disponivel;";
        else
            std::cout << "\n5) Piso;\n6) Tipologia;\n7) Pago;\n8) Disponivel;";
        int param = Opcao(false, 8);
        cin.ignore(1000, '\n');
        if (habitacoes[ind]->getTipo() == "Vivenda") {
            Vivenda* v = dynamic_cast<Vivenda*> (habitacoes[ind]);
            switch (param) {
                case 1:
                    std::cout << "Introduza o novo ID: ", getline(std::cin, aux);
                    verifyId(stoi(aux));
                    (*v).setId(aux);
                    break;
                case 2:
                    std::cout << "\nIntroduza a nova Morada: ", getline(std::cin, aux);
                    (*v).setMorada(aux);
                    break;
                case 3:
                    std::cout << "Introduza o novo Valor Base: ", getline(std::cin, aux);
                    (*v).setValorBase(aux);
                    break;
                case 4:
                    std::cout << "Introduza a nova Area Habitacional: ", getline(std::cin, aux);
                    (*v).setAreaHabitacional(aux);
                    break;
                case 5:
                    std::cout << "Introduza a nova Area Exterior: ", getline(std::cin, aux);
                    (*v).setAreaExterior(aux);
                    break;
                case 6:
                    std::cout << "Introduza tem Piscina?('sim'\\'nao'): ", getline(std::cin, aux);
                    (*v).setPiscina(aux);
                    break;
                case 7:
                    std::cout << "Introduza esta Pago?('sim'\\'nao'): ", getline(std::cin, aux);
                    (*v).setPago(aux);
                    break;
                case 8:
                    std::cout << "Introduza esta Disponivel('sim'\\'nao'): ", getline(std::cin, aux);
                    (*v).setDisponibilidade(aux);
                    break;
            }
        }
        else {
            Apartamento* a = dynamic_cast<Apartamento*> (habitacoes[ind]);
            switch (param) {
                case 1:
                    std::cout << "Introduza o novo ID: ", getline(std::cin, aux);
                    verifyId(stoi(aux));
                    (*a).setId(aux);
                    break;
                case 2:
                    std::cout << "\nIntroduza a nova Morada: ", getline(std::cin, aux);
                    (*a).setMorada(aux);
                    break;
                case 3:
                    std::cout << "Introduza o novo Valor Base: ", getline(std::cin, aux);
                    (*a).setValorBase(aux);
                    break;
                case 4:
                    std::cout << "Introduza a nova Area Habitacional: ", getline(std::cin, aux);
                    (*a).setAreaHabitacional(aux);
                    break;
                case 5:
                    std::cout << "Introduza o novo Piso: ", getline(std::cin, aux);
                    (*a).setPiso(aux);
                    break;
                case 6:
                    std::cout << "Introduza a nova Tipologia: ", getline(std::cin, aux);
                    (*a).setTipologia(aux);
                    break;
                case 7:
                    std::cout << "Introduza esta Pago?('sim'\\'nao'): ", getline(std::cin, aux);
                    (*a).setPago(aux);
                    break;
                case 8:
                    std::cout << "Introduza esta Disponivel('sim'\\'nao'): ", getline(std::cin, aux);
                    (*a).setDisponibilidade(aux);
                    break;
            }
        }
        cout << "\nHabitacao alterada com sucesso!";
    }
    void removerHabitacao(){
        verTodosHabitacoes();
        string aux;
        int onde = -1;
        cin.ignore(1000, '\n');
        cout << "Introduza o ID do pacote: ", getline(cin, aux);
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == stoi(aux)){
                onde = i;
                break;
            }
        }
        if(onde == -1)
            throw logic_error("Nao existe nenhum pacote com o ID: " + aux);
        habitacoes.erase(habitacoes.begin() + onde);
        cout << "\nHabitacao removida com sucesso!";
    }
    void verifyId(int id){
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == id)
                throw logic_error("Ja existe uma habitacao com o ID: " + id);
        }
    }
    void verifyNif(string nif){
        for (int i = 0; i < nif.length(); i++)
            if (!isdigit(nif[i]) && nif[i] != '.')
                throw logic_error("Erro ao no atributo Nif!");
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].getNif() == stoi(nif))
                throw logic_error("Ja existe um cliente com esse NIF: " + nif);
        }
    }
    vector<Habitacao*> getHabitacoes() const{return habitacoes;}
    vector<Cliente> getClientes() const{ return  clientes;}
    void pagar(){
        imprimeTodosClientes();
        string aux;
        cin.ignore(1000, '\n');
        cout << "Introduza o nome do Cliente: ", getline(cin, aux);
        Cliente c(aux);
        vector<Cliente>::iterator it = find(clientes.begin(), clientes.end(), c);
        if(it == clientes.end())
            throw logic_error("Nao existe nenhum cliente com o nome: "  + aux);
        int id = it->pagarMen();
        for(int i = 0; i < habitacoes.size(); i++){
            if(habitacoes[i]->getId() == id){
                habitacoes[i]->setPago("sim");
                break;
            }
        }
        cout << "\nMensalidade paga com sucesso!";
    }
};


#endif //PROJ1_CONDOMINIO_H
