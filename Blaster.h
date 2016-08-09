#ifndef GB_BLASTER_H
#define GB_BLASTER_H

#include "Conf.h"
#include "Dns.h"
#include "HttpServer.h"
#include "HashTableT.h"
#include "Loop.h"
#include "iana_charset.h"
#include <sys/resource.h>  // setrlimit

struct StateBD;

class Blaster {
 public:
	Blaster();
	~Blaster();
	
	void reset();

	bool init();

	void runBlaster(char *file1,char *file2,
			int32_t maxNumThreads, int32_t wait, 
			bool isLogFile,
			bool verbose,bool justDisplay,
			bool useProxy,
			bool injectUrlWithLinks = false ,
			bool injectUrl = false );

	void startBlastering();

	void freeStateBD(StateBD *st);

	void gotDoc1(void *state,TcpSocket *s);

	void gotDoc2(void *state,TcpSocket *s);

	void gotDoc3 ( void *state, TcpSocket *s);

	void gotDoc4 ( void *state, TcpSocket *s);

	void processLogFile(void *state);

	bool m_doInjection;
	bool m_doInjectionWithLinks;

 protected:
	int32_t  m_maxNumThreads;
	int32_t  m_launched;
	char *m_buf1;
	int32_t  m_bufSize1;
	char *m_buf2;
	int32_t m_bufSize2;
	char *m_p1;
	char *m_p1end;
	char *m_p2;
	char *m_p2end;
	int32_t  m_totalUrls;
	int32_t  m_totalDone;
	bool  m_portSwitch;
	int32_t  m_wait;
	bool  m_justDisplay;
	bool  m_useProxy;
	bool  m_verbose;
	bool  m_isLogFile;
	int64_t m_startTime;
	bool m_blasterDiff;
	bool m_print;
};

extern Blaster g_blaster;

#endif // GB_BLASTER_H

