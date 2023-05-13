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
    string consulta = "(acud AND anill) OR ahor";
    evaluate(consulta,keyWords);

    cout << "Resultados: " << endl;
    list<int> resultados = keyWords["result"];

    for(auto it=resultados.begin();it!=resultados.end();it++){
        cout << *it << ",";
    }
    cout << endl;


    //Envío consulta 2	
    string consulta2 = "(acudir AND anillado) OR ahorro";
    evaluate(consulta2,keyWords);

    cout << "Resultados: " << endl;
    list<int> resultados2 = keyWords["result"];

    for(auto it=resultados2.begin();it!=resultados2.end();it++){
        cout << *it << ",";
    }
    cout << endl;


    //Funciona pero ahora necesio que funcione con palabras que tengan un sufijo en el map, no que sean iguales
    return 0;
}