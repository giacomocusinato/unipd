#include "app.h"

using std::string;

App::App(string name, string dev, category cat, string local, double cost)
    : StoreItem(name, dev, cost), genre(cat), localization(local) {}
App::App(string name, string dev, double rate, int nrat, category cat, string local, double cost)
    : StoreItem(name, dev, rate, nrat, cost), genre(cat), localization(local) {}

App::category App::getCategoty() const
{
    return genre;
}

string App::getLocalization() const
{
    return localization;
}

bool App::isGlobal() const
{
    return localization == "Global";
}

App* App::clone() const
{
    return new App(*this);
}
