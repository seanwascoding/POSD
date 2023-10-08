all: dirs bin/ut_all

bin/ut_all: test/ut_all.cpp test/Iterator_test.h test/dfsIterator_test.h test/bfsIterator_test.h src/node.h src/folder.h src/file.h src/null_iterator.h iterator.o dfs_iterator.o
	g++ -std=c++11 test/ut_all.cpp obj/iterator.o obj/dfs_iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.cpp src/iterator.h
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

dfs_iterator.o: src/dfs_iterator.cpp src/dfs_iterator.h
	g++ -std=c++11 -c src/dfs_iterator.cpp -o obj/dfs_iterator.o

dirs:
	mkdir -p bin obj

clean:
	rm -rf bin obj

.PHONY: clean