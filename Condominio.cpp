#include "Condominio.h"
#include <fstream>

/**
 * le os ficheiros
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void Condominio::readFile(){
    //---------------------------
    string aux;
    ifstream entrada;
    cout << "Nome do Ficheiro: ", std::cin >> aux;
    entrada.open(aux);
    //verifica se houve algum erro ao tentar abrir o ficheiro
    while(std::cin.fail() || !entrada.is_open()){
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else
            std::cin.ignore(1000, '\n');
        std::cout << "Erro! Nome do Ficheiro: ", std::cin >> aux;
        entrada.open(aux);
    }
    nomeFicheiro = aux;
    //----------------------------
    //Le o ficheiro do condominio
    getline(entrada, aux);  //le palavra Habitacoes
    getline(entrada, aux); // le palavra seguinte a habitacoes
    while(aux != "CLIENTES") { // se a palvra nao for servicos
        if(aux == "Vivenda"){
            Vivenda *v = new Vivenda();
            (*v).setTipo(aux);
            getline(entrada, aux), (*v).setId(aux);
            getline(entrada, aux), (*v).setMorada(aux);
            getline(entrada, aux), (*v).setValorBase(aux);
            getline(entrada, aux), (*v).setAreaHabitacional(aux);
            getline(entrada, aux), (*v).setAreaExterior(aux);
            getline(entrada, aux), (*v).setPiscina(aux);
            getline(entrada, aux), (*v).setDisponibilidade(aux);
            v->setPago("nao"), v->calcImposto();
            habitacoes.push_back(v);
        }
        else{
            Apartamento *a = new Apartamento();
            (*a).setTipo(aux);
            getline(entrada, aux), (*a).setId(aux);
            getline(entrada, aux), (*a).setMorada(aux);
            getline(entrada, aux), (*a).setValorBase(aux);
            getline(entrada, aux), (*a).setAreaHabitacional(aux);
            getline(entrada, aux), (*a).setPiso(aux);
            getline(entrada, aux), (*a).setTipologia(aux);
            getline(entrada, aux), (*a).setDisponibilidade(aux);
            (*a).setPago("nao"), a->calcImposto();
            habitacoes.push_back(a);
        }
        getline(entrada, aux);
    }
    getline(entrada, aux); // le palavra seguinte a clientes
    while(aux != "SERVICOS") {
        Cliente *cl = new Cliente();
        cl->setNome(aux);
        getline(entrada, aux), cl->setNif(aux);
        getline(entrada, aux), cl->setIds(aux);
        clientes.push_back(*cl);
        getline(entrada, aux);
    }
    getline(entrada, aux); //le palavra servicos
    update = false;
    entrada.close();
    //-------------------------

}

/**
 * escreve nos ficheiros se for necessario e sai do programa
 * @param c classe usada que e para ser alterada e usada ao longo do programa
 */
void Condominio::writeFile(){
    char res;
    if(update == true){//o ficheiro foi alterado
        std::cout << "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
        std::cout << "Pretende guardar as alteracoes efetuadas('s'\\'n'): ", std::cin >> res;
        while(std::cin.fail() || (res!= 's' && res!='n')){
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            std::cout << "Erro! Pretende guardar as alteracoes efetuadas('s'\\'n'): ", std::cin >> res;
        }
        if(res == 's'){
            std::ofstream saida1;
            saida1.open(nomeFicheiro);
            saida1 << "HABITACOES";
            for(int i = 0; i < habitacoes.size(); i++){
                if(habitacoes[i]->getTipo() == "Vivenda") {
                    Vivenda *v = dynamic_cast<Vivenda *> (habitacoes[i]);
                    saida1 << endl << v->getTipo()
                           << std::endl << v->getId()
                           << std::endl << v->getMorada()
                           << std::endl << v->getValorBase()
                           << std::endl << v->getAreaHabitacional()
                           << std::endl << v -> getAreaExterior();
                    if(v -> getPiscina() == true)
                        saida1 << "\nsim";
                    else
                        saida1 << "\nnao";
                    if(v -> getDisponivel() == true)
                        saida1 << "\nsim";
                    else
                        saida1 << "\nnao";
                }
                else{
                    Apartamento *a = dynamic_cast<Apartamento *> (habitacoes[i]);
                    saida1 << endl << a->getTipo()
                           << std::endl << a->getId()
                           << std::endl << a->getMorada()
                           << std::endl << a->getValorBase()
                           << std::endl << a->getAreaHabitacional()
                           << std::endl << a -> getPiso()
                           << std::endl << a -> getTipologia();
                    if(a -> getDisponivel() == true)
                        saida1 << "\nsim";
                    else
                        saida1 << "\nnao";
                }
            }
            saida1 << std::endl << "CLIENTES";
            for(int i = 0; i < clientes.size(); i++){
                saida1 << endl << clientes[i].getNome()
                       << std::endl << clientes[i].getNif();
                if(clientes[i].getIds().size() == 0)
                    saida1 << "\n-";
                else{
                    vector<int> ids = clientes[i].getIds();
                    saida1 << endl;
                    for(int j = 0; j < ids.size(); j++){
                        if(j == ids.size() - 1)
                            saida1 << ids[j];
                        else
                            saida1 << ids[j] << "; ";
                    }
                }

            }
            saida1 << "\nSERVICOS";
            saida1.close();
            std::cout << "\nAs alteracoes foram gravadas com sucesso!\n\n";
            exit(1);
        }
        else
            exit(1);
    }
    else
        exit(1);
}

//---------------------------------------------------------
//                  AUXILIARES
//---------------------------------------------------------

/**
 * E usada para confirmar e validar as opcoes
 * @param zero diz se e para considerar zero ou nao
 * @param num e o numero de opcoes maximas que pode escolher
 * @return opcao que o utilizador escolheu
 */
int Opcao(bool zero, int num){
    int op;
    if(zero == true) {
        std::cout << "\n\nInsira a sua opcao: ", std::cin >> op;
        while (std::cin.fail() || op < 0 || op > num) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            } else {
                std::cin.ignore(1000, '\n');
            }
            std::cout << "Opcao Invalida! Insira a sua opcao: ", std::cin >> op;
        }
    }
    else{
        std::cout << "\n\nInsira a sua opcao: ", std::cin >> op;
        while (std::cin.fail() || op < 1 || op > num) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            } else {
                std::cin.ignore(1000, '\n');
            }
            std::cout << "Opcao Invalida! Insira a sua opcao: ", std::cin >> op;
        }
    }
    return op;
}

