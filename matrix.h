#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H
#include "node.h"
#include <stdexcept>

using namespace std;

#include <vector>
template <typename T>
class Matrix {
private:
	vector <Header<T>*>* x;
    vector <Header<T>*>* y;
    unsigned const rows, columns;

 /*   Node<T>* find(unsigned pX, unsigned pY){
        int contX;
        auto temp = root;
        while(temp->down && temp->posY <= pY){
            temp= temp->down;
        }
    }*/

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
/*
    bool set(unsigned pX , unsigned pY, T data){
        auto nodoInsert = find(pX,pY);
        if(!nodoInsert){
            nodoInsert= new Node<T>(pX,pY,data);

        }
        return false;
	}
*/

/*
    T operator()(unsigned, unsigned) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    */

    void print() const{
        int i;
        int cont= 0;
        for(auto it = y->cbegin() ; it != y->cend() ; it++){
            auto temp = (*it)->next;
                while (temp) {
                    while (cont++ < temp->posX)
                        cout << 0 << " ";
                    cout << temp->data << " ";
                    temp = temp->right;
                }
                while (cont++ < columns){
                    cout << 0 <<  " " ;
                }
                cont = 0;
                cout << endl;

        }
    }
	
    //~Matrix();

};

#endif //SPARSE_MATRIX_MATRIX_H