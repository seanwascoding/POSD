#include "../src/file.h"
#include "../src/folder.h"
#include "../src/find_by_name_visitor.h"

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

TEST(Vistor, FindByNameInFile)
{
    FindByNameVisitor vistor("makefile");

    File file("/home/sean/test/posd2023f/makefile");

    file.accept(&vistor);

    ASSERT_EQ(1, vistor.getPaths().size());
}

TEST(Vistor, FindByNameInFolder)
{
    FindByNameVisitor vistor("makefile");

    Folder folder("/home/sean/test/posd2023f");
    folder.add(new File("/home/sean/test/posd2023f/README.md"));
    folder.add(new File("/home/sean/test/posd2023f/bin"));
    folder.add(new File("/home/sean/test/posd2023f/test"));
    folder.add(new File("/home/sean/test/posd2023f/makefile"));

    folder.accept(&vistor);

    ASSERT_EQ(1, vistor.getPaths().size());
}