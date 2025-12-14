#pragma once

#include <QObject>
#include "../iointerface.h"
class CanBase : public QObject
{
	Q_OBJECT

public:
	CanBase(QObject *parent);
	~CanBase();
};
