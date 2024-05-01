#include "scale.h"

container *scale_CPU(container *start)
{
    if (start == NULL) //exception handling
    {
        fprintf(stderr, "ERROR: Not exist container list!\n");
        start = NULL;
        return start;
    }
    
    container *head = start;

    DOCKER *docker = docker_init("v1.41");
    char request[150];
    CURLcode response;

    if (!docker) // exception handling
    {
        fprintf(stderr, "ERROR: Failed to connect a docker client!\n");
        start = NULL;
        return start;
    }

    // core 개수를 동적으로 할당할 수 있긴 해야하는데 그럼 로직이 너무 더러워질거같아서...
    // 나중에 보강을 고민해보자
    for (int i = 0; head != NULL; i++)
    {
        strcpy(request, "http://v1.41/containers/");
        strcat(request, head->name);
        strcat(request, "/update");

        // threshold mechanism based elatic cpu allocation 
        if (system_info.cpu_usage - total_container_info.total_cpu_usage >= 50.0)
        {
            response = docker_post(docker, request, "{\"CpusetCpus\": \"6-7\"}");
            head->number_cpus = 2;
        }
        else if (system_info.cpu_usage - total_container_info.total_cpu_usage >= 30.0)
        {
            response = docker_post(docker, request, "{\"CpusetCpus\": \"5-7\"}");
            head->number_cpus = 3;
        }
        else
        {
            response = docker_post(docker, request, "{\"CpusetCpus\": \"4-7\"}");
            head->number_cpus = 4;
        }

        if (response != CURLE_OK) // response failed
        {
            fprintf(stderr, "ERROR: Failed to get a responce to docker client!\n");
            return start;
        }
            
        head = head->next;
    }
    
    docker_destroy(docker);

    return start;
}