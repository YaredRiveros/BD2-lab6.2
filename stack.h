#include <iostream>

using namespace std;


template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){ 
        //data = 0;
        next = nullptr;
        prev = nullptr;
    }

    Node(T value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }

    void killSelf(){
        ~Node();
    }

    ~Node(){
        //delete next; //Ya se libera memoria de todos los nodos en las clases double, forward y circular list
        //delete prev;     
    }    
};

template <typename T>
class List {    
    public:        
        virtual ~List(){
            // TODO            
        };        
        //Contrato: Todas las clases que heredan de una clase abstracta, deben de implementar todos los métodos de la clase padre o
        //habrá error al instanciar un objeto de las clases hijas
        virtual T front() = 0;
        virtual T back() = 0;
        virtual void push_front(T) = 0;
        virtual void push_back(T) = 0;
        virtual T pop_front() = 0;
        virtual T pop_back() = 0;
        virtual void insert(T, int) = 0;
        virtual bool remove(int) = 0;
        virtual T& operator[](int) = 0;//debe ser declarado en cada clase hija
        virtual bool is_empty() = 0;
        virtual int size() = 0;
        virtual void clear() = 0;
        virtual void sort() = 0;
        virtual bool is_sorted() = 0;
        virtual void reverse() = 0;
        virtual std::string name() = 0;
        virtual void display() = 0;
};



template <typename T>
class DoubleList : public List<T> {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int nodes;
    public:
        DoubleList() : List<T>() {
            head = nullptr;
            tail = nullptr;
            nodes = 0;
        }

        ~DoubleList(){ 
            clear();
        }

        T front(){
            T elemento;
            try{
                if(is_empty())
                    throw "La lista está vacía!";
                else
                    elemento = head->data;
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
            return elemento;
        }

        T back(){
            T elemento;
            try{
                if(is_empty())
                    throw "La lista está vacía!";
                else
                    elemento = tail->data;
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
            return elemento;
        }

        void push_front(T value){
            Node<T>* nuevo = new Node<T>(value);
            if(is_empty()){
                head = nuevo;
                tail = nuevo;
            }
            else{
                nuevo->next = head;
                head->prev = nuevo;
                head = nuevo;
            }
            nodes++;
        }

        void push_back(T value){
            Node<T>* nuevo = new Node<T>(value);
            if(is_empty()){
                head = nuevo;
                tail = nuevo;
            }
            else{
                nuevo->prev = tail;
                tail->next = nuevo;
                tail = nuevo;
            }
            nodes++;
        }

        T pop_front(){ //Funciona
            T elm;
            try{
                if(is_empty()){
                    throw "La lista está vacía!";
                }   
                else if(head->next==nullptr){
                    elm = head->data;
                    delete head;
                    head = nullptr;
                    nodes--;
                }
                else{
                    elm = head->data;
                    Node<T>* temp = head;
                    head = head->next;
                    delete temp;
                    nodes--;  
                }
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
        
        if(nodes==0){
            head = nullptr;
            tail = nullptr;
        }
        return elm;
        }

        T pop_back(){
            T elm;
            try{
                if(is_empty()){
                    throw "La lista está vacía!";
                }
                else if(head->next==nullptr){
                    elm = tail->data;
                    delete head;
                    head = nullptr;
                    nodes--;
                }
                else{
                    elm = tail->data;
                    Node<T>* temp = tail;
                    tail = tail->prev;
                    tail->next = nullptr;
                    delete temp;
                    nodes--;
                }    
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
            if(nodes==0){
                head = nullptr;
                tail = nullptr;
            }
            return elm;
        }

        void insert(T data, int pos){
            Node<T>* temp = head;
            for(int i=0;i<pos-1;i++){
                temp = temp->next;
            }
            Node<T>* nuevo_nodo = new Node<T>;
            nuevo_nodo->data = data;
            nuevo_nodo->next = temp->next;
            temp->next = nuevo_nodo;
            nodes++;
        }


        bool remove(int pos){
            bool exito = true;
            try{
                if(pos<0 || pos>=nodes){
                    exito = false;
                    throw "Posición fuera de rango";
                }
                else if(is_empty()){
                    exito = false;
                    throw "No hay elementos para eliminar";
                }
                else if(pos==0){
                    pop_front();
                }
                else if(pos==nodes-1){
                    pop_back();
                }
                else{
                    Node<T>* temp = head;
                    for(int i=0;i<pos-1;i++){
                        temp = temp->next;
                    }
                    Node<T>* temp2 = temp->next;
                    temp->next = temp->next->next;
                    delete temp2;
                    nodes--;
                }
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
            if(nodes==0){
                head = nullptr;
                tail = nullptr;
            }
            return exito;
        }

        T& operator[](int index){
            Node<T>* temp = head;
            try{
                if(is_empty())
                    throw "La lista está vacía!";
                else if(index < 0 || index >= nodes)
                    throw "El índice está fuera de rango";
                else{
                    for(int i = 0; i < index; i++)
                        temp = temp->next;
                }
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
            return temp->data;
        }

        bool is_empty(){
            return head == nullptr && tail == nullptr;
        }

        int size(){
            return nodes;
        }

        void clear(){
            while(!is_empty())
                pop_front();
        }

        void sort(){
            Node<T>* temp = head;
            for(int i = 0; i < nodes; i++){
                Node<T>* temp2 = temp->next;
                for(int j = i + 1; j < nodes; j++){
                    if(temp->data > temp2->data){
                        T aux = temp->data;
                        temp->data = temp2->data;
                        temp2->data = aux;
                    }
                    temp2 = temp2->next;
                }
                temp = temp->next;
            }
        }

        bool is_sorted(){
            if(!is_empty()){
                if(head->next==nullptr) //Solo un elemento en la lista
                    return true;
                Node<T>* temp = head;   //Más de un elemento en la lista
                while(temp->next!=nullptr){
                    if(temp->data > temp->next->data)
                        return false;
                    temp = temp->next;
                }
            }
            return true;
        }

        void reverse(){
            Node<T>* temp = head;
            for(int i = 0; i < nodes; i++){
                Node<T>* temp2 = temp->next;
                temp->next = temp->prev; 
                temp->prev = temp2; 
                temp = temp2; 
            }
            temp = head;
            head = tail;
            tail = temp;
        }

        string name(){
            return "Double Linked List";
        }

        void display(){
            if(is_empty()){
                cout << "La lista está vacía!" << endl;
            } 
            else{
                Node<T>* temp = head;
                while(temp!=nullptr){
                    cout << temp->data << ",";
                    temp = temp->next;
                }
                cout << endl;
            }
        }  

        
        
};

template<class T>
class Stack : public DoubleList<T>{
public:
    Stack():DoubleList<T>(){

    }
    ~Stack(){
    }
    void push(T data){
        DoubleList<T>::push_front(data);
    }
    T pop(){
        return DoubleList<T>::pop_front();
    }
    T top(){
        return DoubleList<T>::head->data;
    }
    bool is_empty(){
        return DoubleList<T>::is_empty();
    }
    int size(){
        return DoubleList<T>::size();
    }
    void clear(){
        DoubleList<T>::clear();
    }

    void display(){
        if(is_empty()){
                cout << "El stack está vacío!" << endl;
            } 
            else{
                cout << "Tope->";
                Node<T>* temp = DoubleList<T>::head;
                while(temp!=nullptr){
                    cout << temp->data << ",";
                    temp = temp->next;
                }
                cout << "<-Fondo";
                cout << endl;
            }
    }
};