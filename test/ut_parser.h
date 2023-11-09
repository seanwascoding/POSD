#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/order_by.h"

TEST(parser, normal)
{
    try
    {
        Folder folder("structure");
        folder.add(new Folder("structure/home"));
        folder.add(new Folder("structure/visitor"));
        folder.add(new File("structure/file.txt"));

        Iterator *it = folder.createIterator(OrderBy::Normal);

        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }

        delete it;
    }
    catch (const char &e)
    {
        std::cerr << e << '\n';
    }
}

TEST(parser, OrderByNameIterator)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder folder1("structure/home");
        folder1.add(new File("structure/home/my_profile"));
        folder1.add(new File("structure/home/hello.txt"));
        folder.add(new Folder("structure/visitor"));
        folder.add(new File("structure/file.txt"));
        folder.add(&folder1);

        it = folder.createIterator(OrderBy::Name);
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}

TEST(parser, OrderByNameWithFolderFirstIterator)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder folder1("structure/home");
        folder1.add(new File("structure/home/my_profile"));
        folder1.add(new File("structure/home/hello.txt"));
        folder.add(new File("structure/file.txt"));
        folder.add(new Folder("structure/visitor"));
        folder.add(&folder1);

        it = folder.createIterator(OrderBy::NameWithFolderFirst);
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}

TEST(parser, OrderByKindIterator)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder folder1("structure/home");
        folder1.add(new File("structure/home/my_profile"));
        folder1.add(new File("structure/home/hello.txt"));
        folder.add(new File("structure/file.txt"));
        folder.add(new Folder("structure/visitor"));
        folder.add(&folder1);

        it = folder.createIterator(OrderBy::Kind);
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}