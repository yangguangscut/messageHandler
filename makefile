CFLAGS=-g -lpthread -lmysqlclient -std=c99
SRC=src
TEST=test
OBJ=obj
BIN=bin
INCLUDE=include
INCLUDEDIR = -I ./include
all: buildAll
	echo "Build successfully!"

run: 
	#${TARGET}/server
	#${TARGET}/client
	${TARGET}/sql_api

buildAll : socketConnect.o  jsonTransfer.o messageReceiverServer.o messageServerMain.o
	g++ ${CFLAGS} -o ${BIN}/msgrcvd \
		${OBJ}/socketConnect.o ${OBJ}/jsonTransfer.o  ${OBJ}/messageReceiverServer.o ${OBJ}/messageServerMain.o 
	echo "build successfully!"

testConnect: testServer testClient
	echo "build successfully!"

testServer: socketConnect.o testServer.o
	g++ ${CFLAGS} -o ${BIN}/testServer \
		${OBJ}/testServer.o ${OBJ}/socketConnect.o
		
testClient: socketConnect.o testClient.o
	g++ ${CFLAGS} -o ${BIN}/testClient \
		${OBJ}/testClient.o ${OBJ}/socketConnect.o

rebuild: clean build
	echo rebuilded!
 
 
 # build object
socketConnect.o : ${SRC}/socketConnect.cpp ${INCLUDE}/socketConnect.h
	g++ ${CFLAGS} ${INCLUDEDIR} -o ${OBJ}/socketConnect.o -c ${SRC}/socketConnect.cpp
	
testServer.o: ${INCLUDE}/socketConnect.h ${TEST}/testServer.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -o ${OBJ}/testServer.o -c ${TEST}/testServer.cpp
	
testClient.o: ${INCLUDE}/socketConnect.h ${TEST}/testClient.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -o ${OBJ}/testClient.o -c ${TEST}/testClient.cpp

testJSON.o: ${TEST}/testJSON.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/testJSON.o ${TEST}/testJSON.cpp
	
jsonTransfer.o: ${INCLUDE}/jsonTransfer.h ${SRC}/jsonTransfer.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/jsonTransfer.o ${SRC}/jsonTransfer.cpp
	
messageReceiverServer.o: ${INCLUDE}/MessageReceiveServer.h ${INCLUDE}/socketConnect.h ${SRC}/sendMessage/MessageReceiveServer.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/messageReceiverServer.o ${SRC}/sendMessage/MessageReceiveServer.cpp

messageServerMain.o: ${SRC}/sendMessage/MessageReceiveServer.cpp ${SRC}/sendMessage/messageServerMain.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/messageServerMain.o ${SRC}/sendMessage/messageServerMain.cpp
	
clean :
	rm  -rf ${BIN}/*
	rm  -rf ${OBJ}/*
