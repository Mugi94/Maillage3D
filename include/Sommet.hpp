#ifndef Maillage3D_Sommet_hpp
#define Maillage3D_Sommet_hpp
#include <vector>

// Classe sommet
class Sommet{
    private:
        int indice;
        float x, y, z;
        std::vector<int> voisins;

    public:
        Sommet();
        Sommet(const int i, const float x, const float y, const float z);
        Sommet(const Sommet &s);

        int getIndice();
        float getX() const;
        float getY() const;
        float getZ() const;
        std::vector<int> getVoisins();

        void setIndice(const int i);
        void setX(const float x);
        void setY(const float y);
        void setZ(const float z);

        void ajouterVoisin(int s);
        void supprimerVoisin(int s);
        void translater(float dx, float dy, float dz);
        void afficher();
        void afficherVoisins();
};
#endif // Maillage3D_Sommet_hpp
