#include "game.h"

Game::Game(string name, string dev, category cat, double cost, bool brand)
    : StoreItem(name, dev, cost), genre(cat), xbranding(brand) {}
Game::Game(string name, string dev, double rate, int nrat, category cat, double cost, bool brand)
    : StoreItem(name, dev, rate, nrat, cost), genre(cat), xbranding(brand) {}

Game::category Game::getCategory() const
{
    return genre;
}

bool Game::isXbox() const
{
    return xbranding;
}

Game* Game::clone() const
{
    return new Game(*this);
}
