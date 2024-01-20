
#include "my_utils/Logger.hpp"
#include "my_utils/Profiler.hpp"
#include <cstddef>
#include <cstdlib>
#include <string>

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

int main(int argc, const char** argv)
{
    long x = 0;
    size_t iter = 10000000;
    logger.setLevel(Level::DEB);
    logger.setTarget(Target::STDOUT);

    if (argc == 2) {
        iter = atoi(argv[1]);
    }
    logger.logInfo(std::to_string(iter));

    {
        newTimer("no fn");
        for (size_t i = 0; i < iter; i++) {
            x += 1;
        }
    }
    x = 0;
    {
        newTimer("fn with value");
        for (size_t i = 0; i < iter; i++) {
            x = foo(x);
        }
    }
    x = 0;
    {
        newTimer("fn with ref");
        for (size_t i = 0; i < iter; i++) {
            fooRef(x);
        }
    }

    x = 0;
    {
        newTimer("empty fn call");
        for (size_t i = 0; i < iter; i++) {
            fuu();
        }
    }
    x = 0;
    {
        newTimer("empty loop");
        for (size_t i = 0; i < iter; i++) {
        }
    }
    logger.logInfo(Profiler::getInstance()->getTimingsAsString(true).c_str());
}