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

        // folder3->add(folder2);
        folder3->add(new File("/ewffew/fewewfewf/folder1/folder3/4-1"));
        // folder3->add(folder2);
        folder3->add(new File("/ewffew/fewewfewf/folder1/folder3/4-2"));
        folder3->add(nullptr);

        
        printf("-------------\n");

        folder1->add(new File("/ewffew/fewewfewf/folder1/1-1"));
        folder1->add(nullptr);
        folder1->add(new File("/ewffew/fewewfewf/folder1/3-1"));
        folder1->add(new File("/ewffew/fewewfewf/folder1/5-1"));
        folder1->add(nullptr);
        folder1->add(folder3);
        folder1->add(new File("/ewffew/fewewfewf/folder1/5-1"));
        folder1->add(nullptr);
        folder1->add(nullptr);

        // ASSERT_EQ(6, folder1->numberOfFiles());

        Node * test = folder1->find("/ewffew/fewewfewf/folder1/5-1");
        printf("%s\n", test->name().c_str());


        Iterator *it = folder1->createIterator();

        

        // it->first(); // 1-1
        // cout << it->currentItem()->name() << endl;

        // for (int i = 0; i < 4; i++)
        // {
        //     it->next();
        //     cout << it->currentItem()->name() << endl;
        // }

        // it->next();
        // ASSERT_TRUE(it->isDone());

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