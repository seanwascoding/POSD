#include "../src/file_system_parser.h"

TEST(parser, scanner)
{
    FileSystemScanner *scanner = new FileSystemScanner();
    scanner->setPath("structure");
    scanner->nextNode();
}


TEST(parser, parser)
{
    try
    {
        FileSystemBuilder *builder = new FileSystemBuilder();
        FileSystemScanner *scanner = new FileSystemScanner();
        FileSystemParser *parser = new FileSystemParser(builder, scanner);

        parser->setPath("structure");
        parser->parse();
        Node *getNode = parser->getRoot();

        string temp;
        Iterator *it = getNode->createIterator(OrderBy::Name);
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
}