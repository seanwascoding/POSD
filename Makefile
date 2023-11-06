.PHONY: clean dirs

CFLAGS = -std=c++11 -Wfatal-errors -Wall
LIBS = -lgtest -lpthread

UT_ALL = test/ut_all.cpp
TEST_HEADERS = test/ut_expression.h
SRC_HEADERS = src/term.h src/operand.h src/expression.h src/builder.h src/visitor.h src/scanner.h src/parser.h src/postvisitor.h src/strvisitor.h

all: dirs bin/ut_all

bin/ut_all: $(UT_ALL) $(TEST_HEADERS) $(SRC_HEADERS)
	g++ $(CFLAGS) -o $@ $<  $(LIBS) 

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
