#include <iostream>
#include "CircularArray.h"
#include "stack.h"
#include <map>

using namespace std;


string llamar_AND(string operador1, string operador2, map<string,list<int>>&keyWords){
    list<int> lista1 = keyWords[operador1];
    list<int> lista2 = keyWords[operador2];
    list<int> resultado;
    auto it1 = lista1.begin();
    auto it2 = lista2.begin();
    while(it1!=lista1.end() && it2!=lista2.end()){
        if(*it1==*it2){
            resultado.push_back(*it1);
            it1++;
            it2++;
        }
        else if(*it1<*it2){
            it1++;
        }
        else{
            it2++;
        }
    }
    cout << "AND: ";
    for(auto it=resultado.begin();it!=resultado.end();it++){
        cout << *it << ",";
    }
    cout << endl;

    keyWords["result"] = resultado;     //Creo una nueva llave en el map con el resultado de la operación
    return "result";        //retorn "result" para diferenciar entre un operador normal y una respuesta que ya hice
}

string llamar_OR(string operador1, string operador2, map<string,list<int>>&keyWords){
    list<int> lista1 = keyWords[operador1];
    list<int> lista2 = keyWords[operador2];
    list<int> resultado;
    auto it1 = lista1.begin();
    auto it2 = lista2.begin();
    while(it1!=lista1.end() && it2!=lista2.end()){
        if(*it1==*it2){
            resultado.push_back(*it1);
            it1++;
            it2++;
        }
        else if(*it1<*it2){
            resultado.push_back(*it1);
            it1++;
        }
        else{
            resultado.push_back(*it2);
            it2++;
        }
    }

    while(it1!=lista1.end()){
        resultado.push_back(*it1);
        it1++;
    }

    while(it2!=lista2.end()){
        resultado.push_back(*it2);
        it2++;
    }

    cout << "OR: ";
    for(auto it=resultado.begin();it!=resultado.end();it++){
        cout << *it << ",";
    }
    cout << endl;

    keyWords["result"] = resultado;
    return "result";
}

string llamar_ANDNOT(string operador1, string operador2, map<string,list<int>>&keyWords){
    list<int> lista1 = keyWords[operador1];
    list<int> lista2 = keyWords[operador2];
    list<int> resultado;
    auto it1 = lista1.begin();
    auto it2 = lista2.begin();
    while(it1!=lista1.end() && it2!=lista2.end()){
        if(*it1==*it2){
            it1++;
            it2++;
        }
        else if(*it1<*it2){
            resultado.push_back(*it1);
            it1++;
        }
        else{
            it2++;
        }
    }

    while(it1!=lista1.end()){
        resultado.push_back(*it1);
        it1++;
    }

    cout << "ANDNOT: ";
    for(auto it=resultado.begin();it!=resultado.end();it++){
        cout << *it << ",";
    }
    cout << endl;

    keyWords["result"] = resultado;
    return "result";
}

struct Result{
    double result;
    bool error;
};

//IMPORTANTE: el operador debe estar en mayúsculas, sino no funciona
CircularArray<string> separarCadena(string input){
    CircularArray<string>caracteres;
    for(int i=0;i<input.length();i++){
        if(input[i]==' ')
            continue;
        else if(input[i]=='(' || input[i]==')'){
            string s(1,input[i]); //convierto caracter a string con el constructor del std::string
            caracteres.push_back(s);
        }
        else if(input.length()-(i+1)>=5 && input[i]=='A' && input[i+1]=='N' && input[i+2]=='D' && input[i+3]=='N' && input[i+4]=='O' && input[i+5]=='T'){
            caracteres.push_back("ANDNOT");
        }
        else if(input.length()-(i+1)>=3 && input[i]=='A' && input[i+1]=='N' && input[i+2]=='D'){
            caracteres.push_back("AND");
        }
        else if(input.length()-(i+1)>=2 && input[i]=='O' && input[i+1]=='R'){
            caracteres.push_back("OR");
        }
        else if(input[i]>=97 && input[i]<=122){ //Si es palabra en minuscula
            //recorrido desde el operando hasta que encuentre un espacio vacío, salga de la cadena o encuentre un operador (palabra mayuscula)
            int pos_inicio=i, pos_final=i;
            for(int j=i+1;i<input.length() && input[j]>=97 && input[j]<=122;j++){ //(de izquierda a derecha)
                pos_final++;
            }
            for(int j=i-1;j>=0 && input[j]>=97 && input[j]<=122;j--){ //(de derecha a izquierda)
                pos_inicio--;
            }
            // creo un string con todo el operando
            string num;
            for (int j = pos_inicio; j <= pos_final; j++)
            {
                num += input[j];
            }
            caracteres.push_back(num);
            // Hago que el i salte a la última cifra del operando (para que cuando entre a la cond. del for salga del operando con el i++)
            i = pos_final;
        }
    }
    return caracteres;
}


void evaluate(string input, map<string,list<int>>&keyWords)
{
    Result resultado;
    resultado.error = false;
    // 1- descomponer el input y validar (Listo)
    // string -> vector<string>
    // "(5 + 10)/8.2"  -> "(","5","+","10",")","/","8.2"]  
    
    CircularArray<string>array = separarCadena(input); //descompongo en un circular array


    //Busco palabras en el map que sean sufijos de mis operandos
    // int max_tamanio_raiz = 0;
    map<string,int>max_raiz;
    for(int i=0;i<array.get_size();i++){
        max_raiz[array[i]] = 0;
    }

    for(auto it=keyWords.begin();it!=keyWords.end();++it){
        for(int i=0;i<array.get_size();i++){
            if(array[i].find(it->first)!=string::npos){
                int tamanio_raiz = (it->first).length();
                if(tamanio_raiz>max_raiz[array[i]]){  //busco las raices con más caracteres en común con los operandos
                    max_raiz[array[i]] = (it->first).length();
                    // array[i] = it->first;
                    // cout << "nueva raiz: " << array[i] << endl;
                    // cout << "Tamanio de la nueva raiz: " << array[i].length() << endl;
                }
            }
        }
    }

    //Reemplazo los operandos por sus raices
    for(int i=0;i<array.get_size();i++){
        if(max_raiz[array[i]]!=0){
            array[i] = array[i].substr(0,max_raiz[array[i]]);
        }
    }

    //Imprimir el array
    cout << "Array de cadenas separadas:" << endl;
    for(auto it=array.begin();it!=array.end();++it){
        cout<<*it<<" ";
    }
    cout << endl;
    
    //validaciones para la forma infija
    //a) Validar en el CircularArray "array" que un operador no puede ser ni primer ni último elemento.
    if(array[0]=="AND"|| array[0]=="OR" || array[0]=="ANDNOT"){
        resultado.error = true;
    }
    else if(array[array.get_size()-1]=="AND" || array[array.get_size()-1] == "OR" || array[array.get_size()-1] == "ANDNOT"){
        resultado.error = true;
    }
    //b Un operando no puede estar justo antes de un "(" ni justo después de un ")"
    for(int i=1;i<array.get_size()-1;i++){
        if(array[i]=="(" && array[i-1]!="AND" && array[i-1]!="OR" && array[i-1]!="ANDNOT"){
            resultado.error = true;
        }
        else if(array[i]==")" && array[i+1]!="AND" && array[i+1]!="OR" && array[i+1]!="ANDNOT"){
            resultado.error = true;
        }
        //No puede haber 2 operadores juntos
        else if((array[i]=="AND" || array[i] == "OR" || array[i] == "ANDNOT") &&
         (array[i-1]=="AND" || array[i-1] == "OR" || array[i-1] == "ANDNOT" || 
         array[i+1]=="AND" || array[i+1] == "OR" || array[i+1] == "ANDNOT")){
            resultado.error = true;
        }
    }

    if(resultado.error==true) //Si ocurrió un error a este punto, retornar sin respuesta
        throw("Error en la expresión ingresada");

    // 2- convertir de Infijo a Postfijo
    //  ["(","5","+","10",")","/","8.2"]   -> 5 10 + 8.2 /

    //convierto de infijo a postfijo
    
    CircularArray<string>postfijo;
    Stack<string> pila;

    for(auto it=array.begin();it!=array.end();++it){
        if(*it=="(") //Los '(' se ponen colocan en el tope del stack
            pila.push(*it);
        else if(*it==")"){      //Si se encuentra un ')', hacer pop hasta encontrar un '(' para dar prioridad a esos operadores
            while(pila.top()!="("){
                postfijo.push_back(pila.top()); //Se agrega al array postfijo
                pila.pop();
            }
            pila.pop();
        }
        else if(*it=="AND" || *it=="OR" || *it=="ANDNOT"){     //Si se encuentra un operador
            
            //A este while no entraría nunca en este caso porque no hay operadores con mayor prioridad!

            // while(!pila.is_empty() && pila.top()!="(" && (pila.top()=="*" || pila.top()=="/")){ //Se hace pop y se agregan los operadores de mayor prioridad
            //     postfijo.push_back(pila.top());
            //     pila.pop();
            // }
            pila.push(*it); //se hace push al del operador encontrado al stack
        }
        else{       //Si llega un operando, se le hace push al array postfijo
            postfijo.push_back(*it);
        }
    }

    while(!pila.is_empty()){ //Se agregan a postfijo aquellos operadores que quedaron en el stack
        postfijo.push_back(pila.top());
        pila.pop();
    }


    //Imprimir el array postfijo
    cout << "Array postfijo:" << endl;
    for(auto it=postfijo.begin();it!=postfijo.end();++it){
        cout<<*it<<" ";
    }
    cout << endl;

    // 3- resolver la expresion 
    
    //* Si no cumple la validacion de () y [] retornar Result.error = true;
    Stack<string>validacion;
    for(auto it=array.begin();it!=array.end();++it){
        if(*it=="(" || *it==")"|| *it=="[" || *it=="]"){
            if(*it =="(" || *it == "[")
            validacion.push(*it);
            else if(*it == ")"){ //Si se encuentra un paréntesis de cierre justo dps de abrirse un corchete, hay un error
                if(validacion.pop() != "("){
                    resultado.error = true;
                    break;
                }
            }
            else if(*it == "]"){  //Si se encuentra un corchete de cierre justo después de abrirse un paréntesis, hay un error
                if(validacion.pop() != "["){
                    resultado.error = true;
                    break;
                }
            }
        }
    }
    if(!validacion.is_empty())
        resultado.error=true;

    // Si no está vacía ni tiene errores, se resuelve la expresión <---- Aca me quede. Falta:
    //- adaptarlo para que realice las operaciones AND, OR y ANDNOT. 
    //- Quitar stof porque ya no son números
    Stack<string>operacion;
    if(resultado.error)
        resultado.result=0;
    else{
        for(auto it=postfijo.begin();it!=postfijo.end();++it){
            if(*it!="AND" && *it!="OR" && *it!="ANDNOT") //si es un número se hace push
                operacion.push(*it);
            else{
                if(operacion.size()<=1){        //Si hay menos de 2 operandos, hay un error
                    
                    resultado.error=true;
                }
                else{
                    string operador1 = operacion.pop();
                    string operador2 = operacion.pop();
                    if(*it=="AND"){
                        string resultado = llamar_AND(operador1,operador2,keyWords); //retorna documentos que contengan ambos términos
                        operacion.push(resultado);
                    }
                    else if(*it=="OR"){
                        string resultado = llamar_OR(operador1,operador2,keyWords);  //retorna documentos que contengan al menos uno de los términos
                        operacion.push(resultado);
                    }
                    else if(*it=="ANDNOT"){
                        string resultado = llamar_ANDNOT(operador1,operador2,keyWords); //retorna documentos que contengan el primer término pero no el segundo
                        operacion.push(resultado);
                    }
                }
                
            }
        }
    }

}