#include "../src/file.h"
#include "../src/folder.h"

TEST(File, ReadActualFile)
{
    try
    {
        File file("/home/sean/test/posd2023f/makefile");
        Folder folder("/home/sean/test/posd2023f12");
    }
    catch (const string &e)
    {
        std::cerr << e << '\n';
    }
}