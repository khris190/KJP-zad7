
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cstdlib>

long __attribute__((noinline)) foo(long x)
{
    return x + 1;
}
void __attribute__((noinline)) fooRef(long& x)
{
    x += 1;
}
void __attribute__((noinline)) fuu()
{
}

long x = 0;
long k = 0;
long y = 0;
long z = 0;
int main(int argc, const char** argv)
{
    logger.setLevel(Level::DEB);
    logger.setTarget(Target::STDOUT);
    {
        newTimer("emptyFor");
        for (size_t i = 0; i < 100000000; i++) {
        }
    }

    {
        newTimer("function");
        for (size_t i = 0; i < 100000000; i++) {
            x = foo(x);
        }
    }
    {
        newTimer("functionRef");
        for (size_t i = 0; i < 100000000; i++) {
            fooRef(k);
        }
    }
    {
        newTimer("emptyFn");
        for (size_t i = 0; i < 100000000; i++) {
            fuu();
        }
    }

    {
        newTimer("raw");
        for (size_t i = 0; i < 100000000; i++) {
            y += 1;
        }
    }
    logger.logInfo(Profiler::getInstance()->getTimingsAsString(true).c_str());
    system("PAUSE");
}