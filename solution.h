#include <iostream>
#include "CircularArray.h"
#include "stack.h"

using namespace std;

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
        else if(input.length()-(i+1)>=3 && input[i]=='A' && input[i+1]=='N' && input[i+2]=='D'){
            caracteres.push_back("AND");
        }
        else if(input.length()-(i+1)>=2 && input[i]=='O' && input[i+1]=='R'){
            caracteres.push_back("OR");
        }
        else if(input.length()-(i+1)>=5 && input[i]=='A' && input[i+1]=='N' && input[i+2]=='D' && input[i+3]=='N' && input[i+4]=='O' && input[i+5]=='T'){
            caracteres.push_back("ANDNOT");
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


Result evaluate(string input)
{
    Result resultado;
    resultado.error = false;
    // 1- descomponer el input y validar (Listo)
    // string -> vector<string>
    // "(5 + 10)/8.2"  -> "(","5","+","10",")","/","8.2"]  
    
    CircularArray<string>array = separarCadena(input); //descompongo en un circular array

    //Imprimir el array
    cout << "Array  de cadenas separadas:" << endl;
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
        return resultado;

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
    Stack<float>operacion;
    if(resultado.error)
        resultado.result=0;
    else{
        for(auto it=postfijo.begin();it!=postfijo.end();++it){
            if(*it!="AND" && *it!="OR" && *it!="ANDNOT") //si es un número se hace push
                operacion.push(stof(*it));
            else{
                if(operacion.size()<=1){
                    
                    resultado.error=true;
                }
                else{
                    float operador1 = operacion.pop();
                float operador2 = operacion.pop();
                if(*it=="+"){
                    operacion.push(operador2+operador1);
                }
                else if(*it=="-"){
                    operacion.push(operador2-operador1);
                }
                else if(*it=="*"){
                    operacion.push(operador2*operador1);
                }
                else if(*it=="/"){
                    operacion.push(operador2/operador1);
                }
                }
                
            }
        }
    }

    resultado.result = operacion.pop();
    

    return resultado; //devuelve un objeto de tipo Result
}