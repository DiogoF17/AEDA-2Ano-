#ifndef PROJ1_HABITACAO_H
#define PROJ1_HABITACAO_H

#include <string>
#include <ctype.h>
#include <stdexcept>
#include <iostream>

using namespace std;

class Habitacao {
protected:
    string tipo;
    int id;
    string morada;
    double valorBase;
    double areaHabitacional;
    bool disponivel;
    bool pago;
    double mensalidade;
public:
    Habitacao(){}
    Habitacao(int i):id(i){}
    void setTipo(std::string t) { tipo = t; }
    virtual void imprime() const = 0;
    void setMorada(std::string m) {
        for (int i = 0; i < m.length(); i++)
            if (!isalpha(m[i]) && m[i] != ' ')
                throw logic_error("Erro no atributo Morada!");
        morada = m;
    }
    void setId(std::string id){
        for (int i = 0; i < id.length(); i++)
            if (!isdigit(id[i]) && id[i] != '.')
                throw logic_error("Erro no atributo ID!");
        this->id = stoi(id);
    }
    void setValorBase(std::string vB) {
        for (int i = 0; i < vB.length(); i++)
            if (!isdigit(vB[i]) && vB[i] != '.')
                throw std::logic_error("Erro no atributo Valor Base!");
        valorBase = std::stod(vB);
    }
    void setAreaHabitacional(std::string aA) {
        for (int i = 0; i < aA.length(); i++)
            if (!isdigit(aA[i]) && aA[i] != '.')
                throw std::logic_error("Erro no atributo Area Habitacional!");
        areaHabitacional = std::stod(aA);
    }
    void setPago(string p) {
        for (int i = 0; i < p.length(); i++)
            if (!isalpha(p[i]))
                throw std::logic_error("Erro no atributo Pago!");
        if (p == "sim") pago = true; else pago = false; }
    void setDisponibilidade(string d){
        for (int i = 0; i < d.length(); i++)
            if (!isalpha(d[i]))
                throw std::logic_error("Erro no atributo Piscina!");
        if(d == "sim")
            disponivel = true;
        else
            disponivel = false;
    }
    string getTipo() const{return tipo;}
    int getId()const{return id;}
    string getMorada() const{return morada;}
    double getValorBase() const{return valorBase;}
    double getAreaHabitacional() const{return areaHabitacional;}
    bool getDisponivel() const{return disponivel;}
    bool getPago() const{return pago;}
    double getMensalidade() const{ return mensalidade;}
    virtual void calcImposto() = 0;
};

class Vivenda:public Habitacao{
    double areaExterior;
    bool piscina;
public:
    Vivenda(){}
    void calcImposto() {
        double valor = valorBase;
        if (piscina == true) {
            if (areaExterior <= 500)
                valor = valor + 0.28 * valor;
            else if (areaExterior > 500 && areaExterior <= 1000)
                valor = valor + 0.45 * valor;
            else if (areaExterior > 1000 & areaExterior <= 2000)
                valor = valor + 0.55 * valor;
            else
                valor = valor + valor * 0.70;
        }
        else {
            if (areaExterior <= 500)
                valor = valor + 0.08 * valor;
            else if (areaExterior > 500 && areaExterior <= 1000)
                valor = valor + 0.20 * valor;
            else if (areaExterior > 1000 & areaExterior <= 2000)
                valor = valor + 0.35 * valor;
            else
                valor = valor + valor * 0.50;
        }
        mensalidade = valor;
    }
    void setAreaExterior(std::string aE) {
        for (int i = 0; i < aE.length(); i++)
            if (!isdigit(aE[i]) && aE[i] != '.')
                throw std::logic_error("Erro no atributo Area Exterior!");
        areaExterior = std::stod(aE);
    }
    void setPiscina(std::string p) {
        for (int i = 0; i < p.length(); i++)
            if (!isalpha(p[i]))
                throw std::logic_error("Erro no atributo Piscina!");
        if (p == "sim") piscina = true; else piscina = false;
    }
    double getAreaExterior() const{return areaExterior;}
    bool getPiscina() const{return piscina;}
    void imprime() const{
        cout << "Tipo.............: " << tipo
                << "\nID...............: " << id
             << "\nMorada...........: " << morada
             << "\nArea Habitacional: " << areaHabitacional
             << "\nArea Exterior....: " << areaExterior
             << "\nPiscina..........: ";
        if(piscina == true)
            cout << "sim";
        else
            cout << "nao";
        cout << "\nMensalidade......: " << mensalidade;
        cout << "\nPago.............: ";
        if(pago == true)
            cout << "sim";
        else
            cout << "nao";
        cout << "\nDisponivel.......: ";
        if(disponivel == true)
            cout << "sim";
        else
            cout << "nao";
        cout << endl << endl;
    }
};

class Apartamento:public Habitacao{
    int piso;
    string tipologia;
public:
    Apartamento(){}
    void calcImposto() {
        double valor = valorBase;
        if (piso >= 0 && piso <= 3) {
            if (tipologia == "T1")
                valor = valor + 0.05 * valor;
            else if (tipologia == "T2")
                valor = valor + 0.1 * valor;
            else
                valor = valor + 0.25 * valor;
        }
        else {
            if (tipologia == "T1")
                valor = valor + 0.15 * valor;
            else if (tipologia == "T2")
                valor = valor + 0.25 * valor;
            else
                valor = valor + 0.40 * valor;
        }
        mensalidade = valor;
    }
    void setTipologia(std::string t) {
        for (int i = 0; i < t.length(); i++)
            if (!isalpha(t[i]) && !isdigit(t[i]))
                throw std::logic_error("Erro no atributo Tipologia!");
        tipologia = t;
    }
    /**
     * altera o psio da habitacao e verifica se houve algum erro
     * @param p piso fornecido para alterar
     */
    void setPiso(std::string p) {
        for (int i = 0; i < p.length(); i++)
            if (!isdigit(p[i]) && p[i] != '.')
                throw std::logic_error("Erro no atributo Piso!");
        piso = stoi(p);
    }
    int getPiso() const{ return piso;}
    string getTipologia() const{ return  tipologia;}
    void imprime() const{
        cout << "Tipo.............: " << tipo
             << "\nID...............: " << id
             << "\nMorada...........: " << morada
             << "\nArea Habitacional: " << areaHabitacional
             << "\nPiso.............: " << piso
             << "\nTipologia........: " << tipologia;
        cout << "\nMensalidade......: " << mensalidade;
        cout << "\nPago.............: ";
        if(pago == true)
            cout << "sim";
        else
            cout << "nao";
        cout << "\nDisponivel.......: ";
        if(disponivel == true)
            cout << "sim";
        else
            cout << "nao";
        cout << endl << endl;
    }
};

#endif //PROJ1_HABITACAO_H
