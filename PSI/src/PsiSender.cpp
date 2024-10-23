#include "PsiSender.h"
#include<sys/mman.h>
#include <iostream>
#include <cstdlib>
#include <bitset>
using namespace std;

namespace PSI {

	void PsiSender::runKey1_2(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/outputKey1_2.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		u8* matrixA[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/outputKey1_2.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_c;
		lseek(fd_c,len-1,SEEK_END);
		write(fd_c, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			//////////// Compute matrix Delta /////////////////////////////////

			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			t++;
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_c+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Sender matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		munmap(addr_c, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::runKey1_3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/outputKey1_3.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		u8* matrixA[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/outputKey1_3.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_c;
		lseek(fd_c,len-1,SEEK_END);
		write(fd_c, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			//////////// Compute matrix Delta /////////////////////////////////

			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			t++;
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_c+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Sender matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		munmap(addr_c, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::runKey1_4(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/outputKey1_4.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		u8* matrixA[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/outputKey1_4.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_c;
		lseek(fd_c,len-1,SEEK_END);
		write(fd_c, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			//////////// Compute matrix Delta /////////////////////////////////

			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			t++;
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_c+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Sender matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		munmap(addr_c, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::runKey2_3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/outputKey2_3.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		u8* matrixA[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/outputKey2_3.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_c;
		lseek(fd_c,len-1,SEEK_END);
		write(fd_c, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			//////////// Compute matrix Delta /////////////////////////////////

			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			t++;
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_c+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Sender matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		munmap(addr_c, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::runKey2_4(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/outputKey2_4.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		u8* matrixA[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/outputKey2_4.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_c;
		lseek(fd_c,len-1,SEEK_END);
		write(fd_c, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			//////////// Compute matrix Delta /////////////////////////////////

			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			t++;
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_c+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Sender matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		munmap(addr_c, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::runKey3_4(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/outputKey3_4.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		u8* matrixA[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/outputKey3_4.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_c;
		lseek(fd_c,len-1,SEEK_END);
		write(fd_c, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			//////////// Compute matrix Delta /////////////////////////////////

			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			t++;
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_c+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Sender matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		munmap(addr_c, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}


	void PsiSender::runOffline(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/output_C1.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);

		// std::cout << "Receiver base OT finished\n";
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* matrixA[widthBucket1];
		u8* matrixDelta[widthBucket1];
		u8* matrixC[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixDelta[i] = new u8[heightInBytes];
			matrixC[i] = new u8[heightInBytes];
		}

		u8* transLocations[widthBucket1];// OK
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[receiverSize * locationInBytes + sizeof(u32)];
		}
	
		block randomLocations[bucket1];//The same as sender.
		

		u8* transHashInputs[width];//receiver trans.
		for (auto i = 0; i < width; ++i) {
			transHashInputs[i] = new u8[receiverSizeInBytes];
			memset(transHashInputs[i], 0, receiverSizeInBytes);
		}

		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		


		/////////// Transform input /////////////////////

		commonPrng.get((u8*)&commonKey, sizeof(block));
		commonAes.setKey(commonKey);
		
		block* recvSet = new block[receiverSize];
		block* aesInput = new block[receiverSize];
		block* aesOutput = new block[receiverSize];
		
		RandomOracle H1(h1LengthInBytes);
		u8 h1Output[h1LengthInBytes];
		
		for (auto i = 0; i < receiverSize; ++i) {
			H1.Reset();
			H1.Update((u8*)(senderSet.data() + i), sizeof(block));
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			recvSet[i] = *(block*)(h1Output + sizeof(block));
		}
		
		commonAes.ecbEncBlocks(aesInput, receiverSize, aesOutput);
		for (auto i = 0; i < receiverSize; ++i) {
			recvSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Receiver set transformed\n";
		timer.setTimePoint("Receiver set transformed");
		
		// cout<<"---------------------------------------------\n";
		// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
		// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
		// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
		// cout<<"recvSet1[0] is "<<recvSet[0];
		// cout<<"---------------------------------------------\n";

		// // 写入Matrix D into文件 output_D.txt.
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;


		// 打开文件
		int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);

		u8* addr_c;
		// u8* addr_a; 
		lseek(fd_c,len-1,SEEK_END);
		// lseek(fd_a,len-1,SEEK_END);  

		// lseek(fd_s,lens-1,SEEK_END); 
		// 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子
		write(fd_c, "", 1);
		// write(fd_a, "", 1);

		// write(fd_s, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		// addr1 = (u8*)mmap(NULL, len1, PROT_READ|PROT_WRITE,MAP_SHARED, fd, len1);

		int t=0;

		
		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			//////////// Compute random locations (transposed) ////////////////

			commonPrng.get((u8*)&commonKey, sizeof(block));
			commonAes.setKey(commonKey);

			for (auto low = 0; low < receiverSize; low += bucket1) {
			
				auto up = low + bucket1 < receiverSize ? low + bucket1 : receiverSize;
				commonAes.ecbEncBlocks(recvSet + low, up - low, randomLocations); 
					
				for (auto i = 0; i < w; ++i) {
					for (auto j = low; j < up; ++j) {
						memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);
					}
				}
				
			}
		
		

			//////////// Compute matrix Delta /////////////////////////////////
			
			for (auto i = 0; i < widthBucket1; ++i) {
				memset(matrixDelta[i], 255, heightInBytes);
			}
			
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < receiverSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;//location means the truly location in present of 2-bits.
					
					matrixDelta[i][location >> 3] &= ~(1 << (location & 7));//matrix[i][j]={0-255},location & 7 means the truly changed location between{0-255} 
					// if(j%1000000==0){
					// cout<<s<<" counter c1 is"<<++c1<<" \n";
					// }
				}
			}
			
			
			
			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);

				// matrixA[i][j] ^= matrixDelta[i][j];
				// sentMatrix[i] = new u8[heightInBytes];
				// prng.SetSeed(otMessages[i + wLeft][1]);
				// prng.get(sentMatrix[i], heightInBytes);
				if (choices[i + wLeft]) {
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] = matrixA[i][j]^matrixDelta[i][j];//A^D^r1
					}
				}else{
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] = matrixA[i][j];//A^D^r1
					}
				}
				// for (auto j = 0; j < heightInBytes; ++j) {
				// 	sentMatrix[i][j] ^= matrixA[i][j] ^ matrixDelta[i][j];//A^D^r1
				// }
			
				// ch.asyncSend(otMessages[i + wLeft][0], heightInBytes);
			}
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_c+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
				// memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}
			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);

		munmap(addr_c, len);
		// munmap(addr_a, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::runOffline_next0(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/output_A.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;

		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);

		// std::cout << "Receiver base OT finished\n";
		timer.setTimePoint("Receiver base OT finished");
		
		
		//////////// Initialization ///////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* matrixA[widthBucket1];
		u8* matrixDelta[widthBucket1];
		u8* matrixC[widthBucket1];
		// u8* matrixA1[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixDelta[i] = new u8[heightInBytes];
			matrixC[i] = new u8[heightInBytes];
			// matrixA1[i] = new u8[heightInBytes];
		}

		u8* transLocations[widthBucket1];// OK
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[receiverSize * locationInBytes + sizeof(u32)];
		}
	
		block randomLocations[bucket1];//The same as sender.
		

		u8* transHashInputs[width];//receiver trans.
		for (auto i = 0; i < width; ++i) {
			transHashInputs[i] = new u8[receiverSizeInBytes];
			memset(transHashInputs[i], 0, receiverSizeInBytes);
		}

		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		


		/////////// Transform input /////////////////////

		commonPrng.get((u8*)&commonKey, sizeof(block));
		commonAes.setKey(commonKey);
		
		block* recvSet = new block[receiverSize];
		block* aesInput = new block[receiverSize];
		block* aesOutput = new block[receiverSize];
		
		RandomOracle H1(h1LengthInBytes);
		u8 h1Output[h1LengthInBytes];
		
		for (auto i = 0; i < receiverSize; ++i) {
			H1.Reset();
			H1.Update((u8*)(senderSet.data() + i), sizeof(block));
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			recvSet[i] = *(block*)(h1Output + sizeof(block));
		}
		
		commonAes.ecbEncBlocks(aesInput, receiverSize, aesOutput);
		for (auto i = 0; i < receiverSize; ++i) {
			recvSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Receiver set transformed\n";
		timer.setTimePoint("Receiver set transformed");
		
		// cout<<"---------------------------------------------\n";
		// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
		// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
		// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
		// cout<<"recvSet1[0] is "<<recvSet[0];
		// cout<<"---------------------------------------------\n";

		// // 写入Matrix D into文件 output_D.txt.
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_a = open("/tmp/output_A1.txt", O_RDWR|O_CREAT, 00777);  

		// // // 读取文件长度
		// // int len2 = heightInBytes;
		// // int len1 = len2*widthBucket1;
		// // int len = len1*widthdivide;
		// u8* addr_a;

		// addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);

		// 打开文件
		int fd_c=open("/tmp/output_A.txt", O_RDWR|O_CREAT, 00777);

		u8* addr_c;
		// u8* addr_a; 
		lseek(fd_c,len-1,SEEK_END);
		// lseek(fd_a,len-1,SEEK_END);  

		// lseek(fd_s,lens-1,SEEK_END); 
		// 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子
		write(fd_c, "", 1);
		// write(fd_a, "", 1);

		// write(fd_s, "", 1);
		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		// addr1 = (u8*)mmap(NULL, len1, PROT_READ|PROT_WRITE,MAP_SHARED, fd, len1);

		int t=0;

		
		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////

			commonPrng.get((u8*)&commonKey, sizeof(block));
			commonAes.setKey(commonKey);

			for (auto low = 0; low < receiverSize; low += bucket1) {
			
				auto up = low + bucket1 < receiverSize ? low + bucket1 : receiverSize;
				commonAes.ecbEncBlocks(recvSet + low, up - low, randomLocations); 
					
				for (auto i = 0; i < w; ++i) {
					for (auto j = low; j < up; ++j) {
						memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);
					}
				}
				
			}
		
		

			//////////// Compute matrix Delta /////////////////////////////////
			
			for (auto i = 0; i < widthBucket1; ++i) {
				memset(matrixDelta[i], 255, heightInBytes);
			}
			
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < receiverSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;//location means the truly location in present of 2-bits.
					
					matrixDelta[i][location >> 3] &= ~(1 << (location & 7));//matrix[i][j]={0-255},location & 7 means the truly changed location between{0-255} 
					// if(j%1000000==0){
					// cout<<s<<" counter c1 is"<<++c1<<" \n";
					// }
				}
			}
			
			
			
			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			// for(int k=1;k<widthBucket1+1;k++){
			// 	memcpy(matrixA1[k-1], addr_a+(k-1)*len2+(t-1)*len1, len2);
			// }			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);

				// matrixA[i][j] ^= matrixDelta[i][j];
				// sentMatrix[i] = new u8[heightInBytes];
				// prng.SetSeed(otMessages[i + wLeft][1]);
				// prng.get(sentMatrix[i], heightInBytes);
				if (choices[i + wLeft]) {
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] = matrixA[i][j]^matrixDelta[i][j];//A^D^r1
					}
				}else{
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] = matrixA[i][j];//A^D^r1
					}
				}
				// for (auto j = 0; j < heightInBytes; ++j) {
				// 	sentMatrix[i][j] ^= matrixA[i][j] ^ matrixDelta[i][j];//A^D^r1
				// }
			
				// ch.asyncSend(otMessages[i + wLeft][0], heightInBytes);
			}
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_c+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
				// memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}
			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);
		// close(fd_a);
		munmap(addr_c, len);
		// munmap(addr_a, len);
		// munmap(addr_a, len);

		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}


	void PsiSender::runOffline_next1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {
	//////////Syn The Time ///////////////////////////		
		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
		Timer timer;
		char *savePath_c = "/tmp/output_C2.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_c)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;
		// if(locationInBytes==4){
		// 	locationInBytes=3;
		// }
		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		// auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		BitVector choices(width);
		prng.get(choices.data(), choices.sizeBytes());
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);

		std::cout << "Receiver base OT finished\n";
		// std::cout << "Receiver base OT finished\n";
		timer.setTimePoint("Receiver base OT finished");
		
		
		
		
		//////////// Initialization ///////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* matrixA[widthBucket1];
		u8* matrixDelta[widthBucket1];
		u8* matrixC[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixDelta[i] = new u8[heightInBytes];
			matrixC[i] = new u8[heightInBytes];
		}

		u8* transLocations[widthBucket1];// OK
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[receiverSize * locationInBytes + sizeof(u32)];
		}
	
		block randomLocations[bucket1];//The same as sender.
		

		u8* transHashInputs[width];//receiver trans.
		for (auto i = 0; i < width; ++i) {
			transHashInputs[i] = new u8[receiverSizeInBytes];
			memset(transHashInputs[i], 0, receiverSizeInBytes);
		}

		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Receiver initialized");

		


		/////////// Transform input /////////////////////

		commonPrng.get((u8*)&commonKey, sizeof(block));
		commonAes.setKey(commonKey);
		
		block* recvSet = new block[receiverSize];
		block* aesInput = new block[receiverSize];
		block* aesOutput = new block[receiverSize];
		
		RandomOracle H1(h1LengthInBytes);
		u8 h1Output[h1LengthInBytes];
		
		for (auto i = 0; i < receiverSize; ++i) {
			H1.Reset();
			H1.Update((u8*)(senderSet.data() + i), sizeof(block));
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			recvSet[i] = *(block*)(h1Output + sizeof(block));
		}
		
		commonAes.ecbEncBlocks(aesInput, receiverSize, aesOutput);
		for (auto i = 0; i < receiverSize; ++i) {
			recvSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Receiver set transformed\n";
		timer.setTimePoint("Receiver set transformed");
		
		// cout<<"---------------------------------------------\n";
		// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
		// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
		// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
		// cout<<"recvSet1[0] is "<<recvSet[0];
		// cout<<"---------------------------------------------\n";

		// // 写入Matrix D into文件 output_D.txt.

		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// 打开文件
		int fd_c=open("/tmp/output_C2.txt", O_RDWR|O_CREAT, 00777);

		u8* addr_c;
  
		lseek(fd_c,len-1,SEEK_END);

		write(fd_c, "", 1);

		// 使用mmap函数建立内存映射
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		int t=0;

		
		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			//////////// Compute random locations (transposed) ////////////////

			commonPrng.get((u8*)&commonKey, sizeof(block));
			commonAes.setKey(commonKey);

			for (auto low = 0; low < receiverSize; low += bucket1) {
			
				auto up = low + bucket1 < receiverSize ? low + bucket1 : receiverSize;
				commonAes.ecbEncBlocks(recvSet + low, up - low, randomLocations); 
					
				for (auto i = 0; i < w; ++i) {
					for (auto j = low; j < up; ++j) {
						memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);
					}
				}
				
			}
		
		

			//////////// Compute matrix Delta /////////////////////////////////
			
			for (auto i = 0; i < widthBucket1; ++i) {
				memset(matrixDelta[i], 255, heightInBytes);
			}
			
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < receiverSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;//location means the truly location in present of 2-bits.
					
					matrixDelta[i][location >> 3] &= ~(1 << (location & 7));//matrix[i][j]={0-255},location & 7 means the truly changed location between{0-255} 
				}
			}
			
			
			
			//////////////// Compute matrix A & sent matrix ///////////////////////

			// u8* sentMatrix[w];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				//To replace it is OK
				prng.get(matrixA[i], heightInBytes);
				if (choices[i + wLeft]) {
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] = matrixA[i][j]^matrixDelta[i][j];//A^D^r1
					}
				}else{
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] = matrixA[i][j];//A^D^r1
					}
				}
			}
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_c+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
				// memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}
			
		}

		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_c);

		munmap(addr_c, len);


		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");
		std::cout << timer;
			
		// //////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";	

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::run(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

	//////////Syn The Time ///////////////////////////

		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		Timer timer;
		char *savePath_C = "/tmp/output_C.txt";
		// char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_C)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Sender start");
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;//0001|1110|0101|1010|...
		auto senderSizeInBytes = (senderSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;//which is familier with this as 0001|1100|0101|1000|...|??
		int widthdivide=width/widthBucket1+1;


		//////////////////// Base OTs /////////////////////////////////
		
		IknpOtExtReceiver otExtReceiver;
		otExtReceiver.genBaseOts(prng, ch);
		BitVector choices(width);
		std::vector<block> otMessages(width);
		prng.get(choices.data(), choices.sizeBytes());
		otExtReceiver.receive(choices, otMessages, prng, ch);
		
		// std::cout << "Sender base OT finished\n";


		// cout << " OT size is "<<otMessages[0];
		// cout << " OT size is "<<otMessages[1];
		// cout << " OT size is "<<otMessages[2];
		timer.setTimePoint("Sender base OT finished");

		////////////// Initialization //////////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* transLocations[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[senderSize * locationInBytes + sizeof(u32)];//everysender have locationInBytes
		}
		
		block randomLocations[bucket1];//ok
		
		u8* matrixC[widthBucket1];
		u8* matrixC1[widthBucket1];
		u8* matrixKey2_1[widthBucket1];
		u8* matrixKey2_3[widthBucket1];
		u8* matrixKey2_4[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixC[i] = new u8[heightInBytes];
			matrixC1[i] = new u8[heightInBytes];
			matrixKey2_1[i] = new u8[heightInBytes];
			matrixKey2_3[i] = new u8[heightInBytes];
			matrixKey2_4[i] = new u8[heightInBytes];
		}
		//transHashInputs[sender][width]=0|1|0|0|1|1|0|...
		u8* transHashInputs[width];
		for (auto i = 0; i < width; ++i) {
			transHashInputs[i] = new u8[senderSizeInBytes];
			memset(transHashInputs[i], 0, senderSizeInBytes);
		}

		// std::cout << "Sender initialed\n";
		timer.setTimePoint("Sender initialed");

		/////////// Transform input /////////////////////

		commonPrng.get((u8*)&commonKey, sizeof(block));
		commonAes.setKey(commonKey);
		
		block* sendSet = new block[senderSize];
		block* aesInput = new block[senderSize];
		block* aesOutput = new block[senderSize];
		
		RandomOracle H1(h1LengthInBytes);
		u8 h1Output[h1LengthInBytes];
		
		for (auto i = 0; i < senderSize; ++i) {
			H1.Reset();
			H1.Update((u8*)(senderSet.data() + i), sizeof(block));
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			sendSet[i] = *(block*)(h1Output + sizeof(block));
		}
		//Aes(h1())is OVER.
		commonAes.ecbEncBlocks(aesInput, senderSize, aesOutput);
		for (auto i = 0; i < senderSize; ++i) {
			sendSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Sender set transformed\n";
		timer.setTimePoint("Sender set transformed");

		// 打开文件
		// O_RDWR|O_CREAT, 00777
		int fd_c = open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);  

		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_c;

		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);

		// 打开文件

		int fdKey2_1=open("/tmp/outputKey2_1.txt", O_RDWR|O_CREAT, 00777);
		int fdKey2_3=open("/tmp/outputKey2_3.txt", O_RDWR|O_CREAT, 00777);
		int fdKey2_4=open("/tmp/outputKey2_4.txt", O_RDWR|O_CREAT, 00777);

		u8* addrKey2_1;
		u8* addrKey2_3;
		u8* addrKey2_4;

		addrKey2_1 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey2_1, 0);
		addrKey2_3 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey2_3, 0);
		addrKey2_4 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey2_4, 0);

		int fd_C=open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);		
		u8* addr_C;
		lseek(fd_C,len-1,SEEK_END);
		write(fd_C, "", 1);
		addr_C = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_C, 0);

		// // 打开文件
		// int fd_c3=open("/tmp/output_C3.txt", O_RDWR|O_CREAT, 00777);

		// u8* addr_c3;
  
		// lseek(fd_c3,len-1,SEEK_END);

		// write(fd_c3, "", 1);

		// addr_c3 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c3, 0);

		int t=0;

		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(matrixC1[k-1], addr_c+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey2_1[k-1], addrKey2_1+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey2_3[k-1], addrKey2_3+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey2_4[k-1], addrKey2_4+(k-1)*len2+(t-1)*len1, len2);
			}

			//////////// Compute random locations (transposed) ////////////////

			commonPrng.get((u8*)&commonKey, sizeof(block));
			commonAes.setKey(commonKey);
			
			for (auto low = 0; low < senderSize; low += bucket1) {
			
				auto up = low + bucket1 < senderSize ? low + bucket1 : senderSize;
			
				commonAes.ecbEncBlocks(sendSet + low, up - low, randomLocations);//Fkey(h1) truly.

				for (auto i = 0; i < w; ++i) {
					for (auto j = low; j < up; ++j) {
						// Final i know what's the mean it is.randomLocations + (j - low) means 0001|1110|...|
						//every row have j * locationInBytes,then can be used easyly.
						//(u8*)(randomLocations + (j - low)) + i * locationInBytes means randomLocations[i][jfrom 0 to locationInBytes] copy to transLocations[i][jfrom 0 to locationInBytes]
						memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);//dazhigaodongleyitu.
					}
				}
			}
	

			
			//////////////// Extend OTs and compute matrix C ///////////////////
			//R-OT process.
			u8* recvMatrix;
			recvMatrix = new u8[heightInBytes];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixC[i], heightInBytes);
				
				ch.recv(recvMatrix, heightInBytes);
				
				// if (choices[i + wLeft]) {
				// 	for (auto j = 0; j < heightInBytes; ++j) {
				// 		matrixC[i][j] ^= recvMatrix[j]^matrixC1[i][j];
				// 	}
				// }else{
				// 	for (auto j = 0; j < heightInBytes; ++j) {
				// 		matrixC[i][j] ^= matrixC1[i][j];
				// 	}					
				// }
				if (choices[i + wLeft]) {
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] ^= recvMatrix[j];
					}
				}
				// memcpy(addr_c3+(i)*len2+(t-1)*len1, matrixC[i], len2);
				for (auto j = 0; j < heightInBytes; ++j) {
					// matrixC[i][j] ^= matrixC1[i][j];
					matrixC[i][j] ^= matrixC1[i][j] ^ matrixKey2_1[i][j] ^ matrixKey2_3[i][j] ^ matrixKey2_4[i][j];
				}							
				// matrixC[i][j] ^= matrixC1[i][j];
			}
			for(int k=1;k<w+1;k++){
				memcpy(addr_C+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
				// memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}
			///////////////// Compute hash inputs (transposed) /////////////////////
			
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < senderSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					//it is really excellent transHashInputs ments the senderSize*w outputs.
					transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixC[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
				}		
			}

		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_c);
		close(fd_C);
		close(fdKey2_1);
		close(fdKey2_3);
		close(fdKey2_4);
		// close(fd_c3);
		// 解除映射
		munmap(addr_c, len);
		munmap(addr_C, len);
		munmap(addrKey2_1, len);
		munmap(addrKey2_3, len);
		munmap(addrKey2_4, len);
		// munmap(addr_c3, len);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
	
	
		/////////////////// Compute hash outputs ///////////////////////////
		
		RandomOracle H(hashLengthInBytes);
		u8 hashOutput[sizeof(block)];

		u8* hashInputs[bucket2];
		
		for (auto i = 0; i < bucket2; ++i) {
			hashInputs[i] = new u8[widthInBytes];
		}
		
		for (auto low = 0; low < senderSize; low += bucket2) {
			auto up = low + bucket2 < senderSize ? low + bucket2 : senderSize;
			
			for (auto j = low; j < up; ++j) {
				memset(hashInputs[j - low], 0, widthInBytes);
			}
			
			for (auto i = 0; i < width; ++i) {
				for (auto j = low; j < up; ++j) {
					hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//means * 2^(i & 7),that is OK!
				}
			}
			
			u8* sentBuff = new u8[(up - low) * hashLengthInBytes];
			
			for (auto j = low; j < up; ++j) {
				H.Reset();
				H.Update(hashInputs[j - low], widthInBytes);
				H.Final(hashOutput);
				
				memcpy(sentBuff + (j - low) * hashLengthInBytes, hashOutput, hashLengthInBytes);
			}
			
			ch.asyncSend(sentBuff, (up - low) * hashLengthInBytes);//yipiyipi send to receiver.
		}
		
		// std::cout << "Sender hash outputs computed and sent\n";
		timer.setTimePoint("Sender hash outputs computed and sent");
		
		std::cout << timer;

		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.	
	}

	void PsiSender::run_next1(Channel& ch, const u64& senderSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

	//////////Syn The Time ///////////////////////////

		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		Timer timer;
		timer.setTimePoint("Sender start");
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;//0001|1110|0101|1010|...
		auto senderSizeInBytes = (senderSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;//which is familier with this as 0001|1100|0101|1000|...|??
		int widthdivide=width/widthBucket1+1;

		////////////// Initialization //////////////////////

		// std::cout << "Sender initialed\n";
		timer.setTimePoint("Sender initialed");




		// 打开文件
		// O_RDWR|O_CREAT, 00777
		int fd_c = open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);  

		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_c;

		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		// addr1 = (u8*)mmap(NULL, len1, PROT_READ|PROT_WRITE,MAP_SHARED, fd, len1);
		
		int t=0;

		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			u8* sentMatrix[w];
			for(int k=1;k<widthBucket1+1;k++){
				sentMatrix[k-1] = new u8[heightInBytes];
				memcpy(sentMatrix[k-1], addr_c+(k-1)*len2+(t-1)*len1, len2);
				ch.asyncSend(sentMatrix[k-1], heightInBytes);
			}
			//////////////// Extend OTs and compute matrix C ///////////////////
			//R-OT process.
			
			// for (auto i = 0; i < w; ++i) {
			// 	ch.asyncSend(sentMatrix[i], heightInBytes);
			// }
		}
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender Send The Hybrid MatrixC");

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_c);
		// 解除映射
		munmap(addr_c, len);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		std::cout << timer;

		// ch.recv(SynTime, hashLengthInBytes);
		// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
	}

	void PsiSender::run_next2(Channel& ch, const u64& senderSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

	//////////Syn The Time ///////////////////////////

		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		Timer timer;
		timer.setTimePoint("Sender start");
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;//0001|1110|0101|1010|...
		auto senderSizeInBytes = (senderSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;//which is familier with this as 0001|1100|0101|1000|...|??
		int widthdivide=width/widthBucket1+1;

		////////////// Initialization //////////////////////
		

		// std::cout << "Sender initialed\n";
		timer.setTimePoint("Sender initialed");




		// 打开文件
		// O_RDWR|O_CREAT, 00777
		int fd_c = open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);  

		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_c;

		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		// addr1 = (u8*)mmap(NULL, len1, PROT_READ|PROT_WRITE,MAP_SHARED, fd, len1);
		
		int t=0;

		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			u8* sentMatrix[w];
			for(int k=1;k<widthBucket1+1;k++){
				sentMatrix[k-1] = new u8[heightInBytes];
				memcpy(sentMatrix[k-1], addr_c+(k-1)*len2+(t-1)*len1, len2);
				ch.asyncSend(sentMatrix[k-1], heightInBytes);
			}
			//////////////// Extend OTs and compute matrix C ///////////////////
			//R-OT process.
		}
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender Send The Hybrid MatrixC");

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_c);
		// 解除映射
		munmap(addr_c, len);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		std::cout << timer;

		// ch.recv(SynTime, hashLengthInBytes);
		// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
	}

	void PsiSender::run_next3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& height1, const u64& logHeight1, const u64& width, const u64& width1, std::vector<block>& senderSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

	//////////Syn The Time ///////////////////////////

		u8* SynTime = new u8[hashLengthInBytes];
		ch.recv(SynTime, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		Timer timer;
		timer.setTimePoint("Sender start");

		char *savePath_Sender = "/tmp/output_S.txt";
		if(remove(savePath_Sender)==0){
		cout<<"The path is delete successfully\n";
		}
		int i=0;
		// // 写入Matrix D into文件 output_D.txt.
		int lens = senderSize*hashLengthInBytes;
		int lenhashBatch=hashLengthInBytes*bucket2;
		// 打开文件
		int fd_s=open("/tmp/output_S.txt", O_RDWR|O_CREAT, 00777);

		u8* addr_s;

		lseek(fd_s,lens-1,SEEK_END); 
		// lseek(fd_s,lens-1,SEEK_END); 
		// 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子

		write(fd_s, "", 1);
		// write(fd_s, "", 1);
		// 使用mmap函数建立内存映射
		addr_s = (u8*)mmap(NULL, lens, PROT_READ|PROT_WRITE,MAP_SHARED, fd_s, 0);
		// addr_s = (u8*)mmap(NULL, lens, PROT_READ|PROT_WRITE,MAP_SHARED, fd_s, 0);
		// int t=0;			
	if(i==0){
		i++;
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;//0001|1110|0101|1010|...
		auto senderSizeInBytes = (senderSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;//which is familier with this as 0001|1100|0101|1000|...|??
		int widthdivide=width/widthBucket1+1;

		////////////// Initialization //////////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* transLocations[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[senderSize * locationInBytes + sizeof(u32)];//everysender have locationInBytes
		}
		
		block randomLocations[bucket1];//ok
		
		u8* matrixC[widthBucket1];
		// u8* matrixC1[widthBucket1];
		// u8* matrixC2[widthBucket1];
		// u8* matrixC3[widthBucket1];
		// u8* matrixC4[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixC[i] = new u8[heightInBytes];
			// matrixC1[i] = new u8[heightInBytes];
			// matrixC2[i] = new u8[heightInBytes];
			// matrixC3[i] = new u8[heightInBytes];
			// matrixC4[i] = new u8[heightInBytes];
		}
		//transHashInputs[sender][width]=0|1|0|0|1|1|0|...
		u8* transHashInputs[width];
		for (auto i = 0; i < width; ++i) {
			transHashInputs[i] = new u8[senderSizeInBytes];
			memset(transHashInputs[i], 0, senderSizeInBytes);
		}

		// std::cout << "Sender initialed\n";
		// timer.setTimePoint("Sender initialed");


		/////////// Transform input /////////////////////

		commonPrng.get((u8*)&commonKey, sizeof(block));
		commonAes.setKey(commonKey);
		
		block* sendSet = new block[senderSize];
		block* aesInput = new block[senderSize];
		block* aesOutput = new block[senderSize];
		
		RandomOracle H1(h1LengthInBytes);
		u8 h1Output[h1LengthInBytes];
		
		for (auto i = 0; i < senderSize; ++i) {
			H1.Reset();
			H1.Update((u8*)(senderSet.data() + i), sizeof(block));
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			sendSet[i] = *(block*)(h1Output + sizeof(block));
		}
		//Aes(h1())is OVER.
		commonAes.ecbEncBlocks(aesInput, senderSize, aesOutput);
		for (auto i = 0; i < senderSize; ++i) {
			sendSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Sender set transformed\n";
		// timer.setTimePoint("Sender set transformed");

		// cout<<"---------------------------------------------\n";
		// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
		// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
		// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
		// cout<<"recvSet1[0] is "<<sendSet[0];
		// cout<<"---------------------------------------------\n";

		// 打开文件
		// O_RDWR|O_CREAT, 00777
		int fd_c = open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);
		// int fd_c3 = open("/tmp/output_C3.txt", O_RDWR|O_CREAT, 00777);   
		// int fd_c1 = open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777); 
		// int fd_c2 = open("/tmp/output_C2.txt", O_RDWR|O_CREAT, 00777); 
		// int fd_c4 = open("/tmp/output_C4.txt", O_RDWR|O_CREAT, 00777); 
		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_c;
		// u8* addr_c3;
		// u8* addr_c1;
		// u8* addr_c2;
		// u8* addr_c4;
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		// addr_c3 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c3, 0);
		// addr_c1 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c1, 0);
		// addr_c2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c2, 0);
		// addr_c4 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c4, 0);
		
		int t=0;

		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(matrixC[k-1], addr_c+(k-1)*len2+(t-1)*len1, len2);
				// memcpy(matrixC3[k-1], addr_c3+(k-1)*len2+(t-1)*len1, len2);
				// memcpy(matrixC1[k-1], addr_c1+(k-1)*len2+(t-1)*len1, len2);
				// memcpy(matrixC2[k-1], addr_c2+(k-1)*len2+(t-1)*len1, len2);
				// memcpy(matrixC4[k-1], addr_c4+(k-1)*len2+(t-1)*len1, len2);
			}

			//////////// Compute random locations (transposed) ////////////////

			commonPrng.get((u8*)&commonKey, sizeof(block));
			commonAes.setKey(commonKey);
			
			for (auto low = 0; low < senderSize; low += bucket1) {
			
				auto up = low + bucket1 < senderSize ? low + bucket1 : senderSize;
			
				commonAes.ecbEncBlocks(sendSet + low, up - low, randomLocations);//Fkey(h1) truly.

				for (auto i = 0; i < w; ++i) {
					for (auto j = low; j < up; ++j) {
						// Final i know what's the mean it is.randomLocations + (j - low) means 0001|1110|...|
						//every row have j * locationInBytes,then can be used easyly.
						//(u8*)(randomLocations + (j - low)) + i * locationInBytes means randomLocations[i][jfrom 0 to locationInBytes] copy to transLocations[i][jfrom 0 to locationInBytes]
						memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);//dazhigaodongleyitu.
					}
				}
			}
	

			
			//////////////// Extend OTs and compute matrix C ///////////////////


			///////////////// Compute hash inputs (transposed) /////////////////////
			
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < senderSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					//it is really excellent transHashInputs ments the senderSize*w outputs.
					transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixC[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
				}		
			}

		}
	
		// std::cout << "Sender transposed hash input computed\n";
		// timer.setTimePoint("Sender transposed hash input computed");

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_c);
		// close(fd_c3);
		// close(fd_c1);
		// close(fd_c2);
		// close(fd_c4);
		// 解除映射
		munmap(addr_c, len);
		// munmap(addr_c3, len);
		// munmap(addr_c1, len);
		// munmap(addr_c2, len);
		// munmap(addr_c4, len);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";


		/////////////////// Compute hash outputs ///////////////////////////
		
		RandomOracle H(hashLengthInBytes);
		u8 hashOutput[sizeof(block)];

		u8* hashInputs[bucket2];
		
		for (auto i = 0; i < bucket2; ++i) {
			hashInputs[i] = new u8[widthInBytes];
		}
		int s1=0;
		for (auto low = 0; low < senderSize; low += bucket2) {
			auto up = low + bucket2 < senderSize ? low + bucket2 : senderSize;
			s1++;
			for (auto j = low; j < up; ++j) {
				memset(hashInputs[j - low], 0, widthInBytes);
			}
			
			for (auto i = 0; i < width; ++i) {
				for (auto j = low; j < up; ++j) {
					hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//means * 2^(i & 7),that is OK!
				}
			}
			
			u8* sentBuff = new u8[(up - low) * hashLengthInBytes];
			
			for (auto j = low; j < up; ++j) {
				H.Reset();
				H.Update(hashInputs[j - low], widthInBytes);
				H.Final(hashOutput);
				memcpy(addr_s+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
				// memcpy(sentBuff + (j - low) * hashLengthInBytes, hashOutput, hashLengthInBytes);
			}
			
			// ch.asyncSend(sentBuff, (up - low) * hashLengthInBytes);//yipiyipi send to receiver.
		}
		
		// std::cout << "Sender hash outputs computed and sent\n";
		timer.setTimePoint("Sender hash outputs FIRST computed!");
	}



	if(i==1){
		auto heightInBytes = (height1 + 7) / 8;
		auto widthInBytes = (width1 + 7) / 8;
		auto locationInBytes = (logHeight1 + 7) / 8;//0001|1110|0101|1010|...
		auto senderSizeInBytes = (senderSize + 7) / 8;
		auto shift = (1 << logHeight1) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;//which is familier with this as 0001|1100|0101|1000|...|??



		//////////////////// Base OTs /////////////////////////////////
		
		IknpOtExtReceiver otExtReceiver;
		otExtReceiver.genBaseOts(prng, ch);
		BitVector choices(width1);
		std::vector<block> otMessages(width1);
		prng.get(choices.data(), choices.sizeBytes());
		otExtReceiver.receive(choices, otMessages, prng, ch);
		
		// std::cout << "Sender base OT finished\n";


		// cout << " OT size is "<<otMessages[0];
		// cout << " OT size is "<<otMessages[1];
		// cout << " OT size is "<<otMessages[2];
		timer.setTimePoint("Sender base OT finished");




		////////////// Initialization //////////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* transLocations[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[senderSize * locationInBytes + sizeof(u32)];//everysender have locationInBytes
		}
		
		block randomLocations[bucket1];//ok
		
		u8* matrixC[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixC[i] = new u8[heightInBytes];
		}
		//transHashInputs[sender][width]=0|1|0|0|1|1|0|...
		u8* transHashInputs[width1];
		for (auto i = 0; i < width1; ++i) {
			transHashInputs[i] = new u8[senderSizeInBytes];
			memset(transHashInputs[i], 0, senderSizeInBytes);
		}

		// std::cout << "Sender initialed\n";
		timer.setTimePoint("Sender initialed");



		/////////// Transform input /////////////////////

		commonPrng.get((u8*)&commonKey, sizeof(block));
		commonAes.setKey(commonKey);
		
		block* sendSet = new block[senderSize];
		block* aesInput = new block[senderSize];
		block* aesOutput = new block[senderSize];
		
		RandomOracle H1(h1LengthInBytes);
		u8 h1Output[h1LengthInBytes];
		u8 h1Output_Copy[h1LengthInBytes];
		for (auto i = 0; i < senderSize; ++i) {
			H1.Reset();
			// H1.Update((u8*)(senderSet.data() + i), sizeof(block));
			memcpy(h1Output_Copy, addr_s+i*hashLengthInBytes, hashLengthInBytes);
			H1.Update(h1Output_Copy, hashLengthInBytes);
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			sendSet[i] = *(block*)(h1Output + sizeof(block));
		}
		//Aes(h1())is OVER.
		commonAes.ecbEncBlocks(aesInput, senderSize, aesOutput);
		for (auto i = 0; i < senderSize; ++i) {
			sendSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Sender set transformed\n";
		timer.setTimePoint("Sender set transformed");

		// cout<<"---------------------------------------------\n";
		// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
		// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
		// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
		// cout<<"recvSet1[0] is "<<sendSet[0];
		// cout<<"---------------------------------------------\n";



		for (auto wLeft = 0; wLeft < width1; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width1 ? wLeft + widthBucket1 : width1;
			auto w = wRight - wLeft;

			//////////// Compute random locations (transposed) ////////////////

			commonPrng.get((u8*)&commonKey, sizeof(block));
			commonAes.setKey(commonKey);
			
			for (auto low = 0; low < senderSize; low += bucket1) {
			
				auto up = low + bucket1 < senderSize ? low + bucket1 : senderSize;
			
				commonAes.ecbEncBlocks(sendSet + low, up - low, randomLocations);//Fkey(h1) truly.

				for (auto i = 0; i < w; ++i) {
					for (auto j = low; j < up; ++j) {
						// Final i know what's the mean it is.randomLocations + (j - low) means 0001|1110|...|
						//every row have j * locationInBytes,then can be used easyly.
						//(u8*)(randomLocations + (j - low)) + i * locationInBytes means randomLocations[i][jfrom 0 to locationInBytes] copy to transLocations[i][jfrom 0 to locationInBytes]
						memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);//dazhigaodongleyitu.
					}
				}
			}
	

			
			//////////////// Extend OTs and compute matrix C ///////////////////
			//R-OT process.
			u8* recvMatrix;
			recvMatrix = new u8[heightInBytes];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixC[i], heightInBytes);
				
				ch.recv(recvMatrix, heightInBytes);
				
				if (choices[i + wLeft]) {
					for (auto j = 0; j < heightInBytes; ++j) {
						matrixC[i][j] ^= recvMatrix[j];
					}
				}
			}


			///////////////// Compute hash inputs (transposed) /////////////////////
			
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < senderSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					//it is really excellent transHashInputs ments the senderSize*w outputs.
					transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixC[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
				}		
			}

		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");
	
		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
	
	
		/////////////////// Compute hash outputs ///////////////////////////
		
		RandomOracle H(hashLengthInBytes);
		u8 hashOutput[sizeof(block)];

		u8* hashInputs[bucket2];
		
		for (auto i = 0; i < bucket2; ++i) {
			hashInputs[i] = new u8[widthInBytes];
		}
		
		for (auto low = 0; low < senderSize; low += bucket2) {
			auto up = low + bucket2 < senderSize ? low + bucket2 : senderSize;
			
			for (auto j = low; j < up; ++j) {
				memset(hashInputs[j - low], 0, widthInBytes);
			}
			
			for (auto i = 0; i < width1; ++i) {
				for (auto j = low; j < up; ++j) {
					hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//means * 2^(i & 7),that is OK!
				}
			}
			
			u8* sentBuff = new u8[(up - low) * hashLengthInBytes];
			
			for (auto j = low; j < up; ++j) {
				H.Reset();
				H.Update(hashInputs[j - low], widthInBytes);
				H.Final(hashOutput);
				
				memcpy(sentBuff + (j - low) * hashLengthInBytes, hashOutput, hashLengthInBytes);
			}
			
			ch.asyncSend(sentBuff, (up - low) * hashLengthInBytes);//yipiyipi send to receiver.
		}
		
		// std::cout << "Sender hash outputs computed and sent\n";
		timer.setTimePoint("Sender hash outputs computed and sent");

	}
		close(fd_s);
		// 解除映射
		munmap(addr_s, lens);
		std::cout << timer;

		// ch.recv(SynTime, hashLengthInBytes);
		// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.		
	}

}
