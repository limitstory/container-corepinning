#ifndef SYSINFO_H
#define SYSINFO_H

typedef struct SystemResourceInfo //Total of system metric
{
    // metric은 하나씩 추가해나갑시다...
    // 시스템의 전체 메모리 용량
    float cpu_usage;
    int number_cpus;
    // 나중에 각 데이터가 필요하면 그때 고민...
    //float user_cpu_usage;
    //float system_cpu_usage;
    //float total_cpu_usage;
    u_int64_t total_memory;
    u_int64_t used_cache;
    u_int64_t available_memory;
    u_int64_t used_memory; // 얘는 top에서 받아오는 그대로의 값과 작업관리자의 값이 다른데 왜그런지 확인해봐야되지 않을까
} sysinfo;

sysinfo system_info;

#endif