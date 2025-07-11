#include "Menu.h"
int main()
{
    Menu* m;
    m = new Menu;
    m->display_menu();
    delete m;
    m = nullptr;
    return 0;
}
