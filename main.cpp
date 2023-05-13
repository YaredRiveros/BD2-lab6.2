#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include "solution.h"
#include <vector>

using namespace std;


void leerIndex(map<string,list<int>>&keyWords){
    ifstream file("index.txt");
    string line;

    while(!file.eof()){
        getline(file,line);
        // Hallar la key
        size_t separacion = line.find(":");
        string key = line.substr(0,separacion);
        // cout << key << ":";;
        // Hallar los valores
        string values = line.substr(separacion+1,line.length());
        // cout << values << endl;

        //Agregar valores a una lista
        list<int> valuesList;
        int i=0;
        while(i<values.length()){
            if(values[i]==','){
                i++;
            }
            else{
                string value = values.substr(i,values.find(",",i)-i);
                valuesList.push_back(stoi(value));
                i+=value.length();
            }
        }
        
        // Agregar key y lista de valores al map
        keyWords.insert(pair<string,list<int>>(key,valuesList));
    }
    file.close();
}

void printMap(map<string,list<int>>&keyWords){
    for(auto it=keyWords.begin();it!=keyWords.end();it++){
        cout << it->first << ":";
        for(auto it2=it->second.begin();it2!=it->second.end();it2++){
            cout << *it2 << ",";
        }
        cout << endl;
    }
}

int main(){
    map<string,list<int>> keyWords; 
    // Guardar keyWords:values en un map
    leerIndex(keyWords);

    // Reviso si se leyó correctamente
    printMap(keyWords);


    //Envío consulta 1	
    cout << "\t--Consulta 1--" << endl;
    string consulta1 = "(acudir AND anillado) OR ahora";
    evaluate(consulta1,keyWords);

    cout << "Resultados: " << endl;
    list<int> resultados1 = keyWords["result"];

    for(auto it=resultados1.begin();it!=resultados1.end();it++){
        cout << *it << ",";
    }
    cout << endl;

    //Envío consulta 2
    cout << "\t--Consulta 2--" << endl;
    string consulta2 = "segundo ANDNOT (tortura OR viajero)";
    evaluate(consulta2,keyWords);

    cout << "Resultados: " << endl;
    list<int> resultados2 = keyWords["result"];

    for(auto it=resultados2.begin();it!=resultados2.end();it++){
        cout << *it << ",";
    }
    cout << endl;


    //Envío consulta 3
    cout << "\t--Consulta 3--" << endl;
    string consulta3 = "(tambor OR refugiado) AND trampa";
    evaluate(consulta3,keyWords);

    cout << "Resultados: " << endl;
    list<int> resultados3 = keyWords["result"];

    for(auto it=resultados3.begin();it!=resultados3.end();it++){
        cout << *it << ",";
    }
    cout << endl;

    return 0;
}