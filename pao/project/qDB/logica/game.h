#ifndef GAME_H
#define GAME_H

#include <string>

#include "storeitem.h"

using std::string;

class Game : public StoreItem
{
public:
    enum category { Puzzle, Action, Platformer, Strategy };
private:
    category genre;
    bool xbranding;
public:
    Game(string, string, category, double=0, bool=false);
    Game(string, string, double, int, category, double=0, bool=false);

    category getCategory() const;
    bool isXbox() const;

    // Clone method for SmartPointer class
    Game* clone() const;
};
#endif // GAME_H
