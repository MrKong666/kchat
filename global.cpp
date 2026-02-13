#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#endif // GLOBAL_CPP
#include "global.h"
QString gate_url_prefix="";
std::function<void(QWidget*)> repolish=[](QWidget*w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};
std::function<QString(QString)>xorString=[](QString input){
    QString result = input;
    int totalLen = input.length();
    if (totalLen == 0) return result;

    // 使用原始长度计算密钥，或者指定一个固定密钥
    ushort key = static_cast<ushort>(totalLen % 255 + 1);

    for (int i = 0; i < totalLen; i++) { // 遍历整个字符串
        result[i] = QChar(input[i].unicode() ^ key);
    }
    return result;
};
