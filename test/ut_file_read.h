#include "../src/file.h"
#include "../src/folder.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"

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
    try
    {
        FindByNameVisitor vistor("makefile");

        File file("/home/sean/test/posd2023f/makefile");

        file.accept(&vistor);

        ASSERT_EQ(1, vistor.getPaths().size());
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
    }
}

TEST(Vistor, FindByNameInFolder)
{
    try
    {
        FindByNameVisitor vistor("makefile");

        Folder folder("/home/sean/test/posd2023f");
        folder.add(new File("/home/sean/test/posd2023f/README.md"));
        folder.add(new Folder("/home/sean/test/posd2023f/bin"));
        folder.add(new Folder("/home/sean/test/posd2023f/test"));
        folder.add(new File("/home/sean/test/posd2023f/makefile"));

        folder.accept(&vistor);

        ASSERT_EQ(1, vistor.getPaths().size());
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
    }
}

TEST(Vistor, IteratorTest)
{
    try
    {
        Folder folder("/home/sean/test/posd2023f");
        folder.add(new File("/home/sean/test/posd2023f/README.md"));
        folder.add(new Folder("/home/sean/test/posd2023f/test"));
        folder.add(new File("/home/sean/test/posd2023f/makefile"));

        Iterator *it = folder.createIterator();
        int i = 0;
        for (it->first(); !it->isDone(); it->next())
        {
            printf("%s\n", it->currentItem()->name().c_str());
            i++;
            if (i == 2)
            {
                folder.add(new File("/home/sean/test/posd2023f/eeeee.f"));
            }
        }
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
    }
}

TEST(Vistor, StreamOutVistorFile)
{
    StreamOutVisitor stream;

    File file("/home/sean/test/posd2023f/makefile");

    file.accept(&stream);

    printf("%s\n", stream.getResult().c_str());
}

TEST(Vistor, StreamOutVistorFolder)
{
    StreamOutVisitor stream;

    Folder folder("/home/sean/test/posd2023f");
    folder.add(new File("/home/sean/test/posd2023f/makefile"));
    folder.add(new File("/home/sean/test/posd2023f/README.md"));
    folder.add(new Folder("/home/sean/test/posd2023f/test"));

    folder.accept(&stream);

    printf("%s\n", stream.getResult().c_str());
}