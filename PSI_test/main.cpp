#include "PSI/include/Defines.h"
#include "PSI/include/utils.h"
#include "PSI/include/PsiSender.h"
#include "PSI/include/PsiReceiver.h"

#include <cryptoTools/Network/IOService.h>
#include <cryptoTools/Network/Endpoint.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Common/CLP.h>
#include <cryptoTools/Common/Log.h>

#include <vector>

using namespace std;
using namespace PSI;

const block commonSeed = oc::toBlock(123456);

u64 senderSize;
u64 receiverSize;
u64 width;
u64 width1;
u64 height;
u64 logHeight;
u64 height1;
u64 logHeight1;
u64 hashLengthInBytes;
u64 bucket, bucket1, bucket2;
string ip;


void runSenderKey1_2() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(12));//means a random feed in "123".
	// for (auto i = 0; i < senderSize; ++i) {
	// 	senderSet[i] = prng.get<block>();
	// }
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.runKey1_2(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSenderKey1_3() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(13));//means a random feed in "123".
	// for (auto i = 0; i < senderSize; ++i) {
	// 	senderSet[i] = prng.get<block>();
	// }
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.runKey1_3(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSenderKey1_4() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(14));//means a random feed in "123".
	// for (auto i = 0; i < senderSize; ++i) {
	// 	senderSet[i] = prng.get<block>();
	// }
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.runKey1_4(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSenderKey2_3() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(23));//means a random feed in "123".
	// for (auto i = 0; i < senderSize; ++i) {
	// 	senderSet[i] = prng.get<block>();
	// }
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.runKey2_3(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSenderKey2_4() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(24));//means a random feed in "123".
	// for (auto i = 0; i < senderSize; ++i) {
	// 	senderSet[i] = prng.get<block>();
	// }
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.runKey2_4(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSenderKey3_4() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(34));//means a random feed in "123".
	// for (auto i = 0; i < senderSize; ++i) {
	// 	senderSet[i] = prng.get<block>();
	// }
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.runKey3_4(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}


void runSender() {
	// First time to connect P2
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(123));//means a random feed in "123".
	for (auto i = 0; i < 1000; ++i) {
		senderSet[i] = prng.get<block>();
	}
	// PRNG prng1(oc::toBlock(124));//means a random feed in "123".
	// for (auto i = 100; i < 200; ++i) {
	// 	senderSet[i] = prng1.get<block>();
	// }
	PRNG prng2(oc::toBlock(345));//means a random feed in "123".
	for (auto i = 1000; i < senderSize; ++i) {
		senderSet[i] = prng2.get<block>();
	}		
	PsiSender psiSender;
	psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	// psiSender.run(prng2, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}
// generate A and C P1 false
void runSenderOffline_next0() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(123));//means a random feed in "123".
	for (auto i = 0; i < 1000; ++i) {
		senderSet[i] = prng.get<block>();
	}
	PRNG prng1(oc::toBlock(124));//means a random feed in "123".
	for (auto i = 1000; i < 2000; ++i) {
		senderSet[i] = prng1.get<block>();
	}
	PRNG prng2(oc::toBlock(111));//means a random feed in "123".
	for (auto i = 2000; i < 3000; ++i) {
		senderSet[i] = prng2.get<block>();
	}	
	PRNG prng3(oc::toBlock(555));//means a random feed in "123".
	for (auto i = 3000; i < senderSize; ++i) {
		senderSet[i] = prng3.get<block>();
	}		
	PsiSender psiSender;
	psiSender.runOffline_next0(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	// psiSender.run(prng2, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSenderOffline_next1() {
	// First time to connect P3
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();
// This is no sense.
	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(123));//means a random feed in "123".
	for (auto i = 0; i < 1000; ++i) {
		senderSet[i] = prng.get<block>();
	}
	PRNG prng1(oc::toBlock(124));//means a random feed in "123".
	for (auto i = 1000; i < 2000; ++i) {
		senderSet[i] = prng1.get<block>();
	}
	PRNG prng2(oc::toBlock(567));//means a random feed in "123".
	for (auto i = 2000; i < senderSize; ++i) {
		senderSet[i] = prng2.get<block>();
	}
	PsiSender psiSender;
	psiSender.runOffline_next1(prng2, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	// psiSender.run_next1(prng2, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}


void runSender_next1() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();
// This is no sense.
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.run_next1(ch, senderSize, height, logHeight, width, hashLengthInBytes);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSender_next2() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();
	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.run_next2(ch, senderSize, height, logHeight, width, hashLengthInBytes);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runSender_next3() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(123));//means a random feed in "123".
	for (auto i = 0; i < 1000; ++i) {
		senderSet[i] = prng.get<block>();
	}
	PRNG prng1(oc::toBlock(124));//means a random feed in "123".
	for (auto i = 1000; i < 2000; ++i) {
		senderSet[i] = prng1.get<block>();
	}
	PRNG prng2(oc::toBlock(125));//means a random feed in "123".
	for (auto i = 2000; i < 3000; ++i) {
		senderSet[i] = prng2.get<block>();
	}
	PRNG prng3(oc::toBlock(777));//means a random feed in "123".
	for (auto i = 3000; i < senderSize; ++i) {
		senderSet[i] = prng3.get<block>();
	}	
	PsiSender psiSender;
	// psiSender.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	// psiSender.run_next3(prng3, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiSender.run_next3(prng3, ch, commonSeed, senderSize, receiverSize, height, logHeight, height1, logHeight1, width, width1, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}


void runReceiverKey2_1() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(21));//means a random feed in "123".

	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.runKey2_1(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverKey3_1() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(31));//means a random feed in "123".

	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.runKey3_1(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverKey4_1() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(41));//means a random feed in "123".

	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.runKey4_1(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverKey3_2() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(32));//means a random feed in "123".

	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.runKey3_2(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverKey4_2() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(42));//means a random feed in "123".

	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.runKey4_2(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverKey4_3() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(43));//means a random feed in "123".

	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.runKey4_3(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}


void runReceiver() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	// vector<block> receiverSet(receiverSize); 	
	PRNG prng3(oc::toBlock(456));//means a random feed in "456".
	
	PsiReceiver psiReceiver;
	psiReceiver.runOffline(prng3, ch, senderSize, receiverSize, height, logHeight, width, hashLengthInBytes);
	// psiReceiver.run(prng2, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverOffline_next0() {
	// First time to connect P1 true
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	PRNG prng3(oc::toBlock(5559));//means a random feed in "456".
	
	PsiReceiver psiReceiver;
	psiReceiver.runOffline_next0(prng3, ch, senderSize, receiverSize, height, logHeight, width, hashLengthInBytes);
	// psiReceiver.run(prng2, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiverOffline_next1() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();
// This is no sense.
	PRNG prng2(oc::toBlock(456));//means a random feed in "456".
	
	PsiReceiver psiReceiver;
	psiReceiver.runOffline_next1(prng2, ch, senderSize, receiverSize, height, logHeight, width, hashLengthInBytes);
	// psiReceiver.run(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiver_next1() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();
// This is no sense.
	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.run_next1(ch, receiverSize, height, logHeight, width, hashLengthInBytes);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiver_next2() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();
	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	psiReceiver.run_next2(ch, receiverSize, height, logHeight, width, hashLengthInBytes);
	
	ch.close();
	ep.stop();
	ios.stop();
}


void runReceiver_next3() {
	// First time to connect
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(123));//means a random feed in "123".
	for (auto i = 0; i < 1000; ++i) {
		receiverSet[i] = prng.get<block>();
	}
	PRNG prng1(oc::toBlock(124));//means a random feed in "123".
	for (auto i = 1000; i < 2000; ++i) {
		receiverSet[i] = prng1.get<block>();
	}	
	PRNG prng2(oc::toBlock(111));//means a random feed in "123".
	for (auto i = 2000; i < 3000; ++i) {
		receiverSet[i] = prng2.get<block>();
	}	
	PRNG prng3(oc::toBlock(555));//means a random feed in "456".
	for (auto i = 3000; i < receiverSize; ++i) {
		receiverSet[i] = prng3.get<block>();
	}
	
	PsiReceiver psiReceiver;
	// psiReceiver.runOffline(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	// psiReceiver.run_next3(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);	
	psiReceiver.run_next3(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, height1, logHeight1, width, width1, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}


int main(int argc, char** argv) {
	
	cout<<"That is OK";

	oc::CLP cmd;
	cmd.parse(argc, argv);
	
	cmd.setDefault("ss", 20);
	senderSize = 1 << cmd.get<u64>("ss");
	
	cmd.setDefault("rs", 20);
	receiverSize = 1 << cmd.get<u64>("rs");
	
	cmd.setDefault("w", 300);
	width = cmd.get<u64>("w");
	
	cmd.setDefault("w1", 621);
	width1 = cmd.get<u64>("w1");

	cmd.setDefault("h", 20);
	logHeight = cmd.get<u64>("h");
	height = 1 << cmd.get<u64>("h");

	cmd.setDefault("h1", 20);
	logHeight1 = cmd.get<u64>("h1");
	height1 = 1 << cmd.get<u64>("h1");

	cmd.setDefault("hash", 10);
	hashLengthInBytes = cmd.get<u64>("hash");
	
	cmd.setDefault("ip", "localhost");
	ip = cmd.get<string>("ip");
	
	bucket1 = bucket2 = 1 << 8;
	
	bool noneSet = !cmd.isSet("r");
	if (noneSet) {
		std::cout
		<< "=================================\n"
		<< "||  Private Set Intersection   ||\n"
		<< "=================================\n"
		<< "\n"
		<< "This program reports the performance of the private set intersection protocol.\n"
		<< "\n"
		<< "Experimenet flag:\n"
		<< " -r 0    to run a sender.\n"
		<< " -r 1    to run a receiver.\n"
		<< "\n"
		<< "Parameters:\n"
		<< " -ss     log(#elements) on sender side.\n"
		<< " -rs     log(#elements) on receiver side.\n"
		<< " -w      width of the matrix.\n"
		<< " -w1      width of the matrix from CM20.\n"
		<< " -h      log(height) of the matrix.\n"
		<< " -hash   hash output length in bytes.\n"
		<< " -ip     ip address (and port).\n"
		;
	} else {
		if (cmd.get<u64>("r") == 0) {
			runSenderKey1_2();
			runSenderKey1_3();
			runSenderKey1_4();
			runSenderKey2_3();
			runSenderKey2_4();
			runSenderKey3_4();

			runSender();
			runSenderOffline_next0();
			runSenderOffline_next1();
			runSender_next1();
			runSender_next2();
			runSender_next3();
		} else if (cmd.get<u64>("r") == 1) {
			runReceiverKey2_1();
			runReceiverKey3_1();
			runReceiverKey4_1();
			runReceiverKey3_2();
			runReceiverKey4_2();
			runReceiverKey4_3();
			
			runReceiver();
			runReceiverOffline_next0();
			runReceiverOffline_next1();
			runReceiver_next1();
			runReceiver_next2();
			runReceiver_next3();
		} 
	}		
	
	return 0;
}




