#include "../src/file.h"
#include "../src/folder.h"

TEST(DFSIteratorSuite, TestRecusive)
{
    try
    {
        Node *folder1 = new Folder("/ewffew/fewewfewf/folder1");
        Node *folder2 = new Folder("/ewffew/fewewfewf/folder1/folder3/folder2");
        Node *folder3 = new Folder("/ewffew/fewewfewf/folder1/folder3");
        folder1->switchState(1);
        folder2->switchState(1);
        folder3->switchState(1);

        folder2->add(new File("/ewffew/fewewfewf/folder1/folder3/folder2/2-1"));
        folder2->add(new File("/ewffew/fewewfewf/folder1/folder3/folder2/2-2"));

        folder3->add(folder2);
        folder3->add(new File("/ewffew/fewewfewf/folder1/folder3/4-1"));
        // folder3->add(folder2);
        folder3->add(new File("/ewffew/fewewfewf/folder1/folder3/4-2"));
        // folder3->add(nullptr);

        printf("-------------\n");

        folder1->add(new File("/ewffew/fewewfewf/folder1/1-1"));
        folder1->add(new File("/ewffew/fewewfewf/folder1/3-1"));
        folder1->add(new File("/ewffew/fewewfewf/folder1/5-1"));
        folder1->add(folder3);
        folder1->add(new File("/ewffew/fewewfewf/folder1/5-1"));

        Node *test = folder1->find("/ewffew/fewewfewf/folder1/3-1");
        ASSERT_EQ("3-1", test->name());
        ASSERT_EQ(8, folder1->numberOfFiles());

        Iterator *it = folder1->createIterator();

        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
        ASSERT_TRUE(it->isDone());

        // ASSERT_EQ(6, folder1->numberOfFiles());

        // folder1->remove("/ewffew/fewewfewf/folder1/5-1");

        // ASSERT_EQ(5, folder1->numberOfFiles());

        delete folder1;
        delete folder2;
        delete folder3;
        // delete it;
    }
    catch (const std::runtime_error &e)
    {
        EXPECT_STREQ("wrong path", e.what());
    }
}

TEST(DFSIteratorSuite, TestTARecusive)
{
    Node *fff = new Folder("/Users/user/home");
    fff->add(new File("/Users/user/home/Downloads"));
    fff->add(new Folder("/Users/user/home/Documents"));
    fff->add(new File("/Users/user/home/Downloads123"));
    fff->add(new File("/Users/user/home/Downloads333"));


    Iterator *it = fff->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        printf("%s\n", it->currentItem()->name().c_str());
    }
    ASSERT_TRUE(it->isDone());
    Node *test = fff->find("/Users/user/home/Documents");
    ASSERT_EQ("Documents", test->name());
    ASSERT_EQ(3, fff->numberOfFiles());
    Node *eeee = fff->getChildByName("Documents");
    ASSERT_EQ("Documents", eeee->name());
    // fff->remove("/Users/user/home/Downloads");
    // ASSERT_EQ(2, fff->numberOfFiles());

    delete fff;
    delete it;
}