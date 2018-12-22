#ifndef _IMAGE
#define _IMAGE

#include "Pixel.h"

/*! \mainpage
Ce module image à été realisé par :

Alexandre DEVILLERS
Imran KRIMI
Aymen AZOUI

Il est constitué d'une classe pixel et d'un classe image dépendante de cette classe pixel.

Ce module utilise la librarie SDL2.

Plusieurs fonctions sont disponibles en public dans la classe image et pixel, pour les voir et connaître leurs descriptions ou les paramètres qu'elles prennent, vous devez utiliser la documentation doxygene.

Ce module permet de dessiner des rectangles de différentes couleurs puis de les afficher en mode console ou fenêtré.
*/

/**
* \file Pixel.h
* \author {AZOUI Aymen,KRIMI Imran,DEVILLERS Alexandre}
* \brief Définit une image.
* \details Cette classe définit une image constitué d'un tableau de taille dimx dimy
*/

class Image
{
public:


    /**
    * \brief Le constructeur par défaut de la classe.
    * \details  Initialise l'image par default. Initialise dimx et dimy a 0. Et n'alloue pas de pixel.
    */
// Constructeur par défaut de la classe: initialise dimx et dimy à 0
// ce constructeur n'alloue pas de pixel
    Image ();

    /**
    * \brief Le constructeur de la classe à 2 parametre.
    * \details Initialise dimx et dimy avec les paramètres puis alloue le tableau de pixel sur le tas .
    */
// Constructeur de la classe: initialise dimx et dimy (après vérification)
// puis alloue le tableau de pixel dans le tas (image noire)
    Image (const unsigned int dimensionX,const unsigned int  dimensionY);

    /**
    * \brief Le destructeur de la classe.
    * \details Remet dimx et dimy a 0, désalloue de la mémoire du tableau de pixels .
    */
// Destructeur de la classe: déallocation de la mémoire du tableau de pixels
// et mise à jour des champs dimx et dimy à 0
    ~Image ();

    /**
    * \brief Récupére un pixel.
    * \details Récupère le pixel de coordonnées (x,y) en vérifiant la validité des coordonnées.
    */
// Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
// la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
    Pixel& getPix (const unsigned int x, const unsigned int y) const;

    /**
    * \brief Modifie un pixel
    * \details Applique la couleur du pixel couleur au pixel de coordonnées (x,y).
    */
// Mutateur : modifie le pixel de coordonnées (x,y)
    void setPix (const unsigned int x, const unsigned int y, const Pixel &couleur);

    /**
    * \brief Dessine un rectangle sur l'image.
    * \details Prend les cordonnées d'un point min et d'un point max et coloris tout les pixels entre ces deux points
    */
// Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
    void dessinerRectangle (const int Xmin,const int Ymin,const int Xmax,const int Ymax,const Pixel couleur);

    /**
    * \brief Efface l'image part une couleur unie
    * \details Définit tout les pixels avec la couleur du pixel couleur
    */
// Efface l'image en la remplissant de la couleur en paramètre
// (en appelant dessinerRectangle avec le bon rectangle)
    void effacer (const Pixel couleur);

    /**
    * \brief Test les fonctionnalités du module image
    * \details Test toutes les fonctions du module image de différentes manière
    */
// Effectue une série de tests vérifiant que le module fonctionne et
// que les données membres de l'objet sont conformes
    void testRegression ();

    /**
    * \brief Sauvegarde dans un fichier l'image au format ppm
    *\details Prend le nom d'un fichier en paramètre et y stock chaque pixel avec 3 lignes d'entête pour le format ppm
    */
// Sauvgarde dans un fichier l'image
    void sauver(const string & filename) const;

    /**
    * \brief Ouvre une image depuis un fichier ppm ou txt
    *\details Prend le nom d'un fichier en paramétre et charge dans l'image les pixels stocké dans le fichier
    */
// Ouvre une image depuis un fichier
    void ouvrir(const string & filename);

    /**
    * \brief Affiche l'image dans la console
    *\details Affiche l'image couleur de pixel par couleur de pixel dans la console.
    */
// Affiche les valeurs dans la console
    void afficherConsole() const;

    /**
    * \brief Affiche l'image dans une fenêtre
    *\details Affiche l'image dans une fenêtre à l'aide de SDL2
    */
// Affiche l'image avec SDL2
    void afficher();

private:

    /**
    * \brief Les données membres privées de la classe.
    * \details dimx pour la taille en x, dimy pour la taille en y, et tab est le tableau de pixel qui définit l'image.
    */
    unsigned int dimx,dimy;
    Pixel * tab;

};

#endif
