#include "Pokemon.h"
#include "Squirtle.h"
#include "Attack.h"
#include "First.h"
#include "Second.h"

#include <iostream>
//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;



Squirtle  :: Squirtle  ()
{
    id = 007;
    maxHp = 100;
    Hp = 100;
    name = "Squirtle";
    type = 1; // 1= Water
    lvl = 1;
    atk = 10; // j'y connais pas grand chose il faut peut etre modifier ces valeurs avec def
    sAtk = 2;
    def = 10 ;
    sDef = 2;
    speed = rand()%10-1;
    myAttacks[0]= new First;
    myAttacks[1]= new Second;

}

Squirtle  :: ~Squirtle  () {}
