#include "../src/file_system_parser.h"
#include "../src/tree_visitor.h"
#include <iostream>
#include <unistd.h>

TEST(parser, scanner)
{
    FileSystemScanner *scanner = new FileSystemScanner();
    scanner->setPath("structure");

    scanner->nextNode();
    for (; !scanner->isDone(); scanner->nextNode())
    {
        cout << scanner->currentNodeName() << endl;
    }
    ASSERT_TRUE(scanner->isDone());
}

TEST(parser, parser)
{
    try
    {
        FileSystemBuilder *builder = new FileSystemBuilder();
        FileSystemParser *parser = new FileSystemParser(builder);

        parser->setPath("structure");
        parser->parse();
        Node *getNode = parser->getRoot();

        TreeVisitor *visit = new TreeVisitor(OrderBy::Kind);

        getNode->accept(visit);
        string output = visit->getTree();
        // cout << output;

        ASSERT_EQ(".\n"
                  "├── home\n"
                  "│   ├── my_profile\n"
                  "│   ├── Documents\n"
                  "│   │   ├── favorites\n"
                  "│   │   │   ├── clean-architecture.pdf\n"
                  "│   │   │   ├── cqrs.pdf\n"
                  "│   │   │   └── domain-driven-design.pdf\n"
                  "│   │   ├── hello.txt\n"
                  "│   │   └── note.txt\n"
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
                  visit->getTree());
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
}