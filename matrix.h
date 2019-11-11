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

    Node<T>* findNode(unsigned pX, unsigned pY){
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

    Node<T>* findLeft(unsigned pX, unsigned pY){
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
   Node<T>* findTop(unsigned pX, unsigned pY){
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
	bool remove(unsigned pX , unsigned pY){
        auto temp = findNode(pX,pY);
        if(temp){
            auto temptop = findTop(pX,pY);
            auto templeft = findLeft(pX,pY);
            if(!temptop){
                Header<T>* t = (*x)[pX];
                t->next = temp->down;
            }
            else{
                temptop->down = temp->down;
            }
            if(!temptop){
                Header<T>* t = (*y)[pY];
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
    bool set(unsigned pX , unsigned pY, T data){
        auto temp = findNode(pX,pY);
        if(!temp){
            if(data == 0)
                return false;
            auto arriba = findTop(pX,pY);
            auto izquierda = findLeft(pX,pY);
            auto newNode = new Node<T>(pX,pY,data);
            if(!arriba){
                Header<T>* t = ((*x)[pX]);
                newNode->down = t->next;
                t->next = newNode;
            }
            else{
                newNode->down = arriba->down;
                arriba->down = newNode;

            }
            if(!izquierda){
                Header<T>* t2 = ((*y)[pY]);
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
            temp->data = data;
            return true;
        }
	}



    T operator()(unsigned _x, unsigned _y)const {
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
    /* Matrix<T> operator*(T scalar) const;
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
                    while (cont++ < temp->posX) {
                        cout << setw(4);
                        cout << 0 << " ";
                    }
                    cout << setw(4);
                    cout << temp->data << " ";
                    temp = temp->right;
                }
                while (cont++ < columns){
                    cout << setw(4);
                    cout << 0 <<  " " ;
                }
                cont = 0;
                cout << endl;

        }
    }
	
    //~Matrix();

};

#endif //SPARSE_MATRIX_MATRIX_H