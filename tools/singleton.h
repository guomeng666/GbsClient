#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }
private:
    Singleton(){}
    ~Singleton(){}
};

#endif // SINGLETON_H
