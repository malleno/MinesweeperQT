#pragma once
#include <QObject>
#include "cell.h"

class FilterIsFlagOnCell : public QObject
{
protected:
    virtual bool eventFilter(QObject*, QEvent*);
public:
    FilterIsFlagOnCell(QObject* pobj = 0);
};

