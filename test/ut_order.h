#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/order_by.h"
#include "../src/tree_visitor.h"

TEST(order, normal)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder home("structure/home");
        Folder visitor("structure/visitor");

        Folder Documents("structure/home/Documents");
        Folder favorites("structure/home/Documents/favorites");
        favorites.add(new File("structure/home/Documents/favorites/clean-architecture.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/cqrs.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/domain-driven-design.pdf"));
        Documents.add(&favorites);

        Folder Downloads("structure/home/Downloads");
        Downloads.add(new File("structure/home/Downloads/funny.png"));

        home.add(new File("structure/home/hello.txt"));
        home.add(new File("structure/home/my_profile"));
        home.add(&Documents);
        home.add(&Downloads);

        visitor.add(new File("structure/visitor/file1.txt"));
        visitor.add(new File("structure/visitor/file2.txt"));
        Folder nested("structure/visitor/nested");
        nested.add(new File("structure/visitor/nested/file3.txt"));
        nested.add(new File("structure/visitor/nested/file4.txt"));

        folder.add(&home);
        folder.add(&visitor);
        folder.add(new File("structure/file.txt"));

        string temp;
        it = folder.createIterator(OrderBy::Normal);
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
            temp += it->currentItem()->name();
            temp += "\n";
        }

        ASSERT_TRUE(it->isDone());
        ASSERT_EQ("home\nvisitor\nfile.txt\n", temp);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}

TEST(order, OrderByNameIterator)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder home("structure/home");
        Folder visitor("structure/visitor");

        Folder Documents("structure/home/Documents");
        Folder favorites("structure/home/Documents/favorites");
        favorites.add(new File("structure/home/Documents/favorites/clean-architecture.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/cqrs.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/domain-driven-design.pdf"));
        Documents.add(&favorites);

        Folder Downloads("structure/home/Downloads");
        Downloads.add(new File("structure/home/Downloads/funny.png"));

        home.add(new File("structure/home/hello.txt"));
        home.add(new File("structure/home/my_profile"));
        home.add(&Documents);
        home.add(&Downloads);

        visitor.add(new File("structure/visitor/file1.txt"));
        visitor.add(new File("structure/visitor/file2.txt"));
        Folder nested("structure/visitor/nested");
        nested.add(new File("structure/visitor/nested/file3.txt"));
        nested.add(new File("structure/visitor/nested/file4.txt"));

        folder.add(&home);
        folder.add(&visitor);
        folder.add(new File("structure/file.txt"));

        string temp;
        it = folder.createIterator(OrderBy::Name);
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
            temp += it->currentItem()->name();
            temp += "\n";
        }
        ASSERT_TRUE(it->isDone());
        ASSERT_EQ("file.txt\nhome\nvisitor\n", temp);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}

TEST(order, OrderByNameWithFolderFirstIterator)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder home("structure/home");
        Folder visitor("structure/visitor");

        Folder Documents("structure/home/Documents");
        Folder favorites("structure/home/Documents/favorites");
        favorites.add(new File("structure/home/Documents/favorites/clean-architecture.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/cqrs.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/domain-driven-design.pdf"));
        Documents.add(&favorites);

        Folder Downloads("structure/home/Downloads");
        Downloads.add(new File("structure/home/Downloads/funny.png"));

        home.add(new File("structure/home/hello.txt"));
        home.add(new File("structure/home/my_profile"));
        home.add(&Documents);
        home.add(&Downloads);

        visitor.add(new File("structure/visitor/file1.txt"));
        visitor.add(new File("structure/visitor/file2.txt"));
        Folder nested("structure/visitor/nested");
        nested.add(new File("structure/visitor/nested/file3.txt"));
        nested.add(new File("structure/visitor/nested/file4.txt"));

        folder.add(&home);
        folder.add(&visitor);
        folder.add(new File("structure/file.txt"));

        string temp;
        it = folder.createIterator(OrderBy::NameWithFolderFirst);
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
            temp += it->currentItem()->name();
            temp += "\n";
        }
        ASSERT_TRUE(it->isDone());
        ASSERT_EQ("home\nvisitor\nfile.txt\n", temp);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}

TEST(order, OrderByKindIterator)
{
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder home("structure/home");
        Folder visitor("structure/visitor");

        Folder Documents("structure/home/Documents");
        Folder favorites("structure/home/Documents/favorites");
        favorites.add(new File("structure/home/Documents/favorites/clean-architecture.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/cqrs.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/domain-driven-design.pdf"));
        Documents.add(&favorites);

        Folder Downloads("structure/home/Downloads");
        Downloads.add(new File("structure/home/Downloads/funny.png"));

        home.add(new File("structure/home/hello.txt"));
        home.add(new File("structure/home/my_profile"));
        home.add(&Documents);
        home.add(&Downloads);

        visitor.add(new File("structure/visitor/file1.txt"));
        visitor.add(new File("structure/visitor/file2.txt"));
        Folder nested("structure/visitor/nested");
        nested.add(new File("structure/visitor/nested/file3.txt"));
        nested.add(new File("structure/visitor/nested/file4.txt"));

        folder.add(&home);
        folder.add(&visitor);
        folder.add(new File("structure/file.txt"));

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

TEST(order, visitor)
{
    TreeVisitor *visit = nullptr;
    Iterator *it = nullptr;
    try
    {
        Folder folder("structure");
        Folder home("structure/home");
        Folder visitor("structure/visitor");

        Folder Documents("structure/home/Documents");
        Folder favorites("structure/home/Documents/favorites");
        favorites.add(new File("structure/home/Documents/favorites/clean-architecture.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/cqrs.pdf"));
        favorites.add(new File("structure/home/Documents/favorites/domain-driven-design.pdf"));
        Documents.add(&favorites);

        Folder Downloads("structure/home/Downloads");
        Downloads.add(new File("structure/home/Downloads/funny.png"));

        home.add(new File("structure/home/hello.txt"));
        home.add(new File("structure/home/my_profile"));
        home.add(&Documents);
        home.add(&Downloads);

        visitor.add(new File("structure/visitor/file1.txt"));
        visitor.add(new File("structure/visitor/file2.txt"));
        Folder nested("structure/visitor/nested");
        nested.add(new File("structure/visitor/nested/file3.txt"));
        nested.add(new File("structure/visitor/nested/file4.txt"));
        visitor.add(&nested);

        folder.add(&home);
        folder.add(&visitor);
        folder.add(new File("structure/file.txt"));

        visit = new TreeVisitor(OrderBy::Name);

        folder.accept(visit);

        string output = visit->getTree();

        cout << output;

        ASSERT_EQ(".\n\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 file.txt\n\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 home\n\xE2\x94\x82   \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 Documents\n\xE2\x94\x82   \xE2\x94\x82   \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 favorites\n\xE2\x94\x82   \xE2\x94\x82       \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 clean-architecture.pdf\n\xE2\x94\x82   \xE2\x94\x82       \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 cqrs.pdf\n\xE2\x94\x82   \xE2\x94\x82       \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 domain-driven-design.pdf\n\xE2\x94\x82   \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 Downloads\n\xE2\x94\x82   \xE2\x94\x82   \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 funny.png\n\xE2\x94\x82   \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 hello.txt\n\xE2\x94\x82   \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 my_profile\n\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 visitor\n    \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 file1.txt\n    \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 file2.txt\n    \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 nested\n        \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 file3.txt\n        \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 file4.txt\n", output);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}