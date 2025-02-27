#ifndef Maillage3D_Face_hpp
#define Maillage3D_Face_hpp
#include <array>

// Classe Face
class Face{
    private:
        std::array<int, 3> sommets;
        int indice;

    public:
        Face();
        Face(const int i, const int s1, const int s2, const int s3);
        Face(const Face &f);

        int getSommet(const int pos);
        std::array<int, 3> getSommets();
        int getIndice();
        
        void setSommet(const int pos, const int s);
        void setIndice(const int i);
        
        void afficher();
};
#endif // Maillage3D_Face_hpp
