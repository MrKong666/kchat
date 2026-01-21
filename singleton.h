#ifndef SINGLETON_H
#define SINGLETON_H
#include"global.h"
/**
 * @file singleton.h
 * @brief 单例类的基类
 *
 * @date  2026/01/21
 * @author 孔祥锐
 */

template<typename T>
class Singleton{
protected:
    Singleton()=default;
    Singleton(const Singleton<T>&)=delete;
    Singleton& operator=(const Singleton<T>&st)=delete;
    static std::shared_ptr<T>_instance;
public:
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag,[&](){
            _instance=std::shared_ptr<T>(new T);
        });
        /*
        为什么不用makeshared？
        因为这里的构造函数是protected的,make_shared无法访问受保护的构造函数,而new可以在类的内部直接调用
        */
        return _instance;
    }
    void PrintAddress(){
        std::cout<<_instance.get()<<"\n";
    }
    ~Singleton(){
        std::cout<<"this is singleton destruct\n";
    }
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_instance=nullptr;
/*在 C++ 中，类内部的 static 变量只是声明。对于模板类，你必须在头文件（或实现文件）中提供其定义。注意这里的语法格式：必须带上 template<typename T> 前缀。
*/
#endif // SINGLETON_H
/*std::once_flag
本质：它是一个特殊的标记位（内部通常是一个互斥锁和一个状态位的组合）。

规则：它不可拷贝，也不可移动。

角色：它就像一个“门卫”，记录了关联的任务是否已经完成。

std::call_once
语法：std::call_once(flag, func, args...)

逻辑：

如果 flag 对应的任务没执行过，当前线程就执行 func。

如果此时其他线程也调用了 call_once，它们会阻塞（等待），直到正在执行 func 的那个线程完成。

一旦执行成功，flag 被标记为“已完成”，后续所有调用都会直接返回，不再执行。*/
