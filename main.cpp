#include "myapp.h"

int main(int argc, char *argv[])
{
    MyApp a(argc, argv);

    a.setApplicationVersion(VERSION_STRING); //see BraggCalculator.pro file
    return a.exec();
}
