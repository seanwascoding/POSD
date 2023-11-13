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

        TreeVisitor *v = new TreeVisitor(OrderBy::Normal);
        folder.accept(v);
        // cout << v->getTree();

        ASSERT_EQ(".\n"
                  "├── home\n"
                  "│   ├── hello.txt\n"
                  "│   ├── my_profile\n"
                  "│   ├── Documents\n"
                  "│   │   └── favorites\n"
                  "│   │       ├── clean-architecture.pdf\n"
                  "│   │       ├── cqrs.pdf\n"
                  "│   │       └── domain-driven-design.pdf\n"
                  "│   └── Downloads\n"
                  "│       └── funny.png\n"
                  "├── visitor\n"
                  "│   ├── file1.txt\n"
                  "│   └── file2.txt\n"
                  "└── file.txt\n",
                  v->getTree());
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

        TreeVisitor *v = new TreeVisitor(OrderBy::Name);
        folder.accept(v);
        // cout << v->getTree();

        ASSERT_EQ(".\n"
                  "├── file.txt\n"
                  "├── home\n"
                  "│   ├── Documents\n"
                  "│   │   └── favorites\n"
                  "│   │       ├── clean-architecture.pdf\n"
                  "│   │       ├── cqrs.pdf\n"
                  "│   │       └── domain-driven-design.pdf\n"
                  "│   ├── Downloads\n"
                  "│   │   └── funny.png\n"
                  "│   ├── hello.txt\n"
                  "│   └── my_profile\n"
                  "└── visitor\n"
                  "    ├── file1.txt\n"
                  "    └── file2.txt\n",
                  v->getTree());
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

        TreeVisitor *v = new TreeVisitor(OrderBy::NameWithFolderFirst);
        folder.accept(v);
        // cout << v->getTree();

        ASSERT_EQ(".\n"
                  "├── home\n"
                  "│   ├── Documents\n"
                  "│   │   └── favorites\n"
                  "│   │       ├── clean-architecture.pdf\n"
                  "│   │       ├── cqrs.pdf\n"
                  "│   │       └── domain-driven-design.pdf\n"
                  "│   ├── Downloads\n"
                  "│   │   └── funny.png\n"
                  "│   ├── hello.txt\n"
                  "│   └── my_profile\n"
                  "├── visitor\n"
                  "│   ├── file1.txt\n"
                  "│   └── file2.txt\n"
                  "└── file.txt\n",
                  v->getTree());
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
        visitor.add(&nested);

        folder.add(&visitor);
        folder.add(new File("structure/file.txt"));
        folder.add(&home);

        TreeVisitor *v = new TreeVisitor(OrderBy::Kind);
        folder.accept(v);
        // cout << v->getTree();

        ASSERT_EQ(".\n"
                  "├── home\n"
                  "│   ├── my_profile\n"
                  "│   ├── Documents\n"
                  "│   │   └── favorites\n"
                  "│   │       ├── clean-architecture.pdf\n"
                  "│   │       ├── cqrs.pdf\n"
                  "│   │       └── domain-driven-design.pdf\n"
                  "│   ├── Downloads\n"
                  "│   │   └── funny.png\n"
                  "│   └── hello.txt\n"
                  "├── visitor\n"
                  "│   ├── nested\n"
                  "│   │   ├── file3.txt\n"
                  "│   │   └── file4.txt\n"
                  "│   ├── file1.txt\n"
                  "│   └── file2.txt\n"
                  "└── file.txt\n",
                  v->getTree());
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    delete it;
}