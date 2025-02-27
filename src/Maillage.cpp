#include <iostream>
#include <fstream>
#include <random>
#include "../include/Maillage.hpp"
#include "../include/Vecteur3D.hpp"

Maillage::Maillage(){
    ajouterSommet(0, -1.0f, -1.0f, -1.0f);
    ajouterSommet(1,  1.0f, -1.0f, -1.0f);
    ajouterSommet(2, -1.0f,  1.0f, -1.0f);
    ajouterSommet(3,  1.0f,  1.0f, -1.0f);
    ajouterSommet(4, -1.0f, -1.0f,  1.0f);
    ajouterSommet(5,  1.0f, -1.0f,  1.0f);
    ajouterSommet(6, -1.0f,  1.0f,  1.0f);
    ajouterSommet(7,  1.0f,  1.0f,  1.0f);

    ajouterFace(0, 3, 1, 0);
    ajouterFace(1, 2, 3, 0);
    ajouterFace(2, 3, 7, 1);
    ajouterFace(3, 5, 1, 7);
    ajouterFace(4, 6, 5, 7);
    ajouterFace(5, 5, 6, 4);
    ajouterFace(6, 4, 6, 2);
    ajouterFace(7, 4, 2, 0);
    ajouterFace(8, 6, 7, 3);
    ajouterFace(9, 3, 2, 6);
    ajouterFace(10, 1, 5, 0);
    ajouterFace(11, 4, 0, 5);
};

Maillage::Maillage(const std::string &fichierPly){
    std::ifstream fichier(fichierPly);
    std::string ligne;
    int nbSommets = 0, nbFaces = 0;

    // Retrouver le nombre de sommets et de faces
    while (getline(fichier, ligne)){
        if (ligne.find("element vertex") != std::string::npos){
            size_t pos = ligne.find_last_of(" ");
            nbSommets = std::stoi(ligne.substr(pos + 1));
        }
        
        if (ligne.find("element face") != std::string::npos){
            size_t pos = ligne.find_last_of(" ");
            nbFaces = std::stoi(ligne.substr(pos + 1));
        }
        
        if (ligne == "end_header"){
            break;
        }
    }

    // Sommets
    for (int i = 0; i < nbSommets; ++i){
        getline(fichier, ligne);
        size_t pos1 = 0, pos2 = 0;

        pos2 = ligne.find(" ", pos1);
        float x = std::stod(ligne.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = ligne.find(" ", pos1);
        float y = std::stod(ligne.substr(pos1, pos2 - pos1));
        
        pos1 = pos2 + 1;
        float z = std::stod(ligne.substr(pos1));

        ajouterSommet(i, x, y, z);
    }

    // Faces
    for (int i = 0; i < nbFaces; ++i){
        getline(fichier, ligne);
        size_t pos1 = 0, pos2 = 0;

        pos2 = ligne.find(" ", pos1);
        int nbIndices = std::stoi(ligne.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = ligne.find(" ", pos1);
        int s1 = std::stoi(ligne.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = ligne.find(" ", pos1);
        int s2 = std::stoi(ligne.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        int s3 = std::stoi(ligne.substr(pos1));

        ajouterFace(nbIndices, s1, s2, s3);
    }

    fichier.close();
};

Maillage::~Maillage(){};

void Maillage::ajouterSommet(int indice, float x, float y, float z){
    this->sommets.push_back(Sommet(indice, x, y, z));
};

void Maillage::ajouterFace(int indice, int s1, int s2, int s3){
    this->faces.push_back(Face(indice, s1, s2, s3));
    this->sommets[s1].ajouterVoisin(s2);
    this->sommets[s1].ajouterVoisin(s3);
    this->sommets[s2].ajouterVoisin(s1);
    this->sommets[s2].ajouterVoisin(s3);
    this->sommets[s3].ajouterVoisin(s1);
    this->sommets[s3].ajouterVoisin(s2);
};

void Maillage::centrer(){
    float xMin = sommets[0].getX();
    float yMin = sommets[0].getY();
    float zMin = sommets[0].getZ();

    float xMax = sommets[0].getX();
    float yMax = sommets[0].getY();
    float zMax = sommets[0].getZ();

    for (Sommet &sommet: this->sommets){
        xMin = std::min(xMin, sommet.getX());
        yMin = std::min(yMin, sommet.getY());
        zMin = std::min(zMin, sommet.getZ());

        xMax = std::max(xMax, sommet.getX());
        yMax = std::max(yMax, sommet.getY());
        zMax = std::max(zMax, sommet.getZ());
    }

    float xCentre = (xMin + xMax) / 2;
    float yCentre = (yMin + yMax) / 2;
    float zCentre = (zMin + zMax) / 2;

    for (Sommet &sommet: this->sommets){
        sommet.translater(-xCentre, -yCentre, -zCentre);
    }
};

void Maillage::homotethie(const float facteur){
    for (Sommet &sommet: this->sommets){
        sommet.setX(sommet.getX() * facteur);
        sommet.setY(sommet.getY() * facteur);
        sommet.setZ(sommet.getZ() * facteur);
    }
};

void Maillage::bruitage(const float coefficient){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<float> dis(-coefficient, coefficient);

    for (Sommet &sommet: this->sommets){
        float bx = dis(gen);
        float by = dis(gen);
        float bz = dis(gen);

        sommet.setX(bx);
        sommet.setY(by);
        sommet.setZ(bz);
    }
};

void Maillage::inverserNormales(){
    for (Face &face: this->faces){
        int s = face.getSommet(1);
        face.setSommet(1, face.getSommet(2));
        face.setSommet(2, s);
    }
};

float Maillage::calculerSurface(){
    float surface = 0.0f;

    for (Face &face: this->faces){
        int indiceS1 = face.getSommet(0);
        int indiceS2 = face.getSommet(1);
        int indiceS3 = face.getSommet(2);

        Sommet &s1 = this->sommets[indiceS1];
        Sommet &s2 = this->sommets[indiceS2];
        Sommet &s3 = this->sommets[indiceS3];

        Vecteur3D vecteur1(s1, s2);
        Vecteur3D vecteur2(s1, s3);

        Vecteur3D produitVectoriel = vecteur1.produitVectoriel(vecteur2);
        float aire = 0.5f * produitVectoriel.norme();

        surface += aire;
    }

    return surface;
};

void Maillage::sauvegarderPLY(const std::string &nomFichier){
    std::ofstream fichier("../maillages/" + nomFichier + ".ply");

    fichier << "ply\n";
    fichier << "format ascii 1.0\n";
    fichier << "comment zipper output\n";
    fichier << "element vertex " << sommets.size() << "\n";
    fichier << "property float x\n";
    fichier << "property float y\n";
    fichier << "property float z\n";
    fichier << "element face " << faces.size() << "\n";
    fichier << "property list uchar int vertex_indices\n";
    fichier << "end_header\n";

    for (Sommet &sommet: this->sommets){
        fichier << sommet.getX() << " " << sommet.getY() << " " << sommet.getZ() << "\n";
    }

    for (Face &face: this->faces){
        std::array<int, 3> sommets = face.getSommets();
        fichier << "3 " << sommets[0] << " " << sommets[1] << " " << sommets[2] << "\n";
    }

    fichier.close();
};

void Maillage::afficherSommets(){
    for (Sommet &sommet: this->sommets){
        sommet.afficher();
    }
};

void Maillage::afficherFaces(){
    for (Face &face: this->faces){
        face.afficher();
    }
};
