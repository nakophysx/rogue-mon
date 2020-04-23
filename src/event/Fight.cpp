#include "Player.h"
#include "Pokemon.h"
#include "WildPok.h"
#include "Attack.h"
#include "Item.h"
#include "Fight.h"
#include "Component.h"
#include "InheritedEvents.h"
#include "Event.h"
//#include "../player/Player.h"
#include <iostream> //testing/debug only 
#include <string>
#include <fstream>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "sdlTools.h"



using namespace std;



Fight :: Fight (Player& newme, WildPok & newopposant)
{
    me = &newme;
    opposant = &newopposant;
}

Fight :: ~Fight () {}

Pokemon* Fight :: choicePok (Pokemon* old)
{   
    SDL_Event event;
    
    box<< "Quel Pokemon voulez-vous utliser ? " <<endl;
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case 1: if (old!= me->getPokemon(0)) return me->getPokemon(0);

                case 2 :if ((1<me->getNbPokemon()) && (old!= me->getPokemon(1))) return me->getPokemon(1);

                case 3 :if ((2<me->getNbPokemon()) && (old!= me->getPokemon(2))) return me->getPokemon(2); 
                case 4 :if ((3<me->getNbPokemon()) && (old!= me->getPokemon(3))) return me->getPokemon(3); 
                case 5 :if ((4<me->getNbPokemon()) && (old!= me->getPokemon(4))) return me->getPokemon(4);
                case 6 :if ((5<me->getNbPokemon()) && (old!= me->getPokemon(5))) return me->getPokemon(5);
            }
        //Faut-il faire d'autre cas ?
    } 

}

void Fight :: raid  (Pokemon* Pok)
{
    unsigned short int att;

     box << "Quelle attaque voulez-vous effectuer ?  1 est " << Pok->getMyAttacks(0).getName(); // étendre avec un pour quand on aura plus d'attques
     cin>>att;

    effectsatt(&(Pok->getMyAttacks(att-1)), Pok); 

}

void Fight :: effectsatt (Attack* att, Pokemon* Pok)
{
    opposant->setHp( opposant->getHp()- (att->getImpact()*(Pok->getAtk())-opposant->getDef()));
    Pok->defIncrease( att->getGainDefense() );
    Pok->atkIncrease( att->getGainAtk() );
}

void Fight :: acitem(Pokemon* Pok) // à completer
{
    if (me->getNbItem() == 0) {return;}
    int numit;
    Item thisItem;
     cout<< "Quel objet vous-vous utiliser ?";
     cin>> numit;
    thisItem = me->getItem(numit-1); 
    thisItem.action(Pok);
}

/*
void Fight :: action ()
{
    Pokemon* Pok= new Pokemon;
    char act;
    Pok=me->getPokemon(0);
    if(!me->playerIsDead() && !opposant->wildIsDead())//fonction à écrire
    {
        if (me->pokIsDead())
            {act = 's';}
        else 
        {
            do {
                cout<< "Quelle action voulez-vous effectuer ? x: attaquer; c: item; s: changer de pokemon" <<endl;
                cin>>act;
            }while (act != 'x' || act != 'c' || act != 's');
        }
        switch (act)
            {
                case 'x': raid(Pok); break;

                case 'c': acitem(Pok); break;

                case 's': choicePok(Pok); break;

               default : break;

            }

    }
    else
    {
        if (me->playerIsDead()){ cout<<"Vous avez perdu";}// bizarre pour l'appel
        else { cout<<"Vous avez gagné ! Bravo !!!";}
    }

     delete Pok;

}*/

short int Fight::init(unsigned short int dimX, unsigned short int dimY, SDL_Renderer * renderer) 
{
    cout<<"Fight correct initialisation"<<endl; //debug

    box = make_shared<DialogueBox>();
    
    Pokemon* Pok= new Pokemon;
    Pok=me->getPokemon(0);


    // init components
    box->_init(dimX, dimY, renderer);
    for (short unsigned int i = 0; i < components.size(); i++) {
        if (!(components[i]->_init(dimX, dimY, renderer))) return 1;
    }

    //init background
    back_text = loadImage(background_source);
    background = SDL_CreateTextureFromSurface(renderer, back_text);

    //init file ifstream
    myfile.open(txt_source);

    return run(renderer);
}

short int Fight::run(SDL_Renderer * renderer) {
  bool hasFinished = false;
  SDL_Event evt;
  cout<<"Launched cinematic loop"<<endl; //debug
  read(box);
  do{ 
    //render bg
    if (SDL_RenderCopy(renderer, background, NULL, NULL) < 0) 
    {
        printf("Box: No renderer error. Forcing exit...\n" );
        return ERRCODE_NO_RENDER;
    }

    // update every component
    if (box->_update(renderer) > 0)
    {
        // error during rendering, exit
        break;
    }

    for (unsigned int i = 0; i < components.size(); i++) 
    {
        if ((!components[i]->_update(renderer))>0)
            return 1;
    }

    if(opposant->wildIsDead())
    {
        box<<"Vous avez gagné le combat";
        hasFinished = true;
    }

    
    if(me->pokIsDead())
    {
        box<<"Votre Pokémon n'a plus de point de vie";
        if (me->playerIsDead)
        {
            box<<"Vous avez perdu";
            hasFinished = true;
        }
        else choicePok(Pok);//choice n'est pas en sdl
    }



    //render
    SDL_RenderPresent(renderer);
    // event treatement
    while ( SDL_PollEvent(&evt) ) 
    {
        switch(event.type)
        {
            case SDL_QUIT:
                hasFinished= true;
                break;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.sym) 
                {
                    case SDLK_x : raid(Pok); break;
                
                    case SDLK_c : acitem(Pok); break;

                    case SDLK_s : choicePok(Pok); break;
                }
            default: break;
        }
        //Je sais pas si il faut mettre le tour de l'opposant ici 
    }
    // ou si il faut le faire jouer ici
    } while (!hasFinished);
    //end of event
    delete Pok
  return 0;
}
