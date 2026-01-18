//
// Created by 25137 on 26-1-10.
//

#ifndef INTERFACEBASE_H
#define INTERFACEBASE_H



class InterfaceBase {
public:
    virtual ~InterfaceBase() = default;
    virtual const char* getSignal(int index) const=0;
    virtual const char* getSlot(int index) const=0;
};



#endif //INTERFACEBASE_H
