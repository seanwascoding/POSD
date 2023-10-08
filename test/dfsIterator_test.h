#include "../src/file.h"
#include "../src/folder.h"

TEST(DFSIteratorSuite, TestRecusive)
{
    Folder *folder1 = new Folder("/ewffew/fewewfewf/folder1");
    Folder *folder2 = new Folder("/ewffew/fewewfewf/folder2");
    Folder *folder3 = new Folder("/ewffew/fewewfewf/folder3");
    folder1->switchState(1);
    folder2->switchState(1);
    folder3->switchState(1);

    folder2->add(new File("/ewffew/fewewfewf/folder2/2-1"));
    folder2->add(new File("/ewffew/fewewfewf/folder2/2-2"));
    folder2->add(new File("/reersesr/2-3"));

    folder3->add(folder2);
    folder3->add(new File("/ewffew/fewewfewf/folder3/4-1"));
    folder3->add(folder2);
    folder3->add(new File("/ewffew/fewewfewf/folder3/4-2"));
    folder3->add(folder2);

    folder1->add(new File("/ewffew/fewewfewf/folder1/1-1"));
    folder1->add(folder2);
    folder1->add(new File("/ewffew/fewewfewf/folder1/3-1"));
    folder1->add(folder3);
    folder1->add(new File("/ewffew/fewewfewf/folder1/5-1"));

    Iterator *it = folder1->createIterator();

    it->first(); // 1-1
    cout << it->currentItem()->name() << endl;
    // cout << it->isDone() << endl;

    for (int i = 0; i < 2; i++)
    {
        it->next();
        cout << it->currentItem()->name() << endl;
    }

    it->next();
    ASSERT_TRUE(it->isDone());

    delete folder1;
    delete folder2;
    delete folder3;
    delete it;
}