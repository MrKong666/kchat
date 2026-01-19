#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#endif // GLOBAL_CPP
#include "global.h"

std::function<void(QWidget*)> repolish=[](QWidget*w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};
