CFLAGS=-g -lpthread -lmysqlclient
SRC=src
TEST=test
OBJ=obj
BIN=bin
INCLUDE=include
INCLUDEDIR = -I ./include
all: buildReceiver buildSender
	echo "ALL have been build successfully!"

buildReceiver : socketConnect.o mysqlConnect.o messageDao.o jsonTransfer.o messageReceiveServer.o receiveMain.o
	g++ ${CFLAGS} -o ${BIN}/msgrcvd \
		${OBJ}/socketConnect.o ${OBJ}/mysqlConnect.o  ${OBJ}/messageDao.o ${OBJ}/jsonTransfer.o ${OBJ}/messageReceiveServer.o ${OBJ}/receiveMain.o
	echo "[OK] Receiver has been build successfully!"

buildSender: socketConnect.o mysqlConnect.o messageDao.o jsonTransfer.o messageSendServer.o sendMain.o
	g++ ${CFLAGS} -o ${BIN}/msgsndd \
		${OBJ}/socketConnect.o ${OBJ}/mysqlConnect.o  ${OBJ}/messageDao.o ${OBJ}/jsonTransfer.o ${OBJ}/messageSendServer.o ${OBJ}/sendMain.o
	echo "[OK] Sender has been build successfully!"

 
 # build object
socketConnect.o : ${SRC}/socketConnect.cpp ${INCLUDE}/socketConnect.h
	g++ ${CFLAGS} ${INCLUDEDIR} -o ${OBJ}/socketConnect.o -c ${SRC}/socketConnect.cpp
	
jsonTransfer.o: ${INCLUDE}/jsonTransfer.h ${SRC}/jsonTransfer.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/jsonTransfer.o ${SRC}/jsonTransfer.cpp
	
messageReceiveServer.o: ${INCLUDE}/MessageReceiveServer.h ${INCLUDE}/socketConnect.h ${SRC}/receiveMessage/MessageReceiveServer.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/messageReceiveServer.o ${SRC}/receiveMessage/MessageReceiveServer.cpp

receiveMain.o: ${SRC}/receiveMessage/MessageReceiveServer.cpp ${SRC}/receiveMessage/receiveMain.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/receiveMain.o ${SRC}/receiveMessage/receiveMain.cpp

mysqlConnect.o: ${INCLUDE}/mysqlConnect.h ${SRC}/mysqlConnect.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/mysqlConnect.o ${SRC}/mysqlConnect.cpp

messageDao.o: ${INCLUDE}/mysqlConnect.h ${INCLUDE}/MessageDao.h ${SRC}/MessageDao.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/messageDao.o ${SRC}/MessageDao.cpp

messageSendServer.o: ${INCLUDE}/MessageSendServer.h ${SRC}/sendMessage/MessageSendServer.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/messageSendServer.o ${SRC}/sendMessage/MessageSendServer.cpp

sendMain.o: ${SRC}/sendMessage/sendMain.cpp
	g++ ${CFLAGS} ${INCLUDEDIR} -c -o ${OBJ}/sendMain.o ${SRC}/sendMessage/sendMain.cpp

