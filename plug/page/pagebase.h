//
// Created by 25137 on 26-2-10.
//

#ifndef PAGEBASE_H
#define PAGEBASE_H

#include "interfacebase.h"


class PageBase:public InterfaceBase {

protected:
    inline static const  QString KEY =QStringLiteral("key");
    inline static const  QString CONFIG_KEY =QStringLiteral("config");

public:
     const char* getSignal(int index) const override {return nullptr;}
     const char* getSlot(int index) const override {return nullptr;}
};



#endif //PAGEBASE_H
