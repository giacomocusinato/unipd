#ifndef APP_H
#define APP_H

#include <string>

#include "storeitem.h"

using std::string;

class App : public StoreItem
{
public:
    enum category { Social, News, Multimedia, Utility };
private:
    category genre;
    string localization;
public:
    // App constructors, localization is set to default 'Global'
    App(string, string, category, string="Global", double=0);
    App(string, string, double, int, category, string="Global", double=0);

    category getCategoty() const;
    string getLocalization() const;

    bool isGlobal() const;

    // Clone method for SmartPointer class
    App* clone() const;
};

#endif // APP_H
