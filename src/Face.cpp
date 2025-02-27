#include <iostream>
#include "../include/Face.hpp"

Face::Face(){
    this->indice = 0;
    this->sommets[0] = 0;
    this->sommets[1] = 1;
    this->sommets[2] = 2;
};

Face::Face(const int i, const int s1, const int s2, const int s3){
    this->indice = i;
    this->sommets[0] = s1;
    this->sommets[1] = s2;
    this->sommets[2] = s3;
};

Face::Face(const Face &f){
    this->indice = f.indice;
    this->sommets[0] = f.sommets[0];
    this->sommets[1] = f.sommets[1];
    this->sommets[2] = f.sommets[2];
};

int Face::getSommet(const int pos){
    if (pos >= 0 && pos < 3){
        return sommets[pos];
    } else{
        throw std::out_of_range("Position de sommet invalide : " + std::to_string(pos));
    }
};

std::array<int, 3> Face::getSommets(){
    return this->sommets;
};

int Face::getIndice(){
    return this->indice;
};

void Face::setSommet(const int pos, const int s){
    if (pos >= 0 && pos < 3){
        this->sommets[pos] = s;
    } else{
        throw std::out_of_range("Position de sommet invalide : " + std::to_string(pos));
    }
};

void Face::setIndice(const int i){
    this->indice = i;
};

void Face::afficher(){
    std::cout << "Face: " << this->indice << "(" 
    << this->sommets[0] << ", " 
    << this->sommets[1] << ", " 
    << this->sommets[2] 
    << ")" << std::endl;
};
