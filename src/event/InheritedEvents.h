/**@file inherited events header file*/

#ifndef POKE_EVI_H
#define POKE_EVI_H

#include "Event.h"
#include "Component.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <fstream>
#include <memory>

/*------------------ TESTING BLOCK STRUCTURE ---------------------------------*/
struct data {
  int hp;
  int hp_max;
  int atk;
  int def;
};


/** @class Test class, first event
    @brief testing purposes only
    yo*/
class Test : public Event {
public :
  /** @brief see Event init() */
  short int init();

  /** @brief see Event run() */
  short int run();

private :
  data ennemy[2];
};
/*----------------------------------------------------------------------------*/

class Cinematic : public Event {
public :
  /** class constructor */
  Cinematic(std::string text_adress, std::string image_adress);
  /** @brief see Event init() */
  short int init(unsigned short int dimX, unsigned short int dimY, SDL_Renderer * render);
  /** @brief see Event run()*/
  short int run(SDL_Renderer * render);
private :
  /** @brief text reader */
  short int read(std::shared_ptr<DialogueBox> db);
  /** @brief cinematic text file adress */
  std::string txt_source;
  /** @brief background adress */
  std::string background_source;
  SDL_Texture * background;
  SDL_Surface * back_text;
  /** @brief text flux */
  std::ifstream myfile;
  /** @brief dialogue box for cinematic*/
  std::shared_ptr<DialogueBox> box;
};
/*----------------------------------------------------------------------------*/

/*class Healing : public Event {
public:
  Healing();
  ~Healing();
  short int init(unsigned short int dimX, unsigned short int dimY, SDL_Renderer * renderer, const Player & player);
};
*/
#endif
