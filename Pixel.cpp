#include "Pixel.h"

#include <iostream>
using namespace std;

// Constructeur par défaut de la classe: initialise le pixel à la couleur noire
Pixel::Pixel()
{
    r = 0;
    g = 0;
    b = 0;
}

// Constructeur de la classe: initialise r,g,b avec les paramètres
Pixel::Pixel (const unsigned char nr,const unsigned char ng,const unsigned char nb)
{
    r = nr;
    g = ng;
    b = nb;
}

// Accesseur : récupère la composante rouge du pixel
unsigned char Pixel::getRouge () const
{
    return r;
}

// Accesseur : récupère la composante verte du pixel
unsigned char Pixel::getVert () const
{
    return g;
}

// Accesseur : récupère la composante bleue du pixel
unsigned char Pixel::getBleu () const
{
    return b;
}

// Mutateur : modifie la composante rouge du pixel
void Pixel::setRouge (const unsigned char sr)
{
    r = sr;
}

// Mutateur : modifie la composante verte du pixel
void Pixel::setVert (const unsigned char sg)
{
    g = sg;
}

// Mutateur : modifie la composante bleue du pixel
void Pixel::setBleu (const unsigned char sb)
{
    b = sb;
}
