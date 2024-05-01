#ifndef CONTAINER_H
#define CONTAINER_H

typedef struct TotalContainerInfo //Total of container metric
{
    int total_con_num;
    u_int64_t total_mem_usage;
    float total_cpu_usage;
    int total_net_usage;
    int total_disk_usage;
} total_container;

total_container total_container_info;

typedef struct ContainerInfo //metric of containers
{
    //basic container info
    char id[100];
    char name[50];
    char image[100];
    char command[150];
    u_int64_t created;
    char state[100];
    char status[150];

    char IPAddress[20];
    char MacAddress[20];

    double mem_usage;
    double cpu_usage;

    //detailed container info
    
    int is_data;

    // network
    u_int64_t rx_byte;
    u_int64_t tx_byte;
    u_int64_t rx_packets;
    u_int64_t tx_packets;
    
    //disk
    //blkio_stats에서 major가 무엇을 뜻하는지 확인할 필요성이 있음...
    u_int64_t blk_byte[6]; // read, write, sync, async, discard, total
    u_int64_t blk_num[6]; // read, write, sync, async, discard, total
    
    //cpu
    u_int64_t percpu_usage[20];
    u_int64_t cpu_total_usage;
    u_int64_t system_cpu_usage;
    u_int64_t precpu_total_usage;
    u_int64_t system_precpu_usage;
    u_int64_t cpu_delta;
    u_int64_t system_cpu_delta;
    u_int64_t number_cpus;
    //u_int64_t usage_in_usermode;
    //u_int64_t usage_in_kernelmode;
    
    //mem
    u_int64_t memory_stats_usage;
    u_int64_t memory_stats_cache;
    u_int64_t used_memory;
    u_int64_t available_memory;


    int PIDs;    // number of processes
    int vCPU[4]; // allocated core id;
    int pid;
    struct ContainerInfo *next;
} container;

# endif