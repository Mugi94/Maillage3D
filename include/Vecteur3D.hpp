#ifndef Maillage3D_Vecteur3D_hpp
#define Maillage3D_Vecteur3D_hpp
#include "./Sommet.hpp"

// Classe Vecteur3D
class Vecteur3D{
    private:
        float x, y, z;

    public:
        Vecteur3D();
        Vecteur3D(const float x, const float y, const float z);
        Vecteur3D(const Sommet &s1, const Sommet &s2);

        float getX() const;
        float getY() const;
        float getZ() const;

        float norme() const;
        Vecteur3D produitVectoriel(const Vecteur3D &v);
};
#endif // Maillage3D_Vecteur3D_hpp