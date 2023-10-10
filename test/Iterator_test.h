#include "../src/file.h"
#include "../src/folder.h"
#include <memory>

TEST(FileSuite, TestFolderException)
{
    try
    {
        std::unique_ptr<Node> node(new Folder("/TEST/43434/ffff"));
        node->add(new File("/dfsdfdfs/dsfdsfdfs/dsfdsf"));
    }
    catch (const std::runtime_error &e)
    {
        EXPECT_STREQ("wrong path", e.what());
    }
}

TEST(FileSuite, TestNameAndPathReturnValue)
{
    // file
    Node *file = new File("/home/sean/Desktop/test.txt");
    ASSERT_STREQ("test.txt", file->name().c_str());
    ASSERT_STREQ("/home/sean/Desktop/test.txt", file->path().c_str());

    // folder
    Node *folder = new Folder("/home/sean/Desktop");
    ASSERT_STREQ("Desktop", folder->name().c_str());
    ASSERT_STREQ("/home/sean/Desktop", folder->path().c_str());

    delete file;
    delete folder;
}

TEST(FileSuite, TestFolderIterator)
{
    Node *folder = new Folder("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder");
    folder->switchState(0);

    // add
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test.txt"));

    // Create Iterator
    Iterator *it = folder->createIterator();

    // Search
    it->first();
    ASSERT_EQ("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test.txt", it->currentItem()->path());
    ASSERT_EQ("test.txt", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
    delete folder;
}

TEST(FileSuite, TestFolderRemove)
{
    Node *folder = new Folder("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder");
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test1.py"));
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test2.py"));
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test3.py"));
    string PATH = "/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test2.py";
    Iterator *it = folder->createIterator();
    it->first();
    it->next();
    folder->remove(PATH);
    ASSERT_EQ(2, folder->numberOfFiles());
    ASSERT_EQ("test3.py", it->currentItem()->name());
    delete it;
    delete folder;
}

TEST(FileSuite, TestFoldergetChildByName)
{
    Node *folder = new Folder("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder");

    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test1.py"));
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test2.py"));
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test3.py"));
    char temp[] = "test3.py";

    Node *get_File = folder->getChildByName(temp);

    // ASSERT_EQ(nullptr, get_File);
    ASSERT_EQ("test3.py", get_File->name());
    // ASSERT_EQ("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder", get_File->path());

    delete folder;
}

TEST(FileSuite, TestFolderfind)
{
    Node *folder = new Folder("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder");

    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test1.py"));
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test2.py"));
    folder->add(new File("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test3.py"));
    string temp = "/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test2.py";

    // ASSERT_EQ("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder", folder->path());

    Node *getFile = folder->find(temp);

    // ASSERT_EQ(nullptr, getFile);
    ASSERT_EQ("test2.py", getFile->name());
    ASSERT_EQ("/home/nvidia/Desktop/POSD/HW2/posd2023f_ta-master/template/test_folder/test2.py", getFile->path());
    ASSERT_EQ(3, folder->numberOfFiles());

    delete folder;
}

TEST(FileSuite, TestTAIssue)
{
    // The below Issue is the error about the TA test => resolve

    Node *fff = new Folder("/Users/user/home");
    fff->switchState(0); // switch to normal Iterator

    Node *documents = new Folder("/Users/user/home/documents");
    Node *profile = new Folder("/Users/user/home/profile");
    Node *download = new Folder("/Users/user/home/download");

    Node *fav = new Folder("/Users/user/home/documents/fav");

    fff->add(profile);
    fff->add(documents);

    documents->add(fav);

    fav->add(new File("/Users/user/home/documents/fav/1"));
    fav->add(new File("/Users/user/home/documents/fav/2"));
    fav->add(new File("/Users/user/home/documents/fav/3"));

    documents->add(new File("/Users/user/home/documents/note"));

    fff->add(download);

    download->add(new File("/Users/user/home/download/funny"));

    ASSERT_EQ(0, fff->numberOfFiles()); // all of the node is folder type in the normal iterator

    Iterator *it = fff->createIterator();

    for (it->first(); !it->isDone(); it->next())
    {
        cout << it->currentItem()->name() << endl;
    }

    ASSERT_TRUE(it->isDone());

    delete fff;
    delete documents;
    delete profile;
    delete download;
    delete fav;
}