#include <iostream>
#include "../include/Sommet.hpp"
#include "../include/Face.hpp"
#include "../include/Maillage.hpp"
#include "../include/Vecteur3D.hpp"

int main() {
    Maillage maillage("../maillages_exemple/01_cube.ply");

    std::cout << "Par défaut" << std::endl;
    maillage.afficherSommets();
    maillage.afficherFaces();

    std::cout << "Surface = " << maillage.calculerSurface() << std::endl;

    std::cout << "\nHomotéthie" << std::endl;
    maillage.homotethie(2);
    maillage.afficherSommets();

    std::cout << "\nBruitage" << std::endl;
    maillage.bruitage(2);
    maillage.afficherSommets();

    std::cout << "\nAvant Inversion normales" << std::endl;
    maillage.afficherFaces();

    std::cout << "\nAprès Inversion normales" << std::endl;
    maillage.inverserNormales();
    maillage.afficherFaces();
    
    return 0;
}
