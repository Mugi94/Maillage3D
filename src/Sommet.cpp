#include <iostream>
#include <algorithm>
#include "../include/Sommet.hpp"

// -----------------------
//  Constructeurs
// -----------------------

Sommet::Sommet(){
    this->indice = 0;
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
};

Sommet::Sommet(const int i, const float x, const float y, const float z){
    this->indice = i;
    this->x = x;
    this->y = y;
    this->z = z;
};

Sommet::Sommet(const Sommet &s){
    this->indice = s.indice;
    this->x = s.x;
    this->y = s.y;
    this->z = s.z;
};


// -----------------------
//  Getters et Setters
// -----------------------

int Sommet::getIndice(){
    return this->indice;
};

float Sommet::getX() const{
    return this->x;
};

float Sommet::getY() const{
    return this->y;
};

float Sommet::getZ() const{
    return this->z;
};

std::vector<int> Sommet::getVoisins(){
    return this->voisins;
}

void Sommet::setIndice(const int i){
    this->indice = i;
};

void Sommet::setX(const float x){
    this->x = x;
};

void Sommet::setY(const float y){
    this->y = y;
};

void Sommet::setZ(const float z){
    this->z = z;
};

// -----------------------
//  Méthodes
// -----------------------

void Sommet::ajouterVoisin(int s){
    if (std::find(voisins.begin(), voisins.end(), s) == voisins.end()){
        voisins.push_back(s);
    }
};

void Sommet::supprimerVoisin(int s){
    auto it = std::find(voisins.begin(), voisins.end(), s);
    if (it != voisins.end()){
        voisins.erase(it);
    }
};

void Sommet::translater(float dx, float dy, float dz) {
    this->x += dx;
    this->y += dy;
    this->z += dz;
}

void Sommet::afficher(){
    std::cout << "Sommet: " << this->indice << "(" 
    << this->x << ", " 
    << this->y << ", " 
    << this->z 
    << ")" << std::endl;
};

void Sommet::afficherVoisins(){
    std::cout << "Voisins du sommet " << indice << " : [";
    for (size_t i = 0; i < voisins.size(); ++i){
        std::cout << voisins[i];
        if (i < voisins.size() - 1){
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
};
