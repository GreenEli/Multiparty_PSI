#include "PsiReceiver.h"
#include<sys/mman.h>
#include <array>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <iomanip>
#include <bitset>
#include <thread>
using namespace std;

namespace PSI {

	void PsiReceiver::runKey2_1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"KEY KEY KEY KEY KEY The Process of P1 Connection With P2 KEY KEY KEY KEY KEY \n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/outputKey2_1.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/outputKey2_1.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_a+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Receiver matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }
		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}

	void PsiReceiver::runKey3_1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"KEY KEY KEY KEY KEY The Process of P1 Connection With P3 KEY KEY KEY KEY KEY \n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/outputKey3_1.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/outputKey3_1.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_a+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Receiver matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }
		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}

	void PsiReceiver::runKey4_1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"KEY KEY KEY KEY KEY The Process of P1 Connection With P4 KEY KEY KEY KEY KEY \n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/outputKey4_1.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/outputKey4_1.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_a+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Receiver matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }
		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}

	void PsiReceiver::runKey3_2(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"KEY KEY KEY KEY KEY The Process of P2 Connection With P3 KEY KEY KEY KEY KEY \n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/outputKey3_2.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/outputKey3_2.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_a+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Receiver matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }
		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}

	void PsiReceiver::runKey4_2(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"KEY KEY KEY KEY KEY The Process of P2 Connection With P4 KEY KEY KEY KEY KEY \n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/outputKey4_2.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/outputKey4_2.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_a+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Receiver matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }
		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}

	void PsiReceiver::runKey4_3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"KEY KEY KEY KEY KEY The Process of P3 Connection With P4 KEY KEY KEY KEY KEY \n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/outputKey4_3.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/outputKey4_3.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				memcpy(addr_a+(i)*len2+(t-1)*len1, matrixA[i], len2);
			}
			// if(t%10==0){
			// 	cout<<"---------------------------------------------\n";
			// 	std::cout<<"Receiver matrixA[0][0] is "<<int(matrixA[0][0])<<"\n";			
			// 	cout<<"---------------------------------------------\n";
			// }
		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}


	void PsiReceiver::runOffline(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"P2->P1 The Process of P1 Connection With P2 For P2->P1\n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

		Timer timer;
		char *savePath_a = "/tmp/output_A1.txt";
		if(remove(savePath_a)==0){
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
		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";		
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<otMessages[0]<<"\n";	
		// std::cout<<"Choice is "<<otMessages[10]<<"\n";	
		// std::cout<<"Choice is "<<otMessages[20]<<"\n";		
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";

		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/output_A1.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			u8* recvMatrix;
			recvMatrix = new u8[heightInBytes];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
			}
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}

		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;
		// u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);
	}

	void PsiReceiver::runOffline_next0(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"The Process of P1 Connection With P2 For P1->P2\n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

		Timer timer;
		char *savePath_a = "/tmp/output_C.txt";
		if(remove(savePath_a)==0){
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
		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";		
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<otMessages[0]<<"\n";	
		// std::cout<<"Choice is "<<otMessages[10]<<"\n";	
		// std::cout<<"Choice is "<<otMessages[20]<<"\n";		
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";

		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];
		u8* matrixC1[widthBucket1];
		u8* matrixKey2_1[widthBucket1];
		u8* matrixKey2_3[widthBucket1];
		u8* matrixKey2_4[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixC1[i] = new u8[heightInBytes];
			matrixKey2_1[i] = new u8[heightInBytes];
			matrixKey2_3[i] = new u8[heightInBytes];
			matrixKey2_4[i] = new u8[heightInBytes];			
		}

		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);

		// 打开文件
		// O_RDWR|O_CREAT, 00777
		int fd_c = open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);  

		// 读取文件长度
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


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			u8* recvMatrix;
			recvMatrix = new u8[heightInBytes];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
				for (auto j = 0; j < heightInBytes; ++j) {
					// matrixC[i][j] ^= matrixC1[i][j];
					matrixA[i][j] ^= matrixC1[i][j] ^ matrixKey2_1[i][j] ^ matrixKey2_3[i][j] ^ matrixKey2_4[i][j];
				}
			}


			for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}

		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		close(fd_c);
		munmap(addr_a, len);
		munmap(addr_c, len);

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fdKey2_1);
		close(fdKey2_3);
		close(fdKey2_4);
		// close(fd_c3);
		// 解除映射
		munmap(addrKey2_1, len);
		munmap(addrKey2_3, len);
		munmap(addrKey2_4, len);

		std::cout << timer;
		// u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);
	}

	void PsiReceiver::runOffline_next1(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"The Process of P3 Connection With P1\n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.

		ch.recv(SynTime, hashLengthInBytes);
		Timer timer;
		char *savePath_a = "/tmp/output_A2.txt";
		if(remove(savePath_a)==0){
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
		for(int i=0;i<width;i++){
			choices[i]=0;
		}
		otExtReceiver.receive(choices, otMessages, prng, ch);

		// std::cout << "Sender base OT finished\n";
		// cout<<"---------------------------------------------\n";
		// std::cout<<"Choice is "<<choices<<"\n";
		// std::cout<<"Choice is "<<int(choices[1])<<"\n";
		// std::cout<<"Choice is "<<int(choices[2])<<"\n";		
		// std::cout<<"Choice is "<<int(choices[4])<<"\n";				
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		timer.setTimePoint("Sender base OT finished");

		u8* matrixA[widthBucket1];

		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.

		}
		// std::cout << "Receiver initialized\n";
		timer.setTimePoint("Sender initialized");

		// int Selflen2=SelfheightInBytes;
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;

		// int fd_c=open("/tmp/output_C1.txt", O_RDWR|O_CREAT, 00777);
		int fd_a=open("/tmp/output_A2.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_a;
		lseek(fd_a,len-1,SEEK_END);  
		write(fd_a, "", 1);
		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;

			//////////// Compute random locations (transposed) ////////////////


			//////////////// Compute random matrix A ///////////////////
			//R-OT process.
			u8* recvMatrix;
			recvMatrix = new u8[heightInBytes];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft]);
				prng.get(matrixA[i], heightInBytes);
			}
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_a+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			}

		}
	
		// std::cout << "Sender transposed hash input computed\n";
		timer.setTimePoint("Sender transposed hash input computed");


		// 内存映射建立好了，此时可以关闭文件了, Put This into Final
		close(fd_a);
		munmap(addr_a, len);
		std::cout << timer;

		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

	}

	void PsiReceiver::run(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

		Timer timer;
		char *savePath_A = "/tmp/output_A.txt";
		if(remove(savePath_A)==0){
		cout<<"The path is delete successfully\n";
		}
		timer.setTimePoint("Receiver start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;
		// if(locationInBytes==4){
		// 	locationInBytes=3;
		// }
		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		
		std::vector<std::array<block, 2> > otMessages(width);

		otExtSender.send(otMessages, prng, ch);

		// std::cout << "Receiver base OT finished\n";
		timer.setTimePoint("Receiver base OT finished");
		
		
		
		
		//////////// Initialization ///////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* matrixA[widthBucket1];
		u8* matrixA1[widthBucket1];
		u8* matrixDelta[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixDelta[i] = new u8[heightInBytes];
			matrixA1[i] = new u8[heightInBytes];
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
			H1.Update((u8*)(receiverSet.data() + i), sizeof(block));
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
		
		int fd_a = open("/tmp/output_A1.txt", O_RDWR|O_CREAT, 00777);  

		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_a;

		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);

		int fd_A=open("/tmp/output_A.txt", O_RDWR|O_CREAT, 00777);
		u8* addr_A;
		lseek(fd_A,len-1,SEEK_END);  
		write(fd_A, "", 1);
		addr_A = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_A, 0);
		
		int t=0;
		
		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(matrixA1[k-1], addr_a+(k-1)*len2+(t-1)*len1, len2);
			}
			//////////// Compute random locations (transposed) ////////////////
			// if(s%1000==0)
			// cout<<s<<" counter s is"<<s<<" \n";
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

			u8* sentMatrix[w];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				prng.get(matrixA[i], heightInBytes);

				//---------------------------- This Way To Copy The MatrixA -------------------------------------------------------
				// for(int k=1;k<widthBucket1+1;k++){
				memcpy(addr_A+(i)*len2+(t-1)*len1, matrixA[i], len2);
				// }
				//---------------------------- This Way To Copy The MatrixA -------------------------------------------------------

				sentMatrix[i] = new u8[heightInBytes];
				prng.SetSeed(otMessages[i + wLeft][1]);
				prng.get(sentMatrix[i], heightInBytes);
				
				for (auto j = 0; j < heightInBytes; ++j) {
					sentMatrix[i][j] ^= matrixA[i][j] ^ matrixDelta[i][j];//A^D^r1
					matrixA[i][j] ^= matrixA1[i][j];
				}
				// for (auto j = 0; j < heightInBytes; ++j) {
				// 	matrixA[i][j] ^= matrixA1[i][j];
				// }
				
				ch.asyncSend(sentMatrix[i], heightInBytes);
			}

			// for(int k=1;k<widthBucket1+1;k++){
			// 	memcpy(addr_A+(k-1)*len2+(t-1)*len1, matrixA[k-1], len2);
			// }
						
			///////////////// Compute hash inputs (transposed) /////////////////////
	
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < receiverSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					
					transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixA[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
					// if(j%1000000==0){
					// cout<<s<<" counter c2 is"<<++c2<<" \n";
					// }
				}		
			}
			
		}

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_a);
		close(fd_A);
		// 解除映射
		munmap(addr_a, len);
		munmap(addr_A, len);

		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		
		// std::cout << "Receiver matrix sent and transposed hash input computed\n";
		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");



		/////////////////// Compute hash outputs ///////////////////////////
		
		RandomOracle H(hashLengthInBytes);
		u8 hashOutput[sizeof(block)];
		std::unordered_map<u64, std::vector<std::pair<block, u32>>> allHashes;
		u8* hashInputs[bucket2];
		for (auto i = 0; i < bucket2; ++i) {
			hashInputs[i] = new u8[widthInBytes];
		}
		
		for (auto low = 0; low < receiverSize; low += bucket2) {
			auto up = low + bucket2 < receiverSize ? low + bucket2 : receiverSize;
			
			for (auto j = low; j < up; ++j) {
				memset(hashInputs[j - low], 0, widthInBytes);
			}
			
			for (auto i = 0; i < width; ++i) {
				for (auto j = low; j < up; ++j) {
					hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//transform to output of 0|1|0|0|1|...
				}
			}
			
			for (auto j = low; j < up; ++j) {
				H.Reset();
				H.Update(hashInputs[j - low], widthInBytes);
				H.Final(hashOutput);
				
				allHashes[*(u64*)hashOutput].push_back(std::make_pair(*(block*)hashOutput, j));
			}
		}
		
		// std::cout << "Receiver hash outputs computed\n";
		timer.setTimePoint("Receiver hash outputs computed");
		
	
	
		
		///////////////// Receive hash outputs from sender and compute PSI ///////////////////

		u8* recvBuff = new u8[bucket2 * hashLengthInBytes];//output0001|1111|1010|... to 01010101010101010
		
		auto psi = 0;
		
		for (auto low = 0; low < senderSize; low += bucket2) {
			auto up = low + bucket2 < senderSize ? low + bucket2 : senderSize;
			
			ch.recv(recvBuff, (up - low) * hashLengthInBytes);
			
			for (auto idx = 0; idx < up - low; ++idx) {
				u64 mapIdx = *(u64*)(recvBuff + idx * hashLengthInBytes);
				
				auto found = allHashes.find(mapIdx);
				if (found == allHashes.end()) continue;
				
				for (auto i = 0; i < found->second.size(); ++i) {
					if (memcmp(&(found->second[i].first), recvBuff + idx * hashLengthInBytes, hashLengthInBytes) == 0) {
						++psi;
						break;
					}
				}
			}
		}
		
		std::cout << "Receiver intersection computed"<< psi <<"- correct!\n";
		timer.setTimePoint("Receiver intersection computed");
		
		
		std::cout << timer;
		

			
		//////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";

		// u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);
	}

	void PsiReceiver::run_next1(Channel& ch, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"The Process of P2 Connection With P3\n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

		Timer timer;

		timer.setTimePoint("Receiver start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;
		// if(locationInBytes==4){
		// 	locationInBytes=3;
		// }
		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		// u8* matrixC[widthBucket1];
		// // u8* matrixC3[widthBucket1];
		// // u8* matrixC1[widthBucket1];
		// u8* matrixC2[widthBucket1];
		// // u8* matrixA1[widthBucket1];
		// // u8* matrixDelta[widthBucket1];
		// for (auto i = 0; i < widthBucket1; ++i) {
		// 	matrixC[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		// 	// matrixC3[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		// 	// matrixC1[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		// 	matrixC2[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
		// }
		u8* matrixC[widthBucket1];
		u8* matrixC2[widthBucket1];
		u8* matrixC1[widthBucket1];
		u8* matrixKey3_1[widthBucket1];
		u8* matrixKey3_2[widthBucket1];
		u8* matrixKey3_4[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixC[i] = new u8[heightInBytes];
			matrixC2[i] = new u8[heightInBytes];
			matrixC1[i] = new u8[heightInBytes];
			matrixKey3_1[i] = new u8[heightInBytes];
			matrixKey3_2[i] = new u8[heightInBytes];
			matrixKey3_4[i] = new u8[heightInBytes];
		}

		
		int fd_c = open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);  
		int fd_c2 = open("/tmp/output_C2.txt", O_RDWR|O_CREAT, 00777);  
		// int fd_c4 = open("/tmp/output_C4.txt", O_RDWR|O_CREAT, 00777); 
		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_c;
		u8* addr_c2;
		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		addr_c2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c2, 0);

		// ------------------------------------------------------------------------------
		// 打开文件
		// int fd_C=open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);
		int fdKey3_1=open("/tmp/outputKey3_1.txt", O_RDWR|O_CREAT, 00777);
		int fdKey3_2=open("/tmp/outputKey3_2.txt", O_RDWR|O_CREAT, 00777);
		int fdKey3_4=open("/tmp/outputKey3_4.txt", O_RDWR|O_CREAT, 00777);
		// u8* addr_C;
		u8* addrKey3_1;
		u8* addrKey3_2;
		u8* addrKey3_4;

		// addr_C = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_C, 0);
		addrKey3_1 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey3_1, 0);
		addrKey3_2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey3_2, 0);
		addrKey3_4 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey3_4, 0);

		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;
			//////////////// Compute matrix A & sent matrix ///////////////////////
			t++;
			for(int k=1;k<widthBucket1+1;k++){
				// memcpy(matrixC[k-1], addr_c+(k-1)*len2+(t-1)*len1, len2);
				// memcpy(matrixC3[k-1], addr_c3+(k-1)*len2+(t-1)*len1, len2);
				// memcpy(matrixC1[k-1], addr_c1+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixC2[k-1], addr_c2+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey3_1[k-1], addrKey3_1+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey3_2[k-1], addrKey3_2+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey3_4[k-1], addrKey3_4+(k-1)*len2+(t-1)*len1, len2);
			}				
			u8* sentMatrix[w];
			// u8* sentMatrix2[w];
			for (auto i = 0; i < w; ++i) {
				sentMatrix[i] = new u8[heightInBytes];
				ch.recv(sentMatrix[i], heightInBytes);
			}
			// cout<<"---------------------------------------------\n";
			// std::cout<<"sentMatrix[0][0] is "<<sentMatrix[0][0]<<"\n";		
			// std::cout<<"matrixC[0][0] is "<<matrixC[0][0]<<"\n";	
			// std::cout<<"sentMatrix[0][10] is "<<sentMatrix[0][10]<<"\n";
			// std::cout<<"matrixC[0][10] is "<<matrixC[0][10]<<"\n";		
			// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
			// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
			// cout<<"---------------------------------------------\n";				
			for (auto i = 0; i < w; ++i) {
				// sentMatrix[i] = new u8[heightInBytes];
				// ch.recv(sentMatrix[i], heightInBytes);
				// sentMatrix[i]^=sentMatrix2[i];
				for (auto j = 0; j < heightInBytes; ++j) {
					// matrixC[i][j] = matrixC3[i][j] ^ matrixC1[i][j] ^ matrixC2[i][j];
					// matrixC2[i][j] ^= sentMatrix[i][j];
					// matrixA[i][j] ^= matrixA1[i][j];
					matrixC[i][j] = sentMatrix[i][j] ^ matrixC2[i][j] ^ matrixKey3_1[i][j] ^ matrixKey3_2[i][j] ^ matrixKey3_4[i][j];
				}
			}
			for(int k=1;k<w+1;k++){
				memcpy(addr_c+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
				// memcpy(addr_c4+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
			}				
		}
		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_c);
		close(fd_c2);
		close(fdKey3_1);
		close(fdKey3_2);
		close(fdKey3_4);
		// close(fd_c3);
		// 解除映射
		munmap(addr_c, len);
		munmap(addr_c2, len);
		munmap(addrKey3_1, len);
		munmap(addrKey3_2, len);
		munmap(addrKey3_4, len);

		timer.setTimePoint("Receiver Hybrid MatrixC");
		std::cout << timer;	
		//////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";

		// memset( SynTime, 0, hashLengthInBytes);
		// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		// ch.recv(SynTime, hashLengthInBytes);
	}

	void PsiReceiver::run_next2(Channel& ch, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"The Process of P3 Connection With P4\n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

		Timer timer;

		timer.setTimePoint("Receiver start");
		
		TimeUnit start, end;
		
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;
		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;

		u8* matrixC[widthBucket1];
		// u8* matrixC1[widthBucket1];
		u8* matrixKey4_1[widthBucket1];
		u8* matrixKey4_2[widthBucket1];
		u8* matrixKey4_3[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixC[i] = new u8[heightInBytes];
			// matrixC1[i] = new u8[heightInBytes];
			matrixKey4_1[i] = new u8[heightInBytes];
			matrixKey4_2[i] = new u8[heightInBytes];
			matrixKey4_3[i] = new u8[heightInBytes];
		}

		int fd_c = open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);  

		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_c;

		addr_c = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_c, 0);
		// 打开文件
		// int fd_C=open("/tmp/output_C.txt", O_RDWR|O_CREAT, 00777);
		int fdKey4_1=open("/tmp/outputKey4_1.txt", O_RDWR|O_CREAT, 00777);
		int fdKey4_2=open("/tmp/outputKey4_2.txt", O_RDWR|O_CREAT, 00777);
		int fdKey4_3=open("/tmp/outputKey4_3.txt", O_RDWR|O_CREAT, 00777);
		// u8* addr_C;
		u8* addrKey4_1;
		u8* addrKey4_2;
		u8* addrKey4_3;

		// addr_C = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_C, 0);
		addrKey4_1 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey4_1, 0);
		addrKey4_2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey4_2, 0);
		addrKey4_3 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey4_3, 0);

		int t=0;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;
			//////////////// Compute matrix A & sent matrix ///////////////////////
			t++;
			for(int k=1;k<widthBucket1+1;k++){
				// memcpy(matrixC1[k-1], addr_c+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey4_1[k-1], addrKey4_1+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey4_2[k-1], addrKey4_2+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey4_3[k-1], addrKey4_3+(k-1)*len2+(t-1)*len1, len2);
			}
			u8* sentMatrix[w];
			// u8* sentMatrix2[w];
			for (auto i = 0; i < w; ++i) {
				sentMatrix[i] = new u8[heightInBytes];
				ch.recv(sentMatrix[i], heightInBytes);
				for (auto j = 0; j < heightInBytes; ++j) {
					matrixC[i][j] = sentMatrix[i][j] ^ matrixKey4_1[i][j] ^ matrixKey4_2[i][j] ^ matrixKey4_3[i][j];
				}
			}	
			for(int k=1;k<w+1;k++){
				memcpy(addr_c+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
				// memcpy(addr_c4+(k-1)*len2+(t-1)*len1, matrixC[k-1], len2);
			}	
		}
		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_c);
		// close(fd_c2);
		close(fdKey4_1);
		close(fdKey4_2);
		close(fdKey4_3);
		// close(fd_c3);
		// 解除映射
		munmap(addr_c, len);
		// munmap(addr_c2, len);
		munmap(addrKey4_1, len);
		munmap(addrKey4_2, len);
		munmap(addrKey4_3, len);

		timer.setTimePoint("Receiver Hybrid MatrixC");
		std::cout << timer;	
		//////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";

		// memset( SynTime, 0, hashLengthInBytes);
		// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		// ch.recv(SynTime, hashLengthInBytes);
	}

	// void PsiReceiver::run_next3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

	// 	cout<<"----------------------------------------------------------------------------------------------------------\n";
	// 	cout<<"----------------------------------------------------------------------------------------------------------\n";
	// 	cout<<"----------------------------------------------------------------------------------------------------------\n";
	// 	std::cout<<"The Process of P4 Connection With P1\n";	
	// 	cout<<"----------------------------------------------------------------------------------------------------------\n";
	// 	cout<<"----------------------------------------------------------------------------------------------------------\n";
	// 	cout<<"----------------------------------------------------------------------------------------------------------\n";
	// 	////////////Syn the Time--------------/////////////
	// 	u8* SynTime = new u8[hashLengthInBytes];		
	// 	memset( SynTime, 0, hashLengthInBytes);
	// 	ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
	// 	ch.recv(SynTime, hashLengthInBytes);

	// 	Timer timer;
		
	// 	timer.setTimePoint("Receiver start");
		
	// 	TimeUnit start, end;
	// 	char *savePath_Receiver = "/tmp/output_R.txt";
	// 	if(remove(savePath_Receiver)==0){
	// 	cout<<"The path is delete successfully\n";
	// 	}
	// 	int i=0;
	// 	// // 写入Matrix D into文件 output_D.txt.
	// 	int lenr = receiverSize*hashLengthInBytes;
	// 	int lenhashBatch=hashLengthInBytes*bucket2;
	// 	// 打开文件
	// 	int fd_r=open("/tmp/output_R.txt", O_RDWR|O_CREAT, 00777);

	// 	u8* addr_r;

	// 	lseek(fd_r,lenr-1,SEEK_END); 
	// 	// lseek(fd_s,lens-1,SEEK_END); 
	// 	// 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子

	// 	write(fd_r, "", 1);
	// 	// write(fd_s, "", 1);
	// 	// 使用mmap函数建立内存映射
	// 	addr_r = (u8*)mmap(NULL, lenr, PROT_READ|PROT_WRITE,MAP_SHARED, fd_r, 0);
	// 	// addr_s = (u8*)mmap(NULL, lens, PROT_READ|PROT_WRITE,MAP_SHARED, fd_s, 0);
	// 	// int t=0;		
	// if(i==0){
	// 	i++;
	// 	auto heightInBytes = (height + 7) / 8;
	// 	auto widthInBytes = (width + 7) / 8;
	// 	auto locationInBytes = (logHeight + 7) / 8;
	// 	// if(locationInBytes==4){
	// 	// 	locationInBytes=3;
	// 	// }
	// 	auto receiverSizeInBytes = (receiverSize + 7) / 8;
	// 	auto shift = (1 << logHeight) - 1;
	// 	auto widthBucket1 = sizeof(block) / locationInBytes;
	// 	int widthdivide=width/widthBucket1+1;
		
		
	// 	///////////////////// Base OTs ///////////////////////////
		

	// 	//////////// Initialization ///////////////////
		
	// 	PRNG commonPrng(commonSeed);
	// 	block commonKey;
	// 	AES commonAes;
		
	// 	u8* matrixA[widthBucket1];
	// 	u8* matrixA1[widthBucket1];
	// 	u8* matrixA2[widthBucket1];
	// 	u8* matrixDelta[widthBucket1];
	// 	u8* matrixKey1_2[widthBucket1];
	// 	u8* matrixKey1_3[widthBucket1];
	// 	u8* matrixKey1_4[widthBucket1];
	// 	for (auto i = 0; i < widthBucket1; ++i) {
	// 		matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
	// 		matrixDelta[i] = new u8[heightInBytes];
	// 		matrixA1[i] = new u8[heightInBytes];
	// 		matrixA2[i] = new u8[heightInBytes];
	// 		matrixKey1_2[i] = new u8[heightInBytes];
	// 		matrixKey1_3[i] = new u8[heightInBytes];
	// 		matrixKey1_4[i] = new u8[heightInBytes];
	// 	}

	// 	u8* transLocations[widthBucket1];// OK
	// 	for (auto i = 0; i < widthBucket1; ++i) {
	// 		transLocations[i] = new u8[receiverSize * locationInBytes + sizeof(u32)];
	// 	}
	
	// 	block randomLocations[bucket1];//The same as sender.
		

	// 	u8* transHashInputs[width];//receiver trans.
	// 	for (auto i = 0; i < width; ++i) {
	// 		transHashInputs[i] = new u8[receiverSizeInBytes];
	// 		memset(transHashInputs[i], 0, receiverSizeInBytes);
	// 	}

	// 	// std::cout << "Receiver initialized\n";
	// 	// timer.setTimePoint("Receiver initialized");

	// 	/////////// Transform input /////////////////////

	// 	commonPrng.get((u8*)&commonKey, sizeof(block));
	// 	commonAes.setKey(commonKey);
		
	// 	block* recvSet = new block[receiverSize];
	// 	block* aesInput = new block[receiverSize];
	// 	block* aesOutput = new block[receiverSize];
		
	// 	RandomOracle H1(h1LengthInBytes);
	// 	u8 h1Output[h1LengthInBytes];
		
	// 	for (auto i = 0; i < receiverSize; ++i) {
	// 		H1.Reset();
	// 		H1.Update((u8*)(receiverSet.data() + i), sizeof(block));
	// 		H1.Final(h1Output);
			
	// 		aesInput[i] = *(block*)h1Output;
	// 		recvSet[i] = *(block*)(h1Output + sizeof(block));
	// 	}
		
	// 	commonAes.ecbEncBlocks(aesInput, receiverSize, aesOutput);
	// 	for (auto i = 0; i < receiverSize; ++i) {
	// 		recvSet[i] ^= aesOutput[i];
	// 	}
		
	// 	// std::cout << "Receiver set transformed\n";
	// 	// timer.setTimePoint("Receiver set transformed");
		
	// 	// cout<<"---------------------------------------------\n";
	// 	// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
	// 	// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
	// 	// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
	// 	// cout<<"recvSet1[0] is "<<recvSet[0];
	// 	// cout<<"---------------------------------------------\n";


	// 	// 打开文件
	// 	// O_RDWR|O_CREAT, 00777
	// 	int fd_a = open("/tmp/output_A.txt", O_RDWR|O_CREAT, 00777);  
	// 	int fd_a1 = open("/tmp/output_A1.txt", O_RDWR|O_CREAT, 00777);  
	// 	int fd_a2 = open("/tmp/output_A2.txt", O_RDWR|O_CREAT, 00777);  
	// 	int fdKey1_2=open("/tmp/outputKey1_2.txt", O_RDWR|O_CREAT, 00777);
	// 	int fdKey1_3=open("/tmp/outputKey1_3.txt", O_RDWR|O_CREAT, 00777);
	// 	int fdKey1_4=open("/tmp/outputKey1_4.txt", O_RDWR|O_CREAT, 00777);
	// 	// 读取文件长度
	// 	int len2 = heightInBytes;
	// 	int len1 = len2*widthBucket1;
	// 	int len = len1*widthdivide;
	// 	u8* addr_a;
	// 	u8* addr_a1;
	// 	u8* addr_a2;
	// 	u8* addrKey1_2;
	// 	u8* addrKey1_3;
	// 	u8* addrKey1_4;

	// 	addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
	// 	addr_a1 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a1, 0);
	// 	addr_a2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a2, 0);
	// 	addrKey1_2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey1_2, 0);
	// 	addrKey1_3 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey1_3, 0);
	// 	addrKey1_4 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey1_4, 0);		
	// 	int t=0;
		
	// 	// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
	// 	for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
	// 		auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
	// 		auto w = wRight - wLeft;

	// 		t++;
	// 		for(int k=1;k<widthBucket1+1;k++){
	// 			memcpy(matrixA[k-1], addr_a+(k-1)*len2+(t-1)*len1, len2);
	// 			memcpy(matrixA1[k-1], addr_a1+(k-1)*len2+(t-1)*len1, len2);
	// 			memcpy(matrixA2[k-1], addr_a2+(k-1)*len2+(t-1)*len1, len2);
	// 			memcpy(matrixKey1_2[k-1], addrKey1_2+(k-1)*len2+(t-1)*len1, len2);
	// 			memcpy(matrixKey1_3[k-1], addrKey1_3+(k-1)*len2+(t-1)*len1, len2);
	// 			memcpy(matrixKey1_4[k-1], addrKey1_4+(k-1)*len2+(t-1)*len1, len2);				
	// 		}
	// 		//////////// Compute random locations (transposed) ////////////////

	// 		commonPrng.get((u8*)&commonKey, sizeof(block));
	// 		commonAes.setKey(commonKey);

	// 		for (auto low = 0; low < receiverSize; low += bucket1) {
			
	// 			auto up = low + bucket1 < receiverSize ? low + bucket1 : receiverSize;
	// 			commonAes.ecbEncBlocks(recvSet + low, up - low, randomLocations); 
					
	// 			for (auto i = 0; i < w; ++i) {
	// 				for (auto j = low; j < up; ++j) {
	// 					memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);
	// 				}
	// 			}
				
	// 		}
		
		
	// 		//////////// Compute matrix Delta /////////////////////////////////
			
	// 		//////////////// Compute matrix Hybrid A///////////////////////
			
	// 		for (auto i = 0; i < w; ++i) {
				
	// 			for (auto j = 0; j < heightInBytes; ++j) {
	// 				matrixA[i][j] ^= matrixA1[i][j] ^ matrixA2[i][j] ^ matrixKey1_2[i][j] ^ matrixKey1_3[i][j] ^ matrixKey1_4[i][j];
	// 			}
	// 		}

	// 		///////////////// Compute hash inputs (transposed) /////////////////////
	
	// 		for (auto i = 0; i < w; ++i) {
	// 			for (auto j = 0; j < receiverSize; ++j) {
	// 				auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					
	// 				transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixA[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
	// 				// if(j%1000000==0){
	// 				// cout<<s<<" counter c2 is"<<++c2<<" \n";
	// 				// }
	// 			}		
	// 		}
			
	// 	}

	// 	// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
	// 	close(fd_a);
	// 	close(fd_a1);
	// 	close(fd_a2);
	// 	// 解除映射
	// 	munmap(addr_a, len);
	// 	munmap(addr_a1, len);
	// 	munmap(addr_a2, len);
	// 	// cout<<"---------------------------------------------\n";
	// 	// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
	// 	// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
	// 	// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
	// 	// cout<<"---------------------------------------------\n";
		
	// 	// timer.setTimePoint("Receiver matrix sent and transposed hash input computed");


	// 	/////////////////// Compute hash outputs ///////////////////////////
		
	// 	RandomOracle H(hashLengthInBytes);
	// 	u8 hashOutput[sizeof(block)];
	// 	std::unordered_map<u64, std::vector<std::pair<block, u32>>> allHashes;
	// 	u8* hashInputs[bucket2];
	// 	for (auto i = 0; i < bucket2; ++i) {
	// 		hashInputs[i] = new u8[widthInBytes];
	// 	}
	// 	int s1=0;
	// 	for (auto low = 0; low < receiverSize; low += bucket2) {
	// 		auto up = low + bucket2 < receiverSize ? low + bucket2 : receiverSize;
	// 		s1++;
	// 		for (auto j = low; j < up; ++j) {
	// 			memset(hashInputs[j - low], 0, widthInBytes);
	// 		}
			
	// 		for (auto i = 0; i < width; ++i) {
	// 			for (auto j = low; j < up; ++j) {
	// 				hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//transform to output of 0|1|0|0|1|...
	// 			}
	// 		}
			
	// 		for (auto j = low; j < up; ++j) {
	// 			H.Reset();
	// 			H.Update(hashInputs[j - low], widthInBytes);
	// 			H.Final(hashOutput);
	// 			memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
	// 			// allHashes[*(u64*)hashOutput].push_back(std::make_pair(*(block*)hashOutput, j));
	// 		}
	// 	}

	// 	// cout<<"---------------------------------------------\n";
	// 	// // receiverSet[0] = (block)hashOutput;
	// 	// // memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
	// 	// // std::cout<<"receiverSet is "<<receiverSet.data()<<"\n";
	// 	// std::cout<<"hashOutput is "<<hashOutput<<"\n";
	// 	// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
	// 	// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
	// 	// cout<<"---------------------------------------------\n";	
		
	// 	// std::cout << "Receiver hash outputs computed\n";
	// 	timer.setTimePoint("Receiver hash outputs FIRST computed!");
	// }	
	// if(i==1){
	// 	auto heightInBytes = (height + 7) / 8;
	// 	auto widthInBytes = (width + 7) / 8;
	// 	auto locationInBytes = (logHeight + 7) / 8;
	// 	// if(locationInBytes==4){
	// 	// 	locationInBytes=3;
	// 	// }
	// 	auto receiverSizeInBytes = (receiverSize + 7) / 8;
	// 	auto shift = (1 << logHeight) - 1;
	// 	auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
	// 	///////////////////// Base OTs ///////////////////////////
		
	// 	IknpOtExtSender otExtSender;
	// 	otExtSender.genBaseOts(prng, ch);
		
	// 	std::vector<std::array<block, 2> > otMessages(width);

	// 	otExtSender.send(otMessages, prng, ch);

	// 	// std::cout << "Receiver base OT finished\n";
	// 	timer.setTimePoint("Receiver base OT finished");
		
		
		
		
	// 	//////////// Initialization ///////////////////
		
	// 	PRNG commonPrng(commonSeed);
	// 	block commonKey;
	// 	AES commonAes;
		
	// 	u8* matrixA[widthBucket1];
	// 	u8* matrixDelta[widthBucket1];
	// 	for (auto i = 0; i < widthBucket1; ++i) {
	// 		matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
	// 		matrixDelta[i] = new u8[heightInBytes];
	// 	}

	// 	u8* transLocations[widthBucket1];// OK
	// 	for (auto i = 0; i < widthBucket1; ++i) {
	// 		transLocations[i] = new u8[receiverSize * locationInBytes + sizeof(u32)];
	// 	}
	
	// 	block randomLocations[bucket1];//The same as sender.
		

	// 	u8* transHashInputs[width];//receiver trans.
	// 	for (auto i = 0; i < width; ++i) {
	// 		transHashInputs[i] = new u8[receiverSizeInBytes];
	// 		memset(transHashInputs[i], 0, receiverSizeInBytes);
	// 	}

	// 	// std::cout << "Receiver initialized\n";
	// 	timer.setTimePoint("Receiver initialized");	


	// 	/////////// Transform input /////////////////////

	// 	commonPrng.get((u8*)&commonKey, sizeof(block));
	// 	commonAes.setKey(commonKey);
		
	// 	block* recvSet = new block[receiverSize];
	// 	block* aesInput = new block[receiverSize];
	// 	block* aesOutput = new block[receiverSize];
		
	// 	RandomOracle H1(h1LengthInBytes);
	// 	u8 h1Output[h1LengthInBytes];

	// 	u8 h1Output_Copy[h1LengthInBytes];

	// 	for (auto i = 0; i < receiverSize; ++i) {
	// 		H1.Reset();
	// 		memcpy(h1Output_Copy, addr_r+i*hashLengthInBytes, hashLengthInBytes);
	// 		H1.Update(h1Output_Copy, hashLengthInBytes);
	// 		// H1.Update((u8*)(receiverSet.data() + i), sizeof(block));
	// 		H1.Final(h1Output);
			
	// 		aesInput[i] = *(block*)h1Output;
	// 		recvSet[i] = *(block*)(h1Output + sizeof(block));
	// 	}
		
	// 	commonAes.ecbEncBlocks(aesInput, receiverSize, aesOutput);
	// 	for (auto i = 0; i < receiverSize; ++i) {
	// 		recvSet[i] ^= aesOutput[i];
	// 	}
		
	// 	// std::cout << "Receiver set transformed\n";
	// 	timer.setTimePoint("Receiver set transformed");
		
	// 	// cout<<"---------------------------------------------\n";
	// 	// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
	// 	// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
	// 	// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
	// 	// cout<<"recvSet1[0] is "<<recvSet[0];
	// 	// cout<<"---------------------------------------------\n";

		
	// 	int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
	// 	for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
	// 		auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
	// 		auto w = wRight - wLeft;

	// 		s++;
	// 		//////////// Compute random locations (transposed) ////////////////
	// 		// if(s%1000==0)
	// 		// cout<<s<<" counter s is"<<s<<" \n";
	// 		commonPrng.get((u8*)&commonKey, sizeof(block));
	// 		commonAes.setKey(commonKey);

	// 		for (auto low = 0; low < receiverSize; low += bucket1) {
			
	// 			auto up = low + bucket1 < receiverSize ? low + bucket1 : receiverSize;
	// 			commonAes.ecbEncBlocks(recvSet + low, up - low, randomLocations); 
					
	// 			for (auto i = 0; i < w; ++i) {
	// 				for (auto j = low; j < up; ++j) {
	// 					memcpy(transLocations[i] + j * locationInBytes, (u8*)(randomLocations + (j - low)) + i * locationInBytes, locationInBytes);
	// 				}
	// 			}
				
	// 		}
		
		

	// 		//////////// Compute matrix Delta /////////////////////////////////
			
	// 		for (auto i = 0; i < widthBucket1; ++i) {
	// 			memset(matrixDelta[i], 255, heightInBytes);
	// 		}
			
	// 		for (auto i = 0; i < w; ++i) {
	// 			for (auto j = 0; j < receiverSize; ++j) {
	// 				auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;//location means the truly location in present of 2-bits.
					
	// 				matrixDelta[i][location >> 3] &= ~(1 << (location & 7));//matrix[i][j]={0-255},location & 7 means the truly changed location between{0-255} 
	// 				// if(j%1000000==0){
	// 				// cout<<s<<" counter c1 is"<<++c1<<" \n";
	// 				// }
	// 			}
	// 		}
			
			
			
	// 		//////////////// Compute matrix A & sent matrix ///////////////////////

	// 		u8* sentMatrix[w];
			
	// 		for (auto i = 0; i < w; ++i) {
	// 			PRNG prng(otMessages[i + wLeft][0]);
	// 			prng.get(matrixA[i], heightInBytes);
				
	// 			sentMatrix[i] = new u8[heightInBytes];
	// 			prng.SetSeed(otMessages[i + wLeft][1]);
	// 			prng.get(sentMatrix[i], heightInBytes);
				
	// 			for (auto j = 0; j < heightInBytes; ++j) {
	// 				sentMatrix[i][j] ^= matrixA[i][j] ^ matrixDelta[i][j];//A^D^r1
	// 			}
				
	// 			ch.asyncSend(sentMatrix[i], heightInBytes);
	// 		}
			
			
			
	// 		///////////////// Compute hash inputs (transposed) /////////////////////
	
	// 		for (auto i = 0; i < w; ++i) {
	// 			for (auto j = 0; j < receiverSize; ++j) {
	// 				auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					
	// 				transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixA[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
	// 				// if(j%1000000==0){
	// 				// cout<<s<<" counter c2 is"<<++c2<<" \n";
	// 				// }
	// 			}		
	// 		}
			
	// 	}

	// 	// cout<<"---------------------------------------------\n";
	// 	// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
	// 	// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
	// 	// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
	// 	// cout<<"---------------------------------------------\n";
		
	// 	// std::cout << "Receiver matrix sent and transposed hash input computed\n";
	// 	timer.setTimePoint("Receiver matrix sent and transposed hash input computed");

	// 	// // // 写入Matrix D into文件 output_D.txt.
	// 	// int lenr = receiverSize*hashLengthInBytes;
	// 	// int lenhashBatch=hashLengthInBytes*bucket2;
	// 	// // 打开文件
	// 	// int fd_r=open("/tmp/output_R.txt", O_RDWR|O_CREAT, 00777);

	// 	// u8* addr_r;

	// 	// lseek(fd_r,lenr-1,SEEK_END); 
	// 	// // lseek(fd_s,lens-1,SEEK_END); 
	// 	// // 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子

	// 	// write(fd_r, "", 1);
	// 	// // write(fd_s, "", 1);
	// 	// // 使用mmap函数建立内存映射
	// 	// addr_r = (u8*)mmap(NULL, lenr, PROT_READ|PROT_WRITE,MAP_SHARED, fd_r, 0);
	// 	// // addr_s = (u8*)mmap(NULL, lens, PROT_READ|PROT_WRITE,MAP_SHARED, fd_s, 0);
	// 	// // int t=0;		
		
	// 	/////////////////// Compute hash outputs ///////////////////////////
		
	// 	RandomOracle H(hashLengthInBytes);
	// 	u8 hashOutput[sizeof(block)];
	// 	std::unordered_map<u64, std::vector<std::pair<block, u32>>> allHashes;
	// 	u8* hashInputs[bucket2];
	// 	for (auto i = 0; i < bucket2; ++i) {
	// 		hashInputs[i] = new u8[widthInBytes];
	// 	}
	// 	int s1=0;
	// 	for (auto low = 0; low < receiverSize; low += bucket2) {
	// 		auto up = low + bucket2 < receiverSize ? low + bucket2 : receiverSize;
	// 		s1++;
	// 		for (auto j = low; j < up; ++j) {
	// 			memset(hashInputs[j - low], 0, widthInBytes);
	// 		}
			
	// 		for (auto i = 0; i < width; ++i) {
	// 			for (auto j = low; j < up; ++j) {
	// 				hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//transform to output of 0|1|0|0|1|...
	// 			}
	// 		}
			
	// 		for (auto j = low; j < up; ++j) {
	// 			H.Reset();
	// 			H.Update(hashInputs[j - low], widthInBytes);
	// 			H.Final(hashOutput);
	// 			// memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
	// 			allHashes[*(u64*)hashOutput].push_back(std::make_pair(*(block*)hashOutput, j));
	// 		}
	// 	}
		
	// 	// // std::cout << "Receiver hash outputs computed\n";
	// 	// timer.setTimePoint("Receiver hash outputs computed");
	// 	// cout<<"---------------------------------------------\n";
	// 	// // receiverSet[0] = (block)hashOutput;
	// 	// // memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
	// 	// // std::cout<<"receiverSet is "<<receiverSet.data()<<"\n";
	// 	// std::cout<<"hashOutput is "<<hashOutput<<"\n";
	// 	// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
	// 	// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
	// 	// cout<<"---------------------------------------------\n";			
	
	
		
	// 	///////////////// Receive hash outputs from sender and compute PSI ///////////////////

	// 	u8* recvBuff = new u8[bucket2 * hashLengthInBytes];//output0001|1111|1010|... to 01010101010101010
		
	// 	auto psi = 0;
		
	// 	for (auto low = 0; low < senderSize; low += bucket2) {
	// 		auto up = low + bucket2 < senderSize ? low + bucket2 : senderSize;
			
	// 		ch.recv(recvBuff, (up - low) * hashLengthInBytes);
			
	// 		for (auto idx = 0; idx < up - low; ++idx) {
	// 			u64 mapIdx = *(u64*)(recvBuff + idx * hashLengthInBytes);
				
	// 			auto found = allHashes.find(mapIdx);
	// 			if (found == allHashes.end()) continue;
				
	// 			for (auto i = 0; i < found->second.size(); ++i) {
	// 				if (memcmp(&(found->second[i].first), recvBuff + idx * hashLengthInBytes, hashLengthInBytes) == 0) {
	// 					++psi;
	// 					break;
	// 				}
	// 			}
	// 		}
	// 	}
		
	// 	// if (psi == 100) {
	// 	// 	std::cout << "Receiver intersection computed - correct!\n";
	// 	// }
	// 	// else{
	// 	std::cout << "Receiver intersection computed"<< psi <<"- correct!\n";
	// 	// }
	// 	timer.setTimePoint("Receiver intersection computed");
	// }	
	// 	close(fd_r);
	// 	// 解除映射
	// 	munmap(addr_r, lenr);		
	// 	std::cout << timer;
		
	// 	//////////////// Output communication /////////////////
	
	// 	u64 sentData = ch.getTotalDataSent();
	// 	u64 recvData = ch.getTotalDataRecv();
	// 	u64 totalData = sentData + recvData;
		
	// 	std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
	// 	std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
	// 	std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";
			
	// 	// memset( SynTime, 0, hashLengthInBytes);
	// 	// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
	// 	// ch.recv(SynTime, hashLengthInBytes);		
	// }

	void PsiReceiver::run_next3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& height1, const u64& logHeight1, const u64& width, const u64& width1, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2) {

		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		std::cout<<"The Process of P4 Connection With P1\n";	
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		cout<<"----------------------------------------------------------------------------------------------------------\n";
		////////////Syn the Time--------------/////////////
		u8* SynTime = new u8[hashLengthInBytes];		
		memset( SynTime, 0, hashLengthInBytes);
		ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		ch.recv(SynTime, hashLengthInBytes);

		Timer timer;
		
		timer.setTimePoint("Receiver start");
		
		TimeUnit start, end;
		char *savePath_Receiver = "/tmp/output_R.txt";
		if(remove(savePath_Receiver)==0){
		cout<<"The path is delete successfully\n";
		}
		int i=0;
		// // 写入Matrix D into文件 output_D.txt.
		int lenr = receiverSize*hashLengthInBytes;
		int lenhashBatch=hashLengthInBytes*bucket2;
		// 打开文件
		int fd_r=open("/tmp/output_R.txt", O_RDWR|O_CREAT, 00777);

		u8* addr_r;

		lseek(fd_r,lenr-1,SEEK_END); 
		// lseek(fd_s,lens-1,SEEK_END); 
		// 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子

		write(fd_r, "", 1);
		// write(fd_s, "", 1);
		// 使用mmap函数建立内存映射
		addr_r = (u8*)mmap(NULL, lenr, PROT_READ|PROT_WRITE,MAP_SHARED, fd_r, 0);
		// addr_s = (u8*)mmap(NULL, lens, PROT_READ|PROT_WRITE,MAP_SHARED, fd_s, 0);
		// int t=0;		
	if(i==0){
		i++;
		auto heightInBytes = (height + 7) / 8;
		auto widthInBytes = (width + 7) / 8;
		auto locationInBytes = (logHeight + 7) / 8;
		// if(locationInBytes==4){
		// 	locationInBytes=3;
		// }
		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;
		int widthdivide=width/widthBucket1+1;
		
		
		///////////////////// Base OTs ///////////////////////////
		

		//////////// Initialization ///////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* matrixA[widthBucket1];
		u8* matrixA1[widthBucket1];
		u8* matrixA2[widthBucket1];
		u8* matrixDelta[widthBucket1];
		u8* matrixKey1_2[widthBucket1];
		u8* matrixKey1_3[widthBucket1];
		u8* matrixKey1_4[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixDelta[i] = new u8[heightInBytes];
			matrixA1[i] = new u8[heightInBytes];
			matrixA2[i] = new u8[heightInBytes];
			matrixKey1_2[i] = new u8[heightInBytes];
			matrixKey1_3[i] = new u8[heightInBytes];
			matrixKey1_4[i] = new u8[heightInBytes];
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
		// timer.setTimePoint("Receiver initialized");

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
			H1.Update((u8*)(receiverSet.data() + i), sizeof(block));
			H1.Final(h1Output);
			
			aesInput[i] = *(block*)h1Output;
			recvSet[i] = *(block*)(h1Output + sizeof(block));
		}
		
		commonAes.ecbEncBlocks(aesInput, receiverSize, aesOutput);
		for (auto i = 0; i < receiverSize; ++i) {
			recvSet[i] ^= aesOutput[i];
		}
		
		// std::cout << "Receiver set transformed\n";
		// timer.setTimePoint("Receiver set transformed");
		
		// cout<<"---------------------------------------------\n";
		// cout<<"h1Output[0] is "<<h1Output[0]<<"\n";
		// cout<<"aesInput1[0] is "<<aesInput[0]<<"\n";
		// cout<<"aesOutput1[0] is "<<aesOutput[0]<<"\n";
		// cout<<"recvSet1[0] is "<<recvSet[0];
		// cout<<"---------------------------------------------\n";


		// 打开文件
		// O_RDWR|O_CREAT, 00777
		int fd_a = open("/tmp/output_A.txt", O_RDWR|O_CREAT, 00777);  
		int fd_a1 = open("/tmp/output_A1.txt", O_RDWR|O_CREAT, 00777);  
		int fd_a2 = open("/tmp/output_A2.txt", O_RDWR|O_CREAT, 00777);  
		int fdKey1_2=open("/tmp/outputKey1_2.txt", O_RDWR|O_CREAT, 00777);
		int fdKey1_3=open("/tmp/outputKey1_3.txt", O_RDWR|O_CREAT, 00777);
		int fdKey1_4=open("/tmp/outputKey1_4.txt", O_RDWR|O_CREAT, 00777);
		// 读取文件长度
		int len2 = heightInBytes;
		int len1 = len2*widthBucket1;
		int len = len1*widthdivide;
		u8* addr_a;
		u8* addr_a1;
		u8* addr_a2;
		u8* addrKey1_2;
		u8* addrKey1_3;
		u8* addrKey1_4;

		addr_a = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a, 0);
		addr_a1 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a1, 0);
		addr_a2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fd_a2, 0);
		addrKey1_2 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey1_2, 0);
		addrKey1_3 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey1_3, 0);
		addrKey1_4 = (u8*)mmap(NULL, len, PROT_READ|PROT_WRITE,MAP_SHARED, fdKey1_4, 0);		
		int t=0;
		
		// int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		for (auto wLeft = 0; wLeft < width; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width ? wLeft + widthBucket1 : width;
			auto w = wRight - wLeft;

			t++;
			for(int k=1;k<widthBucket1+1;k++){
				memcpy(matrixA[k-1], addr_a+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixA1[k-1], addr_a1+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixA2[k-1], addr_a2+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey1_2[k-1], addrKey1_2+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey1_3[k-1], addrKey1_3+(k-1)*len2+(t-1)*len1, len2);
				memcpy(matrixKey1_4[k-1], addrKey1_4+(k-1)*len2+(t-1)*len1, len2);				
			}
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
			
			//////////////// Compute matrix Hybrid A///////////////////////
			
			for (auto i = 0; i < w; ++i) {
				
				for (auto j = 0; j < heightInBytes; ++j) {
					matrixA[i][j] ^= matrixA1[i][j] ^ matrixA2[i][j] ^ matrixKey1_2[i][j] ^ matrixKey1_3[i][j] ^ matrixKey1_4[i][j];
				}
			}

			///////////////// Compute hash inputs (transposed) /////////////////////
	
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < receiverSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					
					transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixA[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
					// if(j%1000000==0){
					// cout<<s<<" counter c2 is"<<++c2<<" \n";
					// }
				}		
			}
			
		}

		// 内存映射建立好了，此时可以关闭文件了,Put This Process into Final.
		close(fd_a);
		close(fd_a1);
		close(fd_a2);
		// 解除映射
		munmap(addr_a, len);
		munmap(addr_a1, len);
		munmap(addr_a2, len);
		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		
		// timer.setTimePoint("Receiver matrix sent and transposed hash input computed");


		/////////////////// Compute hash outputs ///////////////////////////
		
		RandomOracle H(hashLengthInBytes);
		u8 hashOutput[sizeof(block)];
		std::unordered_map<u64, std::vector<std::pair<block, u32>>> allHashes;
		u8* hashInputs[bucket2];
		for (auto i = 0; i < bucket2; ++i) {
			hashInputs[i] = new u8[widthInBytes];
		}
		int s1=0;
		for (auto low = 0; low < receiverSize; low += bucket2) {
			auto up = low + bucket2 < receiverSize ? low + bucket2 : receiverSize;
			s1++;
			for (auto j = low; j < up; ++j) {
				memset(hashInputs[j - low], 0, widthInBytes);
			}
			
			for (auto i = 0; i < width; ++i) {
				for (auto j = low; j < up; ++j) {
					hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//transform to output of 0|1|0|0|1|...
				}
			}
			
			for (auto j = low; j < up; ++j) {
				H.Reset();
				H.Update(hashInputs[j - low], widthInBytes);
				H.Final(hashOutput);
				memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
				// allHashes[*(u64*)hashOutput].push_back(std::make_pair(*(block*)hashOutput, j));
			}
		}

		// cout<<"---------------------------------------------\n";
		// // receiverSet[0] = (block)hashOutput;
		// // memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
		// // std::cout<<"receiverSet is "<<receiverSet.data()<<"\n";
		// std::cout<<"hashOutput is "<<hashOutput<<"\n";
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";	
		
		// std::cout << "Receiver hash outputs computed\n";
		timer.setTimePoint("Receiver hash outputs FIRST computed!");
	}	
	if(i==1){
		auto heightInBytes = (height1 + 7) / 8;
		auto widthInBytes = (width1 + 7) / 8;
		auto locationInBytes = (logHeight1 + 7) / 8;
		// if(locationInBytes==4){
		// 	locationInBytes=3;
		// }
		auto receiverSizeInBytes = (receiverSize + 7) / 8;
		auto shift = (1 << logHeight1) - 1;
		auto widthBucket1 = sizeof(block) / locationInBytes;
		
		
		///////////////////// Base OTs ///////////////////////////
		
		IknpOtExtSender otExtSender;
		otExtSender.genBaseOts(prng, ch);
		
		std::vector<std::array<block, 2> > otMessages(width1);

		otExtSender.send(otMessages, prng, ch);

		// std::cout << "Receiver base OT finished\n";
		timer.setTimePoint("Receiver base OT finished");
		
		
		
		
		//////////// Initialization ///////////////////
		
		PRNG commonPrng(commonSeed);
		block commonKey;
		AES commonAes;
		
		u8* matrixA[widthBucket1];
		u8* matrixDelta[widthBucket1];
		for (auto i = 0; i < widthBucket1; ++i) {
			matrixA[i] = new u8[heightInBytes];//every have the number of heightbyte figures.
			matrixDelta[i] = new u8[heightInBytes];
		}

		u8* transLocations[widthBucket1];// OK
		for (auto i = 0; i < widthBucket1; ++i) {
			transLocations[i] = new u8[receiverSize * locationInBytes + sizeof(u32)];
		}
	
		block randomLocations[bucket1];//The same as sender.
		

		u8* transHashInputs[width1];//receiver trans.
		for (auto i = 0; i < width1; ++i) {
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

		u8 h1Output_Copy[h1LengthInBytes];

		for (auto i = 0; i < receiverSize; ++i) {
			H1.Reset();
			memcpy(h1Output_Copy, addr_r+i*hashLengthInBytes, hashLengthInBytes);
			H1.Update(h1Output_Copy, hashLengthInBytes);
			// H1.Update((u8*)(receiverSet.data() + i), sizeof(block));
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

		
		int c=0;int c1=0;int c2=0;int c3=0;int s=-1;
		for (auto wLeft = 0; wLeft < width1; wLeft += widthBucket1) {
			auto wRight = wLeft + widthBucket1 < width1 ? wLeft + widthBucket1 : width1;
			auto w = wRight - wLeft;

			s++;
			//////////// Compute random locations (transposed) ////////////////
			// if(s%1000==0)
			// cout<<s<<" counter s is"<<s<<" \n";
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

			u8* sentMatrix[w];
			
			for (auto i = 0; i < w; ++i) {
				PRNG prng(otMessages[i + wLeft][0]);
				prng.get(matrixA[i], heightInBytes);
				
				sentMatrix[i] = new u8[heightInBytes];
				prng.SetSeed(otMessages[i + wLeft][1]);
				prng.get(sentMatrix[i], heightInBytes);
				
				for (auto j = 0; j < heightInBytes; ++j) {
					sentMatrix[i][j] ^= matrixA[i][j] ^ matrixDelta[i][j];//A^D^r1
				}
				
				ch.asyncSend(sentMatrix[i], heightInBytes);
			}
			
			
			
			///////////////// Compute hash inputs (transposed) /////////////////////
	
			for (auto i = 0; i < w; ++i) {
				for (auto j = 0; j < receiverSize; ++j) {
					auto location = (*(u32*)(transLocations[i] + j * locationInBytes)) & shift;
					
					transHashInputs[i + wLeft][j >> 3] |= (u8)((bool)(matrixA[i][location >> 3] & (1 << (location & 7)))) << (j & 7);
					// if(j%1000000==0){
					// cout<<s<<" counter c2 is"<<++c2<<" \n";
					// }
				}		
			}
			
		}

		// cout<<"---------------------------------------------\n";
		// std::cout<<"transHashInputs[0][0] is "<<int(transHashInputs[0][0])<<"\n";
		// std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";
		
		// std::cout << "Receiver matrix sent and transposed hash input computed\n";
		timer.setTimePoint("Receiver matrix sent and transposed hash input computed");

		// // // 写入Matrix D into文件 output_D.txt.
		// int lenr = receiverSize*hashLengthInBytes;
		// int lenhashBatch=hashLengthInBytes*bucket2;
		// // 打开文件
		// int fd_r=open("/tmp/output_R.txt", O_RDWR|O_CREAT, 00777);

		// u8* addr_r;

		// lseek(fd_r,lenr-1,SEEK_END); 
		// // lseek(fd_s,lens-1,SEEK_END); 
		// // 从指针处写入一个空字符；mmap不能扩展文件长度，这里相当于预先给文件长度，准备一个空架子

		// write(fd_r, "", 1);
		// // write(fd_s, "", 1);
		// // 使用mmap函数建立内存映射
		// addr_r = (u8*)mmap(NULL, lenr, PROT_READ|PROT_WRITE,MAP_SHARED, fd_r, 0);
		// // addr_s = (u8*)mmap(NULL, lens, PROT_READ|PROT_WRITE,MAP_SHARED, fd_s, 0);
		// // int t=0;		
		
		/////////////////// Compute hash outputs ///////////////////////////
		
		RandomOracle H(hashLengthInBytes);
		u8 hashOutput[sizeof(block)];
		std::unordered_map<u64, std::vector<std::pair<block, u32>>> allHashes;
		u8* hashInputs[bucket2];
		for (auto i = 0; i < bucket2; ++i) {
			hashInputs[i] = new u8[widthInBytes];
		}
		int s1=0;
		for (auto low = 0; low < receiverSize; low += bucket2) {
			auto up = low + bucket2 < receiverSize ? low + bucket2 : receiverSize;
			s1++;
			for (auto j = low; j < up; ++j) {
				memset(hashInputs[j - low], 0, widthInBytes);
			}
			
			for (auto i = 0; i < width1; ++i) {
				for (auto j = low; j < up; ++j) {
					hashInputs[j - low][i >> 3] |= (u8)((bool)(transHashInputs[i][j >> 3] & (1 << (j & 7)))) << (i & 7);//transform to output of 0|1|0|0|1|...
				}
			}
			
			for (auto j = low; j < up; ++j) {
				H.Reset();
				H.Update(hashInputs[j - low], widthInBytes);
				H.Final(hashOutput);
				// memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
				allHashes[*(u64*)hashOutput].push_back(std::make_pair(*(block*)hashOutput, j));
			}
		}
		
		// // std::cout << "Receiver hash outputs computed\n";
		// timer.setTimePoint("Receiver hash outputs computed");
		// cout<<"---------------------------------------------\n";
		// // receiverSet[0] = (block)hashOutput;
		// // memcpy(addr_r+(j-low)*hashLengthInBytes+(s1-1)*lenhashBatch, hashOutput, hashLengthInBytes);
		// // std::cout<<"receiverSet is "<<receiverSet.data()<<"\n";
		// std::cout<<"hashOutput is "<<hashOutput<<"\n";
		// // std::cout<<"transHashInputs[1][0] is "<<int(transHashInputs[1][0])<<"\n";
		// // std::cout<<"transHashInputs[2][0] is "<<int(transHashInputs[2][0])<<"\n";
		// cout<<"---------------------------------------------\n";			
	
	
		
		///////////////// Receive hash outputs from sender and compute PSI ///////////////////

		u8* recvBuff = new u8[bucket2 * hashLengthInBytes];//output0001|1111|1010|... to 01010101010101010
		
		auto psi = 0;
		
		for (auto low = 0; low < senderSize; low += bucket2) {
			auto up = low + bucket2 < senderSize ? low + bucket2 : senderSize;
			
			ch.recv(recvBuff, (up - low) * hashLengthInBytes);
			
			for (auto idx = 0; idx < up - low; ++idx) {
				u64 mapIdx = *(u64*)(recvBuff + idx * hashLengthInBytes);
				
				auto found = allHashes.find(mapIdx);
				if (found == allHashes.end()) continue;
				
				for (auto i = 0; i < found->second.size(); ++i) {
					if (memcmp(&(found->second[i].first), recvBuff + idx * hashLengthInBytes, hashLengthInBytes) == 0) {
						++psi;
						break;
					}
				}
			}
		}
		
		// if (psi == 100) {
		// 	std::cout << "Receiver intersection computed - correct!\n";
		// }
		// else{
		std::cout << "Receiver intersection computed"<< psi <<"- correct!\n";
		// }
		timer.setTimePoint("Receiver intersection computed");
	}	
		close(fd_r);
		// 解除映射
		munmap(addr_r, lenr);		
		std::cout << timer;
		
		//////////////// Output communication /////////////////
	
		u64 sentData = ch.getTotalDataSent();
		u64 recvData = ch.getTotalDataRecv();
		u64 totalData = sentData + recvData;
		
		std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";
			
		// memset( SynTime, 0, hashLengthInBytes);
		// ch.asyncSend(SynTime, hashLengthInBytes);//yipiyipi send to receiver.
		// ch.recv(SynTime, hashLengthInBytes);		
	}

// // ----------------Copy----------------Restore---------------

}
