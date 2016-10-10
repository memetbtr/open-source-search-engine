#ifndef GB_RDBTESTUTILS_H
#define GB_RDBTESTUTILS_H

class RdbBuckets;
class RdbIndex;

namespace GbTest {
	void initializeRdbs();
	void resetRdbs();

	void addPosdbKey(RdbBuckets *buckets, int64_t termId, int64_t docId, int32_t wordPos, bool isDelKey = false);
	void addPosdbKey(RdbIndex *index, int64_t termId, int64_t docId, int32_t wordPos, bool isDelKey = false);

}


#endif // GB_RDBTESTUTILS_H