#include "Pixel.h"
#include "Image.h"

#include <fstream>
#include <cassert>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

// Constructeur par défaut de la classe: initialise dimx et dimy à 0
// ce constructeur n'alloue pas de pixel
Image::Image()
{
    dimx = 0;
    dimy = 0;
    tab = NULL;
}

// Constructeur de la classe: initialise dimx et dimy (après vérification)
// puis alloue le tableau de pixel dans le tas (image noire)
Image::Image(const unsigned int dimensionX, const unsigned int dimensionY)
{
    dimx = dimensionX;
    dimy = dimensionY;
    tab = new Pixel[dimx * dimy];
}

//Destructeur de la classe: déallocation de la mémoire du tableau de pixels
//et mise à jour des champs dimx et dimy à 0
Image::~Image()
{
    delete [] tab;
    tab = NULL;
    dimx = 0;
    dimy = 0;
}

// Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
// la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
Pixel& Image::getPix(const unsigned int x, const unsigned int y) const
{
    assert(x < dimx);
    assert(y < dimy);
    return tab[y*dimx+x];
}

// Mutateur : modifie le pixel de coordonnées (x,y)
void Image::setPix (const unsigned int x, const unsigned int y, const Pixel &couleur)
{
    assert(x < dimx);
    assert(y < dimy);
    tab[y*dimx+x] = couleur;
}

// Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
void Image::dessinerRectangle(const int Xmin, const int Ymin, const int Xmax, const int Ymax, const Pixel couleur)
{
    assert(Xmin < Xmax);
    assert(Ymin < Ymax);
    for(int i = Xmin; i <= Xmax; i++)
    {
        for(int j = Ymin; j <= Ymax; j++)
        {
            setPix(i,j,couleur);
        }
    }
}

// Efface l'image en la remplissant de la couleur en paramètre
// (en appelant dessinerRectangle avec le bon rectangle)
void Image::effacer(const Pixel couleur)
{
    dessinerRectangle(0,0,dimx-1,dimy-1,couleur);
}

// Effectue une série de tests vérifiant que le module fonctionne et
// que les données membres de l'objet sont conformes
void Image::testRegression()
{
    dimx = 10;
    dimy = 10;
    tab = new Pixel[dimx * dimy];

    cout << (int)getPix(1,1).getRouge() << endl; // 0
    Pixel c(255,0,0);
    setPix(1,1,c);
    cout << (int)getPix(1,1).getRouge() << endl; // 255
    dessinerRectangle(0,0,2,2,c);
    cout << (int)getPix(2,2).getRouge() << endl; // 255
    effacer(c);
    cout << (int)getPix(5,5).getRouge() << endl; // 255

    afficherConsole();
    sauver("./data/save.txt");
    ouvrir("./data/save.txt");
}

void Image::sauver(const string & filename) const
{
    ofstream fichier (filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; ++y)
    {
        for(unsigned int x=0; x<dimx; ++x)
        {
            Pixel& pix = getPix(x,y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
        fichier << endl;
    }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}

void Image::ouvrir(const string & filename)
{
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
    unsigned int r,g,b;
    string mot;
    fichier >> mot >> dimx >> dimy >> mot;
    assert(dimx > 0 && dimy > 0);
    if (tab != NULL)
        delete [] tab;
    tab = new Pixel [dimx * dimy];
    for(unsigned int y=0; y<dimy; ++y)
    {
        for(unsigned int x=0; x<dimx; ++x)
        {
            fichier >> r >> g >> b;
            getPix(x,y).setRouge(r);
            getPix(x,y).setVert(g);
            getPix(x,y).setBleu(b);
        }
    }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole() const
{
    cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy; ++y)
    {
        for(unsigned int x=0; x<dimx; ++x)
        {
            Pixel& pix = getPix(x,y);
            cout << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
        cout << endl;
    }
}

float Image::to_degree(float rad)
{
    return 180.f * rad/M_PI;
}

float Image::to_rad(float deg)
{
    return M_PI*deg/180.f;
}

Complex Image::rotate(const Complex & p, float cx, float cy, float theta_deg)
{
    Complex rot = make_complex_expo( 1, to_rad(theta_deg));
    Complex tr = make_complex( cx, cy);
    return ((p-tr)*rot)+tr;
}

void Image::afficher()
{
    const int dimW = 200;
    const int dimH = 200;
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Texture * image = NULL;
    int w, h;
    float zoom = 1;
    bool quit = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
    SDL_Quit();
    exit(1);
    }

    window = SDL_CreateWindow("Module image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimW, dimH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    sauver("./data/printed.ppm");
    int coefX = 0;
    int coefY = 0;
    while (quit == false) {
	SDL_Event e;
	if ( SDL_PollEvent(&e) ) {
		if (e.type == SDL_QUIT)
			quit = true;
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			quit = true;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_t)
			zoom++;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_z)
			coefY--;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
			coefX--;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
			coefY++;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d)
			coefX++;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f)
			if(zoom > 1)
                zoom--;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_g)		rotate();
		
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_h)		rotate();
	}
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderClear(renderer);
	image = IMG_LoadTexture(renderer, "./data/printed.ppm");
	SDL_Rect texr;
	SDL_QueryTexture(image, NULL, NULL, &w, &h);
    texr.x = (dimW/2)-(w*zoom/2)+coefX;
    texr.y = (dimH/2)-(h*zoom/2)+coefY;
    texr.w = w*zoom;
    texr.h = h*zoom;
	SDL_RenderCopy(renderer, image, NULL, &texr);
	SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}