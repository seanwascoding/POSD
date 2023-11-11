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

        TreeVisitor *visit = new TreeVisitor(OrderBy::NameWithFolderFirst);

        getNode->accept(visit);
        string output = visit->getTree();
        cout << output;
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
}