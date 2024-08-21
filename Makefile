#all:bin/main bin/test bin/client

#bin/DictProducer.o:src/DictProducer.cpp
#	g++ -c -g -I include src/DictProducer.cpp -o bin/DictProducer.o

#bin/SplitTool.o:src/SplitTool.cpp
#	g++ -c -g -I include src/SplitTool.cpp -o bin/SplitTool.o 

#bin/SplitToolCppJieba.o:src/SplitToolCppJieba.cpp
#	g++ -c -g -I include src/SplitToolCppJieba.cpp -o bin/SplitToolCppJieba.o 

#bin/main.o:src/mian.cpp 
#	g++ -c -g -I include src/mian.cpp -o bin/main.o

#bin/test:bin/DictProducer.o bin/SplitTool.o bin/SplitToolCppJieba.o bin/test.o 
#	g++ bin/DictProducer.o bin/SplitTool.o bin/SplitToolCppJieba.o bin/test.o -o bin/test 

#all:bin/test

all:bin/test bin/client

#bin/Configuration.o: src/Configuration.cc
#	g++ -g -c src/Configuration.cc -o bin/Configuration.o

bin/Configuration.o:src/Configuration.cpp
	g++ -Wall -c -g -I include src/Configuration.cpp -o bin/Configuration.o

bin/Dictionary.o:src/Dictionary.cpp
	g++ -Wall -c -g -I include src/Dictionary.cpp -o bin/Dictionary.o

bin/KeyRecommander.o:src/KeyRecommander.cpp
	g++ -Wall -c -g -I include src/KeyRecommander.cpp -o bin/KeyRecommander.o

bin/CandidateResult.o:src/CandidateResult.cpp
	g++ -Wall -c -g -I include src/CandidateResult.cpp -o bin/CandidateResult.o

bin/Acceptor.o:src/Acceptor.cc
	g++ -Wall -c -g src/Acceptor.cc -o bin/Acceptor.o

bin/EchoServer.o:src/EchoServer.cc
	g++ -Wall -c -g src/EchoServer.cc -o bin/EchoServer.o

bin/EventLoop.o:src/EventLoop.cc
	g++ -Wall -c -g src/EventLoop.cc -o bin/EventLoop.o

bin/InetAddress.o:src/InetAddress.cc
	g++ -Wall -c -g src/InetAddress.cc -o bin/InetAddress.o

bin/Socket.o:src/Socket.cc
	g++ -Wall -c -g src/Socket.cc -o bin/Socket.o

bin/SocketIO.o:src/SocketIO.cc
	g++ -Wall -c -g src/SocketIO.cc -o bin/SocketIO.o

bin/TaskQueue.o:src/TaskQueue.cc
	g++ -Wall -c -g src/TaskQueue.cc -o bin/TaskQueue.o

bin/TcpConnection.o:src/TcpConnection.cc
	g++ -Wall -c -g src/TcpConnection.cc -o bin/TcpConnection.o

bin/TcpServer.o:src/TcpServer.cc
	g++ -Wall -c -g src/TcpServer.cc -o bin/TcpServer.o

bin/ThreadPool.o:src/ThreadPool.cc
	g++ -Wall -c -g src/ThreadPool.cc -o bin/ThreadPool.o

bin/SearchEngineServer.o:src/SearchEngineServer.cpp
	g++ -Wall -c -g src/SearchEngineServer.cpp -o bin/SearchEngineServer.o

bin/test.o:src/test.cc
	g++ -Wall -c -g -I include src/test.cc -o bin/test.o

bin/test: bin/Dictionary.o bin/KeyRecommander.o bin/CandidateResult.o bin/Acceptor.o \
          bin/EchoServer.o bin/EventLoop.o bin/InetAddress.o bin/Socket.o bin/SocketIO.o \
        bin/Configuration.o	bin/SearchEngineServer.o  bin/TaskQueue.o bin/TcpConnection.o bin/TcpServer.o bin/ThreadPool.o bin/test.o 
	
	g++ -Wall -g  bin/Dictionary.o bin/KeyRecommander.o bin/CandidateResult.o bin/Acceptor.o \
          bin/EchoServer.o bin/EventLoop.o bin/InetAddress.o bin/Socket.o bin/SocketIO.o \
    bin/Configuration.o    bin/SearchEngineServer.o  bin/TaskQueue.o bin/TcpConnection.o bin/TcpServer.o bin/ThreadPool.o bin/test.o -o bin/test


bin/client.o: test/client.cc
	g++ -g -c test/client.cc -o bin/client.o

bin/client: bin/client.o
	g++ -g bin/client.o -o bin/client

clean:
	rm -f bin/*.o bin/test
