#include <gtest/gtest.h>
#include "GigablastTestUtils.h"
#include "Loop.h"
#include "Collectiondb.h"
#include "Statsdb.h"
#include "Posdb.h"
#include "Titledb.h"
#include "Tagdb.h"
#include "Spider.h"
#include "Doledb.h"
#include "Clusterdb.h"
#include "Linkdb.h"

static void deleteRdbFiles() {
	// delete all rdb files
	for (int rdbId = RDB_NONE; rdbId < RDB_END; ++rdbId) {
		Rdb *rdb = getRdbFromId(rdbId);
		if (rdb) {
			for (int32_t i = 0; i < rdb->getNumBases(); ++i ) {
				RdbBase *base = rdb->getBase(i);
				if (base) {
					for (int32_t j = 0; j < base->getNumFiles(); ++j) {
						ASSERT_TRUE(base->getFile(j)->unlink());
						ASSERT_TRUE(base->getMap(j)->unlink());

						if (base->getIndex(j)) {
							ASSERT_TRUE(base->getIndex(j)->unlink());
						}
					}
				}
			}
		}
	}
}

void GbTest::initializeRdbs() {
	ASSERT_TRUE(g_loop.init());

	ASSERT_TRUE(g_collectiondb.loadAllCollRecs());

	ASSERT_TRUE(g_statsdb.init());
	ASSERT_TRUE(g_posdb.init());
	ASSERT_TRUE(g_titledb.init());
	ASSERT_TRUE(g_tagdb.init());
	ASSERT_TRUE(g_spiderdb.init());
	ASSERT_TRUE(g_doledb.init());
	ASSERT_TRUE(g_spiderCache.init());
	ASSERT_TRUE(g_clusterdb.init());
	ASSERT_TRUE(g_linkdb.init());

	ASSERT_TRUE(g_collectiondb.addRdbBaseToAllRdbsForEachCollRec());
}

void GbTest::resetRdbs() {
	deleteRdbFiles();

	g_linkdb.reset();
	g_clusterdb.reset();
	g_spiderCache.reset();
	g_doledb.reset();
	g_spiderdb.reset();
	g_tagdb.reset();
	g_titledb.reset();
	g_posdb.reset();
	g_statsdb.reset();

	g_collectiondb.reset();

	g_loop.reset();
	new(&g_loop) Loop(); // some variables are not Loop::reset. Call the constructor to re-initialize them
}

void GbTest::addPosdbKey(RdbBuckets *buckets, int64_t termId, int64_t docId, int32_t wordPos, bool isDelKey) {
	char key[MAX_KEY_BYTES];
	::Posdb::makeKey(&key, termId, docId, wordPos, 0, 0, 0, 0, 0, 0, 0, false, isDelKey, false);
	buckets->addNode(0, key, NULL, 0);
}

void GbTest::addPosdbKey(RdbIndex *index, int64_t termId, int64_t docId, int32_t wordPos, bool isDelKey) {
    char key[MAX_KEY_BYTES];
	::Posdb::makeKey(&key, termId, docId, wordPos, 0, 0, 0, 0, 0, 0, 0, false, isDelKey, false);
    index->addRecord(key);
}