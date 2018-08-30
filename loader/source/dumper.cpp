#include <switch.h>
#include <cstdio>
#include <cstring>
#include "sha256.h"
#include "lz4.h"
#include "ldr_nso.hpp"
#include "ldr_npdm.hpp"
#include "ldr_map.hpp"
#include "ldr_random.hpp"
#include "dumper.hpp"

bool Dumper::isExist(char * path)
{
	FILE * f = fopen(path, "r");
	bool ret = (f != NULL);
	if(ret)
	{
		fclose(f);
	}
	return ret;
}

bool Dumper::isDumpFlag(u64 title_id)
{
	char path[FS_MAX_PATH];
	snprintf(path, FS_MAX_PATH, "sdmc:/dumps/%016lx/exefs/dumpflag", title_id);
	return Dumper::isExist(path);
}

void Dumper::dumpNso(u64 title_id, unsigned int index)
{
	char writeFilePath[FS_MAX_PATH];
	snprintf(writeFilePath, FS_MAX_PATH, "sdmc:/dumps/%016lx/exefs/%s", title_id, NsoUtils::GetNsoFileName(index));
	if(!Dumper::isExist(writeFilePath))
	{
		FILE * writeFile = fopen(writeFilePath, "wb");
		FILE * readFile = NsoUtils::OpenNsoFromExeFS(index);
		if((writeFile != NULL) && (readFile != NULL))
		{
			unsigned char dumpedByte;
			while(1)
			{
				if(fread(&dumpedByte, sizeof(unsigned char), 1, readFile) < 1)
				{
					break;
				}
				if(fwrite(&dumpedByte, sizeof(unsigned char), 1, writeFile) < 1)
				{
					break;
				}
			}
		}
		if(writeFile != NULL)
		{
			fclose(writeFile);
		}
		if(readFile != NULL)
		{
			fclose(readFile);
		}
	}
}

void Dumper::dumpNpdm(u64 title_id)
{
	char writeFilePath[FS_MAX_PATH];
	snprintf(writeFilePath, FS_MAX_PATH, "sdmc:/dumps/%016lx/exefs/main.npdm", title_id);
	if(!Dumper::isExist(writeFilePath))
	{
		FILE * writeFile = fopen(writeFilePath, "wb");
		FILE * readFile = NpdmUtils::OpenNpdmFromExeFS();
		if((writeFile != NULL) && (readFile != NULL))
		{
			unsigned char dumpedByte;
			while(1)
			{
				if(fread(&dumpedByte, sizeof(unsigned char), 1, readFile) < 1)
				{
					break;
				}
				if(fwrite(&dumpedByte, sizeof(unsigned char), 1, writeFile) < 1)
				{
					break;
				}
			}
		}
		if(writeFile != NULL)
		{
			fclose(writeFile);
		}
		if(readFile != NULL)
		{
			fclose(readFile);
		}
	}
}