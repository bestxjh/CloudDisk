all:bin/test

bin/DictProducer.o:src/DictProducer.cpp
	gcc -c -g src/DictProducer.cpp -o bin/DictProducer.o

bin/SplitTool.o:src/SplitTool.cpp
	gcc -c -g src/SplitTool.cpp -o bin/SplitTool.o

bin/SplitToolCppJieba.o:src/SplitToolCppJieba.cpp
	gcc -c -g src/SplitToolCppJieba.cpp -o bin/SplitToolCppJieba.o

bin/test.o:src/mian.cpp 
	gcc -c -g src/mian.cpp -o bin/test.o

bin/test:bin/DictProducer.o bin/SplitTool.o bin/SplitToolCppJieba.o bin/test.o
	g++ bin/DictProducer.o bin/SplitTool.o bin/SplitToolCppJieba.o bin/test.o -o bin/test

clean:
	rm -f bin/*.o bin/test
