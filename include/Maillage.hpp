#ifndef Maillage3D_Maillage_hpp
#define Maillage3D_Maillage_hpp
#include <vector>
#include <string>
#include "./Sommet.hpp"
#include "./Face.hpp"

// Classe Maillage
class Maillage{
    private:
        std::vector<Sommet> sommets;
        std::vector<Face> faces;
    public:
        Maillage();
        Maillage(const std::string &fichierPly);
        ~Maillage();

        void ajouterSommet(int indice, float x, float y, float z);
        void ajouterFace(int indice, int s1, int s2, int s3);
        void centrer();
        void homotethie(const float facteur);
        void bruitage(const float coefficient);
        void inverserNormales();
        float calculerSurface();
        void sauvegarderPLY(const std::string &nomFichier);
        void afficherSommets();
        void afficherFaces();
};
#endif // Maillage3D_Maillage_hpp
