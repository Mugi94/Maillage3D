#include "../include/Vecteur3D.hpp"
#include <cmath>

Vecteur3D::Vecteur3D(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
};

Vecteur3D::Vecteur3D(const float x, const float y, const float z){
    this->x = x;
    this->y = y;
    this->z = z;
};

Vecteur3D::Vecteur3D(const Sommet &s1, const Sommet &s2){
    this->x = s2.getX() - s1.getX();
    this->y = s2.getY() - s1.getY();
    this->z = s2.getZ() - s1.getZ();
};

float Vecteur3D::getX() const{
    return this->x;
};

float Vecteur3D::getY() const{
    return this->y;
};

float Vecteur3D::getZ() const{
    return this->z;
};

float Vecteur3D::norme() const{
    return std::sqrt(this->x * x + this->y * y + this->z * z);
};

Vecteur3D Vecteur3D::produitVectoriel(const Vecteur3D &v){
    float x = (this->y * v.z) - (this->z * v.y);
    float y = (this->z * v.x) - (this->x * v.z);
    float z = (this->x * v.y) - (this->y * v.x);
    
    return Vecteur3D(x, y, z);
};
