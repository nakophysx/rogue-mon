#include "Item.h"
#include "Pokemon.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

Item :: Item(){}

Item :: Item(unsigned int newId, string newName, unsigned short int newAmount)
{
  id = newId;
  name = newName;
  amount = newAmount;
}

Item :: ~Item(){}

unsigned short int Pokemon :: getId ()const
{
    return id;
}

string Pokemon :: getName ()const
{
    return name;
}

/*Item :: useItem(){//cet intitulé est bizarre
    amount--;
}*/

void Item :: action ()
{
  amount--;
  if( amount<=0)
  {
    
  }
}