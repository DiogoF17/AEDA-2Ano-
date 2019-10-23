#include <iostream>
#include <fstream>
#include <vector>
#include "Condominio.h"

using namespace std;

//------------------------------------------------------
//                      FUNCOES PRINCIPAIS
//-----------------------------------------------------

/**
 * cria um cliente
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void criarCliente(Condominio &c){
    std::string aux;
    Cliente *cl = new Cliente();
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tCRIAR CLIENTE\n";
    //------------------------------------------------------------
    //                          TENTA CRIAR A VIVENDA
    //-------------------------------------------------------------
    try {
        std::cin.ignore(1000, '\n');
        cout << "Introduza o nome: ", getline(cin, aux), cl->setNome(aux);
        std::cout << "Introduza o NIF: ", getline(std::cin, aux);
        c.verifyNif(aux);
        cl->setNif(aux);
        c.addCliente(*cl);   //adiciona a vivenda ao cliente
        c.update = true;
        std::cout << std::endl << std::endl;
    }
    catch(std::logic_error &l){
        std::cout << l.what() << std::endl << std::endl;
        delete cl;
    }
    system("pause");
}

/**
 * altera um cliente
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void alterarCliente(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tALTERAR CLIENTE\n\n";
    try{
        c.alterarCliente();
        c.update = true;
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    catch(int id){
        cout << "\nNao existe nenhuma habitacao com o ID: " << id << "\n\n";
    }
    system("pause");
}

/**
 * remove um cliente
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void removerCliente(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tREMOVER CLIENTE\n\n";
    try{
        c.removerCliente();
        c.update = true;
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

/**
 * associa uma habitacao a um cliente
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void associarHabit(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tADQUIRIR HABITACAO\n\n";
    try{
        c.associarHabit();
        c.update = true;
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

/**
 * desassocia uma habitacao
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void desassociarHabit(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tDESASSOCIAR HABITACAO\n\n";
    try{
        c.desassociarHabit();
        c.update = true;
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

/**
 * cria uma vivenda e adiciona a classe Condominio
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void criarVivenda(Condominio &c){
    std::string aux;
    Vivenda *v = new Vivenda();
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tCRIAR VIVENDA\n";
    //------------------------------------------------------------
    //                          TENTA CRIAR A VIVENDA
    //-------------------------------------------------------------
    try {
        std::cin.ignore(1000, '\n');
        v->setTipo("Vivenda");
        cout << "Introduza o ID: ", getline(cin, aux), v->setId(aux);
        c.verifyId(stoi(aux));
        std::cout << "Introduza a morada: ", getline(std::cin, aux), v->setMorada(aux);
        std::cout << "Introduza o Valor Base: ", getline(std::cin, aux), v->setValorBase(aux);
        std::cout << "Introduza a Area de Habitacao: ", getline(std::cin, aux), v->setAreaHabitacional(aux);
        std::cout << "Introduza a Area Exterior: ", getline(std::cin, aux), v->setAreaExterior(aux);
        std::cout << "Introduza se tem Piscina('sim'/'nao'): ", getline(std::cin, aux), v->setPiscina(aux);
        v->setPago("nao"), v->calcImposto(), v->setDisponibilidade("sim");
        c.addHabitacao(v);   //adiciona a vivenda ao cliente
        c.update = true;
        std::cout << std::endl << std::endl;
    }
    catch(std::logic_error &l){
        std::cout << l.what() << std::endl << std::endl;
        delete v;
    }
    system("pause");
}

/**
 * cria um apartamento e adicionao a classe Condominio
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void criarApartamento(Condominio &c) {
    std::string aux;
    Apartamento *a = new Apartamento();
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tCRIAR APARTAMENTO\n";
    try{
        std::cin.ignore(1000, '\n');
        a->setTipo("Apartamento");
        cout << "Introduza o ID: ", getline(cin, aux), a->setId(aux);
        c.verifyId(stoi(aux));
        std::cout << "Introduza a morada: ", getline(std::cin, aux), a->setMorada(aux);
        std::cout << "Introduza o Valor Base: ", getline(std::cin, aux), a->setValorBase(aux);
        std::cout << "Introduza a Area de Habitacao: ", getline(std::cin, aux), a->setAreaHabitacional(aux);
        std::cout << "Introduza o Piso: ", getline(std::cin, aux), a->setPiso(aux);
        std::cout << "Introduza a Tipologia: ", getline(std::cin, aux), a->setTipologia(aux);
        a->setPago("nao"), a->calcImposto(), a->setDisponibilidade("sim");
        c.addHabitacao(a);    //adiciona apartamento ao cliente
        c.update = true;
        std::cout << std::endl << std::endl;
    }
    catch(std::logic_error &l){
        std::cout << l.what() << std::endl << std::endl;
        delete a;
    }
    system("pause");
}

/**
 * altera a Habitacao escolhida pelo utilizador atraves das moradas
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void alterarHabitacao(Condominio &c){
    //------------------------------------------------------------
    //                          MOSTRA OS NOMES
    //-------------------------------------------------------------
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tALTERAR HABITACAO\n\n";
    try{
        c.alterarHabitacao();
        c.update = true;
        cout << endl << endl;
    }
    catch(logic_error &e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

/**
 * remove uma habitacao do condominio
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void removerHabitacao(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tREMOVER HABITACAO\n\n";
    try{
        c.removerHabitacao();
        c.update = true;
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

/**
 * funcao que serve para pagar a mensalidade de uma casa que pertence a um determinado cliente
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void pagMen(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tPAGAR MENSALIDADE\n";
   try{
       c.pagar();
       c.update = true;
       cout << endl << endl;
   }
   catch(logic_error &e){
       cout << e.what() << endl << endl;
   }
    system("pause");
}

/**
 * mostra todos os clientes do condominio
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void verTodosClientes(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tVER TODOS CLIENTES\n\n";
    c.imprimeTodosClientes();
    system("pause");
}

/**
 * mostra todos os clientes do condominio
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void verTodasHabitacoes(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tVER TODAS HABITACOES\n\n";
    c.verTodosHabitacoes();
    system("pause");
}

/**
 * mostra um cliente especifico
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void verClienteEsp(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tVER CLIENTE ESPECIFICO\n\n";
    try {
        c.imprimeCliente();
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

/**
 * mostrahabitacao especifica
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void verHabitacaoEsp(Condominio &c){
    std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tVER HABITACAO ESPECIFICA\n\n";
    try {
        c.verHabitacaoEsp();
        cout << endl << endl;
    }
    catch(logic_error& e){
        cout << e.what() << endl << endl;
    }
    system("pause");
}

//---------------------------------------------------------
//                  MENUS
//---------------------------------------------------------

/**
 * menu que permite escolher entre criar habitacao e vivenda
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void criarHabitacao(Condominio &c){
    bool ON = true;
    int op;
    while(ON){
        std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tCRIAR HABITACAO\n\n";
        std::cout << "\n1) Criar Vivenda;\n2) Criar Apartamento;\n3) Voltar;\n0) Sair;";
        op = Opcao(true,3);
        switch(op){
            case 1:
                criarVivenda(c);
                break;
            case 2:
                criarApartamento(c);
                break;
            case 3:
                return;
            case 0:
                c.writeFile();
        }
    }
}

/**
 * mostra o menu ver Clientes
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
 void verClientes(Condominio &c){
    bool ON = true;
    int op;
    while(ON){
        std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tMENU VER CLIENTES\n\n";
        std::cout << "\n1) Ver Todos os Clientes;\n2) Ver Cliente Especifico;\n3) Voltar;\n0) Sair;";
        op = Opcao(true,3);
        switch(op){
            case 1:
                verTodosClientes(c);
                break;
            case 2:
                verClienteEsp(c);
                break;
            case 3:
                return;
            case 0:
                c.writeFile();
        }
    }
 }

 /**
  * mostra o menu ver pacotes
  * @param c classe usada que e para ser alterada e usada ao longo do programa
  */
 void verHabitacoes(Condominio &c){
     bool ON = true;
     int op;
     while(ON){
         std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tMENU VER HABITACOES\n\n";
         std::cout << "\n1) Ver Todos as Habitacoes;\n2) Ver Habitacao Especifico;\n3) Voltar;\n0) Sair;";
         op = Opcao(true,3);
         switch(op){
             case 1:
                 verTodasHabitacoes(c);
                 break;
             case 2:
                 verHabitacaoEsp(c);
                 break;
             case 3:
                 return;
             case 0:
                 c.writeFile();
         }
     }
 }

/**
 * mostra o menu ver info
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void verInfo(Condominio &c){
    bool ON = true;
    int op;
    while(ON){
        std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tMENU VER INFO\n\n";
        std::cout << "\n1) Ver Clientes;\n2) Ver Habitacoes;\n3) Ver Servicos;\n4) Voltar;\n0) Sair;";
        op = Opcao(true,4);
        switch(op){
            case 1:
                verClientes(c);
                break;
            case 2:
                verHabitacoes(c);
                break;
            case 3:
                //removerHabitacao(c);
                break;
            case 4:
                return;
            case 0:
                c.writeFile();
        }
    }
}

/**
 * mostra o menu geir habitacoes
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void gerHabit(Condominio &c){
    bool ON = true;
    int op;
    while(ON){
        std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tMENU GERIR HABITACOES\n\n";
        std::cout << "\n1) Criar Habitacao;\n2) Alterar Habitacao;\n3) Remover Habitacao;\n4) Voltar;\n0) Sair;";
        op = Opcao(true, 4);
        switch(op){
            case 1:
                criarHabitacao(c);
                break;
            case 2:
                alterarHabitacao(c);
                break;
            case 3:
                removerHabitacao(c);
                break;
            case 4:
                return;
            case 0:
                c.writeFile();
        }
    }
}

/**
  * mostra o menu gerir clientes
  * @param c classe usada que e para ser alterada e usada ao longo do programa
  */
void gerCli(Condominio &c){
    bool ON = true;
    int op;
    while(ON){
        std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tMENU GERIR CLIENTES\n\n";
        std::cout << "\n1) Criar Cliente;\n2) Alterar Cliente;\n3) Remover Cliente;\n4) Pagar Mensalidade;\n5) Comprar Habitacao; \n6) Desassociar Habitacao;\n7) Voltar;\n0) Sair;";
        op = Opcao(true, 7);
        switch(op){
            case 1:
                criarCliente(c);
                break;
            case 2:
                alterarCliente(c);
                break;
            case 3:
                removerCliente(c);
                break;
            case 4:
                pagMen(c);
                break;
            case 5:
                associarHabit(c);
                break;
            case 6:
                desassociarHabit(c);
                break;
            case 7:
                return;
            case 0:
                c.writeFile();
        }
    }
}

/**
 * mostra o menu Principal
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void mainMenu(Condominio &c){
    bool ON = true;
    int op;
    while(ON){
        std::cout << "\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\t\tMENU PRINCIPAL\n\n";
        std::cout << "\n1) Gerir Habitacoes;\n2) Gerir Clientes;\n3) Gerir Servicos;\n4) Ver Info;\n0) Sair;";
        op = Opcao(true,4);
        switch(op){
            case 1:
                gerHabit(c);
                break;
            case 2:
                gerCli(c);
                break;
            case 3:

                break;
            case 4:
                verInfo(c);
                break;
            case 0:
                c.writeFile();
        }
    }
}

//----------------------------------------------------------
//                  MAIN
//----------------------------------------------------------

int main() {
    Condominio c;
    c.readFile();
    mainMenu(c);
    return 0;
}