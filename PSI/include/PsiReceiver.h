#pragma once

#include "Defines.h"

#include <vector>

namespace PSI {

	class PsiReceiver {
	public:
		PsiReceiver() {}

		void runKey2_1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);
		void runKey3_1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);
		void runKey4_1(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);
		void runKey3_2(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);
		void runKey4_2(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);
		void runKey4_3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);


		void runOffline(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes);
		void runOffline_next0(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes);
		void runOffline_next1(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes);

		void run(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);
		void run_next1(Channel& ch, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes);
		void run_next2(Channel& ch, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& width, const u64& hashLengthInBytes);
		void run_next3(PRNG& prng, Channel& ch, block commonSeed, const u64& senderSize, const u64& receiverSize, const u64& height, const u64& logHeight, const u64& height1, const u64& logHeight1, const u64& width, const u64& width1, std::vector<block>& receiverSet, const u64& hashLengthInBytes, const u64& h1LengthInBytes, const u64& bucket1, const u64& bucket2);

	};

}
