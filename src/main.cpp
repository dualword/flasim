#include "FlaSimApp.hpp"
#include "Globals.hpp"

int main()
{
    FlaSimApp *a = new FlaSimApp();
    a->execute();

    delete a;
    Globals::shutdown();
    return 0;
}
