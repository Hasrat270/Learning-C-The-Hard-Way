#include "statserve_protocol.h"
#include "../05-Debugging_and_Macros/18-DebugMacros.h"
#include <ctype.h>

StatServer *StatServer_create()
{
    StatServer *server = malloc(sizeof(StatServer));
    check_mem(server);
    server->stats_tree = NULL;
    return server;

error:
    return NULL;
}

void StatServer_destroy(StatServer *server)
{
    if (server) {
        if (server->stats_tree) TSTree_destroy(server->stats_tree);
        free(server);
    }
}

bstring StatServer_process(StatServer *server, bstring input)
{
    struct bstrList *args = bsplit(input, ' ');
    bstring cmd = args->entry[0];
    bstring result = bfromcstr("ERROR\n");

    if (biseqcstr(cmd, "create") && args->qty == 2) {
        Stats *st = Stats_create();
        server->stats_tree = TSTree_insert(server->stats_tree, bdata(args->entry[1]), blength(args->entry[1]), st);
        result = bfromcstr("OK\n");
    } else if (biseqcstr(cmd, "sample") && args->qty == 3) {
        Stats *st = TSTree_search(server->stats_tree, bdata(args->entry[1]), blength(args->entry[1]));
        if (st) {
            Stats_sample(st, atof(bdata(args->entry[2])));
            result = bfromcstr("OK\n");
        }
    } else if (biseqcstr(cmd, "mean") && args->qty == 2) {
        Stats *st = TSTree_search(server->stats_tree, bdata(args->entry[1]), blength(args->entry[1]));
        if (st) {
            result = bformat("MEAN: %f\n", Stats_mean(st));
        }
    } else if (biseqcstr(cmd, "store") && args->qty == 2) {
        // Exercise 51: Implementation for storing to disk
        result = bfromcstr("STORED\n");
    }

    bstrListDestroy(args);
    return result;
}
