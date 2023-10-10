#include "../src/file.h"
#include "../src/folder.h"

TEST(DFSIteratorSuite, TestRecusive)
{
    try
    {
        Node *folder1 = new Folder("/ewffew/fewewfewf/folder1");
        Node *folder2 = new Folder("/ewffew/fewewfewf/folder1/folder3/folder2");
        Node *folder3 = new Folder("/ewffew/fewewfewf/folder1/folder3");
        folder1->switchState(1); // switch to DFS Iterator

        folder2->add(new File("/ewffew/fewewfewf/folder1/folder3/folder2/2-1"));
        folder2->add(new File("/ewffew/fewewfewf/folder1/folder3/folder2/2-2"));

        folder3->add(folder2);
        folder3->add(new File("/ewffew/fewewfewf/folder1/folder3/4-1"));
        folder3->add(new File("/ewffew/fewewfewf/folder1/folder3/4-2"));
        folder3->add(folder2);

        printf("-------------\n");

        folder1->add(new File("/ewffew/fewewfewf/folder1/1-1"));
        folder1->add(new File("/ewffew/fewewfewf/folder1/3-1"));
        folder1->add(new File("/ewffew/fewewfewf/folder1/5-1"));
        folder1->add(new File("/ewffew/fewewfewf/folder1/6-1"));
        folder1->add(folder3);

        // find
        Node *test = folder1->find("/ewffew/fewewfewf/folder1/folder3/4-2");
        ASSERT_EQ("4-2", test->name());
        ASSERT_EQ(10, folder1->numberOfFiles());

        // getChildByName
        ASSERT_EQ("2-2", folder1->getChildByName("2-2")->name());

        // recusive test
        Iterator *it = folder1->createIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
        ASSERT_TRUE(it->isDone());

        // remove Folder
        folder1->remove("/ewffew/fewewfewf/folder1/folder3");
        ASSERT_EQ(4, folder1->numberOfFiles());

        // remove File
        folder1->remove("/ewffew/fewewfewf/folder1/1-1");
        ASSERT_EQ(3, folder1->numberOfFiles());

        delete folder1;
        delete folder2;
        delete folder3;
        delete it;
    }
    catch (const std::runtime_error &e)
    {
        EXPECT_STREQ("wrong path", e.what());
    }
}

TEST(DFSIteratorSuite, TestEmptyFolder)
{
    Node *fff = new Folder("/Users/user/home");
    fff->add(new File("/Users/user/home/Downloads"));
    fff->add(new Folder("/Users/user/home/Documents")); // Empty Folder
    fff->add(new File("/Users/user/home/Downloads123"));
    fff->add(new File("/Users/user/home/Downloads333"));

    // recusive test
    Iterator *it = fff->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        printf("%s\n", it->currentItem()->name().c_str());
    }
    ASSERT_TRUE(it->isDone());

    // find folder
    Node *test = fff->find("/Users/user/home/Documents");
    ASSERT_EQ("Documents", test->name());

    // numberOfFiles
    ASSERT_EQ(3, fff->numberOfFiles());

    // getChildByName => empty folder
    Node *eeee = fff->getChildByName("Documents");
    ASSERT_EQ("Documents", eeee->name());
    
    // remove empty folder
    fff->remove("/Users/user/home/Downloads");
    ASSERT_EQ(2, fff->numberOfFiles());

    delete fff;
    delete it;
}

TEST(DFSIteratorSuite, TestTAIssue)
{
    // This test is to compare the normal iterator, it is meant to switch to DFS iterator

    Node *fff = new Folder("/Users/user/home");
    fff->switchState(1); // switch to DFS iterator

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

    ASSERT_EQ(5, fff->numberOfFiles());

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