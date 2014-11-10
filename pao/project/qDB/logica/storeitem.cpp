#include <string>

#include "storeitem.h"
#include "exceptions.h"

using std::string;

StoreItem::StoreItem(string name, string dev, double cost)
    : title(name), developer(dev), quality(0), nratings(0),  price(cost)
{
    if (price < 0)
        price = 0;
}
StoreItem::StoreItem(string name, string dev, double rate, int nrat, double cost)
    : title(name), developer(dev), quality(rate),  nratings(nrat), price(cost)
{
    if (price < 0)
            price = 0;
    // Quality = 0 => item not yet rated
    if (quality < 0 || quality > 5.0)
        quality = 0;
    if (nratings < 0)
        nratings = 0;
    if (nratings > 0 && quality == 0)
        throw ConstructorException("The number of ratings can not be greater than zero while quality is not set");
    if (nratings == 0 && quality > 0)
        throw ConstructorException("Quality can not be greater than zero while no votes are set");
}

string StoreItem::getTitle() const
{
    return title;
}
string StoreItem::getDeveloper() const
{
    return developer;
}
double StoreItem::getQuality() const
{
    return quality;
}
int StoreItem::getRatings() const
{
    return nratings;
}
double StoreItem::getPrice() const
{
    return price;
}
void StoreItem::setTitle(const string t)
{
    title = t;
}
void StoreItem::setDeveloper(const string dev)
{
    developer = dev;
}
void StoreItem::setPrice(const double p)
{
    price = p;
}
void StoreItem::setQuality(const double q)
{
    quality = q;
}
void StoreItem::setRatings(const int rat)
{
    nratings = rat;
}
