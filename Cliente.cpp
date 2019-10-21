#include "Cliente.h"
#include <vector>
#include <string>

using namespace std;

vector<int> splitIds(string ids) {
    vector<int> ret;
    string aux = "";
    for(int i = 0; i < ids.length(); i++){
        if(ids[i] == ';') {
            if (aux != " ") {
                ret.push_back(stoi(aux));
                aux = "";
            }
        }
        else if(isdigit(ids[i]))
            aux += string(1, ids[i]);
        else
            throw logic_error("Erro no atributo IDS!");
    }
    ret.push_back(stoi(aux));
    return ret;
}
