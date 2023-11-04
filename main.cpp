
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cstddef>
#include <cstdlib>

long foo(long x)
{
    return x + 1;
}
void fooRef(long& x)
{
    x += 1;
}
void fuu()
{
}

long x = 0;
long k = 0;
long y = 0;
long z = 0;
const size_t iter = 1000000000;
int main(int argc, const char** argv)
{
    logger.setLevel(Level::DEB);
    logger.setTarget(Target::STDOUT);
    {
        newTimer("emptyFor");
        for (size_t i = 0; i < iter; i++) {
        }
    }

    {
        newTimer("function");
        for (size_t i = 0; i < iter; i++) {
            x = foo(x);
        }
    }
    {
        newTimer("functionRef");
        for (size_t i = 0; i < iter; i++) {
            fooRef(k);
        }
    }
    {
        newTimer("emptyFn");
        for (size_t i = 0; i < iter; i++) {
            fuu();
        }
    }

    {
        newTimer("raw");
        for (size_t i = 0; i < iter; i++) {
            y += 1;
        }
    }
    logger.logInfo(Profiler::getInstance()->getTimingsAsString(true).c_str());
    system("PAUSE");
}