#ifndef STOREITEM_H
#define STOREITEM_H

#include <string>
using std::string;

class StoreItem
{
public:
    StoreItem(string, string, double=0);
    StoreItem(string, string, double, int, double=0);
    virtual StoreItem* clone() const = 0;
    inline virtual ~StoreItem() {}

    string getTitle() const;
    string getDeveloper() const;
    double getPrice() const;
    double getQuality() const;
    int getRatings() const;
    void setTitle(const string);
    void setDeveloper(const string);
    void setPrice(const double);
    void setQuality(const double);
    void setRatings(const int);


    bool highQuality() const;
    bool topRated() const;
private:
    string title;
    string developer;
    double quality;
    int nratings;
    double price;
};

#endif // STOREITEM_H
