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
        printf("find %s\n", test->name().c_str());

        Iterator *it = folder1->createIterator();

        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
        ASSERT_TRUE(it->isDone());

        // ASSERT_EQ(8, folder1->numberOfFiles());

        // ASSERT_EQ(6, folder1->numberOfFiles());

        // folder1->remove("/ewffew/fewewfewf/folder1/5-1");

        // ASSERT_EQ(5, folder1->numberOfFiles());

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

TEST(DFSIteratorSuite, TestTARecusive)
{
    // Node *folder1 = new Folder("/Users/user/home");
    // folder1->add(new File("/Users/user/home/Downloads"));
    // folder1->add(new Folder("/Users/user/home/Documents"));

    // Iterator *it = folder1->createIterator();

    // it->first();
    // printf("%s\n", it->currentItem()->name().c_str());
    // it->next();
    // printf("%s\n", it->currentItem()->name().c_str());
    // it->next();
    // printf("%d\n", it->isDone());

    // delete folder1;
    // delete it;
}