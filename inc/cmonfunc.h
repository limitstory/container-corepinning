#ifndef CMONFUNC_H
#define CMONFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "docker.h"
#include "cJSON.h"
#include "container.h"
#include "sysinfo.h"
#include "linkedlist.h"
#include "util.h"
#include "dataunit.h"

container* init_container_list();
container* get_container_info(container*);
container* get_container_usage_info(container*);
container* get_total_container_info(container*);
void dump_head(container*);

#endif