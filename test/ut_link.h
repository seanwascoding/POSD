#include "../src/link.h"

TEST(LinkSuite, test)
{
    Folder *home = new Folder("structure/home");
    Link *lHome = new Link("structure/link_to_home", home);


    delete home;
    delete lHome;
}