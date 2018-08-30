#pragma once
#include <switch.h>

class Dumper
{
	public:
		static bool isExist(char * path);
		static bool isDumpFlag(u64 title_id);
		static void dumpNso(u64 title_id, unsigned int i);
		static void dumpNpdm(u64 title_id);
};