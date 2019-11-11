#ifndef SPARSE<_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *right, *down;
    T data;
    int posX;
    int posY;
public:
    explicit Node() : data{ 0 },posX { 0 }, posY{ 0 }, right{ nullptr }, down{ nullptr } {}
    explicit Node(int y, int x, T _data) {
        data = _data;
        posX = x;
        posY = y;
        right = nullptr;
        down = nullptr;
    }
    friend class Matrix<T>;
};

template <typename T>
struct Header{
    Node<T> *next;
    Header():next{nullptr}{}

};

#endif //SPARSE_MATRIX_NODE_H
