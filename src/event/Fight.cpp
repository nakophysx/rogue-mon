#include "Player.h"
#include "WildPok.h"
#include "Attack.h"
#include "Item.h"

#include <string>



Fight :: Fight (const Player& newme, const WildPok & newopposant)
{
    me = &newme;
    opposant = &newopposant;
}

Fight :: ~Fight ()

Pokemon* Fight :: choicePok (Pokemon* old)
{
    do{
        unsigned short int choice;
        std :: cout<< "Quel Pokemon voulez-vous utliser ? " <<endl;
        std :: cin>> choice;
    } while (((choice-1)>=0) && ((choice-1)<nbPokemon) && (old!= (&(choice-1))));//la derniere condition est bizarre
    return me.getPokemon (choice-1); 
}

void Fight :: raid  (Pokemon* Pok)
{
    unsigned short int att;

    std :: cout << "Quelle attaque voulez-vous effectuer ?  1 est " << me.myattacks[1]; // étendre avec un pour quand on aura plus d'attques
    std :: cin>>att;

    effectsatt(Pok.myattacks[att-1]);

}

void Fight :: effectsatt (const Attack& att)
{
    opposant.Hp= opposant.Hp- (att.impact*(Pok->atk)-opposant.def);
    attacker.def += att.gainatk;
    attacker.atk += att.gaindef;
}

void Fight :: acitem(Pokemon* Pok) // à completer
{
    if (me.nbItem= 0) {return;}
    int numit;
    Item thisItem;
    std :: cout<< "Quel objet vous-vous utiliser ?";
    std :: cin>> numit;
    thisItem= me.getItem(numit-1); 
    thisItem.action(Pok);
}

void Fight :: action ()
{
    Pok= new Pokemon;
    char act;
    Pok=me.getPokemon(0);
    if(!me.isDie() && !opposant.wildisdie)
    {
        do {
            std :: cout<< "Quelle action voulez-vous effectuer ? x: attaquer; c: item; s: changer de pokemon" <<endl;
            std :: cin>>act;
        }while (act != 'x' || act != 'c' || act != 's')
        switch (act)
            {
                case x: raid(Pok); break;

                case c: acitem(Pok);break;

                case s: choicePok(Pok); break;

                else : break;

            }
        
    }
    else
    {
        if (me.isDie()){std :: cout<<"Vous avez perdu"}// bizarre pour l'appelle
        else {std :: cout<<"Vous avez gagné ! Bravo !!!"}
    }   
       
     delete Pok;
   
}
