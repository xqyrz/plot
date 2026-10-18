//
// Created by 25137 on 2026/10/18.
//

#ifndef PLOT_SIGNALINTERFACE_H
#define PLOT_SIGNALINTERFACE_H

#include "plug\interfacebase.h"
#include "nodemodel.h"
#include "nodedata.h"
class SignalInterface:public InterfaceBase
{
    Q_OBJECT
public:
    SignalInterface(PLUG::InputType inputType,QObject *parent = nullptr):
    InterfaceBase(parent)
    ,m_inputType(inputType)
    {
        m_inputPorts.clear();
        m_outputPorts.clear();
        m_name =(QtNodes::INNodeData(BaseModel::inputTypeMap.value(m_inputType)).type().name);
        for (int i = 0; i < 5; ++i)
        {
            m_inputPorts.append(m_inputType);
        }
        m_outputPorts.append(BaseModel::inputTOoutput.value(m_inputType));
    };
    QList<PLUG::InputType> in;
private:
    PLUG::InputType m_inputType;
};


#endif // PLOT_SIGNALINTERFACE_H
