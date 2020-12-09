/*
 * Computer Architecture CSE530
 * MIPS pipeline cycle-accurate simulator
 * PSU
 */

#ifndef __UTIL_H__
#define __UTIL_H__
#include <cstdint>

enum ReplacementPolicy;

uint64_t extern currCycle;

extern bool DEBUG_MEMORY;
extern bool DEBUG_PIPE;
extern bool DEBUG_CACHE;
extern bool DEBUG_PREFETCH;

extern bool TRACE_MEMORY;

#define DPRINTF(flag, fmt, ...) \
	if(flag) \
        fprintf(stdout, "Cycle %5lu : [%-20s][%-20s]%4d: " fmt, currCycle, __FILE__, __func__, __LINE__, ##__VA_ARGS__);
#define DPRINTPACKET(src, message, packet)\
	DPRINTF(DEBUG_CACHE, "%8s: %-25s %s\n",src,message,packet->toString().c_str())

#define TRACE(flag, cond, fmt, ...) \
	if((flag) && (cond)) \
        fprintf(stdout, fmt, ##__VA_ARGS__);

enum PacketSrcType {
	PacketTypeFetch = 0,
	PacketTypeLoad = 1,
	PacketTypeStore = 2,
	PacketTypePrefetch = 3,
	PacketTypeWriteBack = 4
};

class MemHrchyInfo{
public:
	uint64_t cache_size_l1;
	uint64_t cache_assoc_l1;
	uint64_t cache_size_l2;
	uint64_t cache_assoc_l2;
	uint64_t cache_blk_size;
	//todo for now keep it int
	int repl_policy_l1i;
	int repl_policy_l1d;
	int repl_policy_l2;
	uint64_t access_delay_l1;
	uint32_t access_delay_l2;
	uint32_t memDelay;

	MemHrchyInfo() {
		cache_size_l1 = 32768;
		cache_assoc_l1 = 4;
		cache_size_l2 = 2 * 1024 * 1024;
		cache_assoc_l2 = 16;
		cache_blk_size = 64;
		repl_policy_l1i = ReplacementPolicy::RandomReplPolicy;
		repl_policy_l1d = ReplacementPolicy::RandomReplPolicy;
		repl_policy_l2 = ReplacementPolicy::RandomReplPolicy;
		access_delay_l1 = 2;
		access_delay_l2 = 20;
		memDelay = 100;
	}
};

/**
 * Terminal codes
*/
#define TERM_CODE_START "\033["
#define TERM_CODE_END "m"
#define TERM_CODE(x) TERM_CODE_START x TERM_CODE_END
#define TERM_INVERSE TERM_CODE("7")
#define TERM_RESET TERM_CODE("0")

#endif
