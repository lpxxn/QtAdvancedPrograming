#ifndef ZIPCODEITEM_H
#define ZIPCODEITEM_H


#include "global.h"
#include <QString>

struct ZipcodeItem
{
    explicit ZipcodeItem(int zipcode = InvalidZipcode,
             const QString &postOffice =QString(),
             const QString &county =QString(),
             const QString &state =QString())
        :zipcode(zipcode),postOffice(postOffice),
          county(county),state(state)
        {}
    bool operator <(const ZipcodeItem &other) const
    {
        return zipcode!=other.zipcode?zipcode<other.zipcode
                                    :postOffice<other.postOffice;
    }

    int zipcode;
    QString postOffice;
    QString county;
    QString state;
};

#endif // ZIPCODEITEM_H
