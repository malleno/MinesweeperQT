#include "filterisflagoncell.h"

FilterIsFlagOnCell::FilterIsFlagOnCell(QObject* pobj) : QObject(pobj)
{
}

bool FilterIsFlagOnCell::eventFilter(QObject* cell, QEvent* event){

    return true;
}
