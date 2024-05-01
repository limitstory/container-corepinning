#include "main.h"

int main()
{
    //printf("main(): triggerd from core-tracekr...!\n");

    // Manage container metric sets as simple linked lists
    container *start;

    // tacking the host(vm) overall resource info for all of containers
    for (int i = 1; ; i++)
    {
        if (i == 100) // limit the number of monitoring
            break;

        switch (i)
        {
            case 1: printf("1st mornitoring number\n"); break;
            case 2: printf("2nd mornitoring number\n"); break;
            case 3: printf("3rd mornitoring number\n"); break;
            default: printf("%dth mornitoring number\n", i);
        }

        start = init_container_list(); // do malloc to linked list
        get_process_resource_data(); //get system resource data
        start = get_container_info(start); // get container info
        start = get_container_usage_info(start); //get container usage info
        start = get_total_container_info(start); // get total usage info of containers
        start = scale_CPU(start); // threshold mechanism based elatic cpu scailing 
        dump_head(start); // print system & constiner status
        do_free(start); // free malloc to linked list

        // sleep(1);
    }

    return 0;
}
