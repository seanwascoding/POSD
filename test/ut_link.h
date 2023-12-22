#include "../src/link.h"

TEST(LinkSuite, LinkToFile)
{
    File *hello = new File("structure/home/hello.txt");
    Link *lHello = new Link("structure/link_to_hello", hello);

    ASSERT_EQ(1, lHello->numberOfFiles());

    delete hello;
    delete lHello;
}

TEST(LinkSuite, LinkToFolder)
{
    File *hello = new File("structure/home/Documents/hello.txt");
    File *note = new File("structure/home/Documents/note.txt");
    Folder *Documents = new Folder("structure/home/Documents");
    Documents->add(hello);
    Documents->add(note);
    Link *lDocuments = new Link("structure/link_to_Documents", Documents);

    ASSERT_EQ(2, lDocuments->numberOfFiles());

    delete Documents;
    delete lDocuments;
}