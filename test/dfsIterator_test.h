// #include "../src/file.h"
// #include "../src/folder.h"

// TEST(DFSIteratorSuite, TestRecusive)
// {
//     Folder *folder1 = new Folder("/ewffew/fewewfewf/folder1");
//     Folder *folder2 = new Folder("/ewffew/fewewfewf/folder2");
//     Folder *folder3 = new Folder("/ewffew/fewewfewf/folder3");

//     folder2->add(new File("/reersesr/2-1"));
//     folder2->add(new File("/reersesr/2-2"));
//     folder2->add(new File("/reersesr/2-3"));

//     folder3->add(folder2);
//     folder3->add(new File("/reersesr/4-1"));
//     folder3->add(folder2);
//     folder3->add(new File("/reersesr/4-2"));
//     folder3->add(folder2);


//     folder1->add(new File("/eefsesffe/fesefsefefs/1-1"));
//     folder1->add(folder2);
//     folder1->add(new File("/eefsesffe/fesefsefefs/3-1"));
//     folder1->add(folder3);
//     folder1->add(new File("/eefsesffe/fesefsefefs/5-1"));

//     Iterator *it = folder1->createIterator();

//     it->first(); // 1-1
//     cout << it->currentItem()->name() << endl;

//     for (int i = 0; i < 21; i++)
//     {
//         it->next();
//         cout << it->currentItem()->name() << endl;
//     }

//     it->next();
//     ASSERT_TRUE(it->isDone());

//     delete folder1;
//     delete folder2;
//     delete folder3;
//     delete it;
// }

// TEST(DFSIteratorSuite, Test)
// {

//     ASSERT_TRUE(true);
// }