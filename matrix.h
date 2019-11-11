#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H
#include "node.h"
#include <stdexcept>

using namespace std;

#include <iomanip>
#include <vector>
template <typename T>
class Matrix {
private:
    vector <Header<T>*>* x;
    vector <Header<T>*>* y;
    unsigned const rows, columns;

    Node<T>* findNode(unsigned pY, unsigned pX){
        Node<T>* temp = ((*y)[pY])->next;
        if(temp)
            while(temp)
            {
                if(temp->posX == pX)
                    return temp;
                else
                    temp = temp->right;
            }
        return nullptr;

    }

    Node<T>* findLeft(unsigned pY, unsigned pX){
        Node<T>* temp = ((*y)[pY])->next;
        if(temp){
            if(temp->posX >= pX)
                return nullptr;
            if(temp->right){
                while(temp->right){
                    if(temp->right->posX >= pX)
                        return temp;
                    else{
                        temp=temp->right;
                    }
                }
            }
            return temp;
        }
        return nullptr;

    }
    Node<T>* findTop(unsigned pY, unsigned pX){
        Node<T>* temp = ((*x)[pX])->next;
        if(temp){
            if(temp->posY >= pY){
                return nullptr;}
            if(temp->down){
                while(temp->down){
                    if(temp->down->posY >= pY){
                        return temp;
                    }
                    else{
                        temp=temp->down;
                    }
                }
            }
            return temp;
        }
        return nullptr;
    }

public:
    Matrix(unsigned _rows, unsigned _columns):rows{_rows} , columns{_columns} {
        x = new vector<Header<T>*>;
        y = new vector<Header<T>*>;
        int i;
        for(i = 0; i < columns ; i++){
            (*x).emplace_back(new Header<T>);
        }
        for(i = 0; i < rows ; i++){
            (*y).emplace_back(new Header<T>);
        }

    }
    bool remove(unsigned ppY , unsigned ppX){
        auto temp = findNode(ppY,ppX);
        if(temp){
            auto temptop = findTop(ppY,ppX);
            auto templeft = findLeft(ppY,ppX);
            if(!temptop){
                Header<T>* t = (*x)[ppX];
                t->next = temp->down;
            }
            else{
                temptop->down = temp->down;
            }
            if(!temptop){
                Header<T>* t = (*y)[ppY];
                t->next = temp->right;
            }
            else{
                templeft->right = temp->right;
            }
            delete temp;
            return true;
        }
        return false;
    }
    bool set(unsigned ppY , unsigned ppX, T data){
        auto temp = findNode(ppY,ppX);
        if(!temp){
            if(data == 0)
                return false;
            auto arriba = findTop(ppY,ppX);
            auto izquierda = findLeft(ppY,ppX);
            auto newNode = new Node<T>(ppY,ppX,data);
            if(!arriba){
                Header<T>* t = ((*x)[ppX]);
                newNode->down = t->next;
                t->next = newNode;
            }
            else{
                newNode->down = arriba->down;
                arriba->down = newNode;

            }
            if(!izquierda){
                Header<T>* t2 = ((*y)[ppY]);
                newNode->right = t2->next;
                t2->next = newNode;
            }
            else{
                newNode->right = izquierda->right;
                izquierda->right = newNode;

            }
            return true;
        }
        else{
            if(data == 0){
                remove(ppY,ppX);
            }
            else{
                temp->data = data;
            }
            return true;
        }
    }


    T operator()(unsigned _y, unsigned _x)const {
        Node<T>* temp = ((*y)[_y])->next;
        if(temp)
            while(temp)
            {
                if(temp->posX == _x)
                    return temp->data;
                else
                    temp = temp->right;
            }
        return 0;
    }
    Matrix<T> operator*(T scalar) const{
        auto matrix = new Matrix<T>(rows,columns);
        for(int i = 0; i < rows ; i++){
            for(int j = 0; j < columns; j++){
                matrix->set(i,j,(operator()(i,j))*scalar);
            }
        }
        return *matrix;
    }

    Matrix<T> operator*(Matrix<T> other) const{
        if(other.rows != columns )
            throw new out_of_range("Matrices no se pueden multiplicar");
        auto matrix = new Matrix<T>(rows,other.columns);

        for(int i=0; i<rows; ++i) {
            for (int j = 0; j < other.columns; ++j) {
                T cont = 0;
                for (int z = 0; z < columns; ++z)
                    cont += operator()(i, z) * other.operator()(z, j);
                matrix->set(i,j,cont);
            }
        }
        return *matrix;
    }

    Matrix<T> operator+(Matrix<T> other) const{
        if(other.rows != rows || other.columns != columns )
            throw new out_of_range("Matrices de diferente tamaño");
        auto matrix = new Matrix<T>(rows,columns);
        for(int i = 0; i < rows; i++){
            for(int j= 0; j< columns ; j++){
                matrix->set(i,j,operator()(i,j) + other.operator()(i,j));
            }
        }
        return *matrix;
    }
    Matrix<T> operator-(Matrix<T> other) const{
        if(other.rows != rows || other.columns != columns )
            throw new out_of_range("Matrices de diferente tamaño");
        auto matrix = new Matrix<T>(rows,columns);
        for(int i = 0; i < rows; i++){
            for(int j= 0; j< columns ; j++){
                matrix->set(i,j,operator()(i,j) - other.operator()(i,j));
            }
        }
        return *matrix;
    }
    Matrix<T> transpose() const{
        auto matrix = new Matrix<T>(columns,rows);
        for(int i  = 0; i < rows ; i++){
            for(int j = 0; j < columns ; j++){
                matrix->set(j,i,operator()(i,j));
            }
        }
        return *matrix;
    }


    void print() const{
        int i;
        int cont= 0;
        for(auto it = y->cbegin() ; it != y->cend() ; it++){
            auto temp = (*it)->next;
            while (temp) {
                while (cont++ < temp->posX)
                    cout << setw(4) << 0 << " ";
                cout << setw(4) << temp->data << " ";
                temp = temp->right;
            }
            while (cont++ < columns){
                cout << setw(4)<< 0 <<  " " ;
            }
            cont = 0;
            cout << endl;
        }
    }

    //~Matrix();

};

#endif //SPARSE_MATRIX_MATRIX_H