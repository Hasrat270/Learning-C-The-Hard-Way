#ifndef _statserve_protocol_h
#define _statserve_protocol_h

#include "../16-Trees/44-TernarySearchTrees_Library.h"
#include "../20-Stats_Engine/41-StatisticsEngine_Library.h"
#include "../13-Safer_Strings/34-bstrlib.h"

typedef struct StatServer {
    TSTree *stats_tree;
} StatServer;

StatServer *StatServer_create();
void StatServer_destroy(StatServer *server);

bstring StatServer_process(StatServer *server, bstring input);

#endif
