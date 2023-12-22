#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal)
{
    Folder home("structure/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("structure/home", home.path());
}

TEST(Folder, invalid_folder)
{
    ASSERT_ANY_THROW(Folder("/NOT/EXIST/PATH"));
}

TEST(Folder, invalid_folder_2)
{
    ASSERT_ANY_THROW(Folder("structure/home/Documents/hello.txt"));
}

TEST(Folder, add_file)
{
    Folder *home = new Folder("structure/home");
    File *hello = new File("structure/home/hello.txt");
    home->add(hello);

    ASSERT_EQ("hello.txt", home->getChildByName("hello.txt")->name());

    delete home;
}

TEST(Folder, add_incorrect_path_file_to_folder)
{
    Folder *home = new Folder("structure/home");
    File *hello = new File("structure/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home->add(hello));

    delete home;
}

TEST(Folder, add_folder)
{
    Folder *home = new Folder("structure/home");
    Folder *document = new Folder("structure/home/Documents");

    home->add(document);

    ASSERT_EQ("Documents", home->getChildByName("Documents")->name());

    delete home;
}

TEST(Folder, rename_folder_file)
{
    Node *home;
    Node *profile;
    Node *download;
    Node *document;
    Node *note;
    Node *favorite;
    Node *ddd;
    Node *ca;
    Node *cqrs;
    Node *funny;

    home = new Folder("structure/home");

    profile = new File("structure/home/my_profile");
    home->add(profile);

    document = new Folder("structure/home/Documents");
    home->add(document);

    favorite = new Folder("structure/home/Documents/favorites");
    document->add(favorite);
    ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
    favorite->add(ddd);
    ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
    favorite->add(ca);
    cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
    favorite->add(cqrs);

    note = new File("structure/home/Documents/note.txt");
    document->add(note);

    download = new Folder("structure/home/Downloads");
    home->add(download);

    funny = new File("structure/home/Downloads/funny.png");
    download->add(funny);

    //? test
    document->rename("test");
    ASSERT_EQ("structure/home/test/favorites", favorite->path());

    ddd->rename("test.jpg");
    ASSERT_EQ("structure/home/test/favorites/test.jpg", ddd->path());

    delete home;
    home = nullptr;
    profile = nullptr;
    download = nullptr;
    document = nullptr;
    note = nullptr;
    favorite = nullptr;
    ddd = nullptr;
    ca = nullptr;
    cqrs = nullptr;
    funny = nullptr;
}