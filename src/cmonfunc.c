#include "cmonfunc.h"

/*
    현재 컨테이너의 개수가 몇개인지 체크하고
    연결리스트의 개수를 증가시킨다.
*/
container *init_container_list()
{
    //printf("do_init(): do_init() invoked...\n");

    DOCKER *docker = docker_init("v1.41");
    CURLcode response;
    container *start = NULL; // Initial state of linked list
    container *head = NULL;


    if (!docker) // exception handling
    {
        fprintf(stderr, "ERROR: Failed to connect a docker client!\n");
        start = NULL;
        return start;
    }

    response = docker_get(docker, "http://v1.41/containers/json");

    if (response != CURLE_OK) // response failed
    {
        fprintf(stderr, "ERROR: Failed to get a responce to docker client!\n");
        start = NULL;
        return start;
    }

    cJSON *all_container_info = cJSON_Parse(docker_buffer(docker)); // total json informaiton from json

    if (all_container_info == NULL) // exception handling
    {
        printf("get_list_data(); error on cJSON root struct\n");
        start = NULL;
        return start;
    }

    for (int i = 0; i < cJSON_GetArraySize(all_container_info); i++) // get number of containers
        start = add_tail(start); // add containers to linked list

    head = start;

    for (int i = 0; head != NULL; i++)
    {
        // get JSON INFO per subContainer
        cJSON *container_info = cJSON_GetArrayItem(all_container_info, i); // i번째 배열에서 값을 가져와서 저장

        // input values in linked list
        strcpy(head->id, cJSON_GetObjectItem(container_info, "Id")->valuestring);

        //이름이 여러개일 수도 있나?? 일단 하나만 하고 나중에 여러개이면 그에 맞추어 자료구조와 로직을 바꿔야 할 것.
        // cJSON_GetArraySize(cJSON_GetObjectItem(container_info, "Names"));를 통해 배열의 크기 확인 가능...(return int)
        cJSON *Names = cJSON_GetArrayItem(cJSON_GetObjectItem(container_info, "Names"), 0);
        strcpy(head->name, Names->valuestring);
        rid_off_symbol(head->name);

        head = head->next;
    }

    //initialize container total infomation
    total_container_info.total_con_num = 0;
    total_container_info.total_mem_usage = 0;
    total_container_info.total_cpu_usage = 0;
    total_container_info.total_net_usage = 0;
    total_container_info.total_disk_usage = 0;

    docker_destroy(docker);

    //printf("do_init(): Number of %d containers running...\n", cJSON_GetArraySize(all_container_info));

    return start;
}

/*
get_con_stats(char json){


}
*/

container *get_container_info(container *start)
{
    if (start == NULL)
    {
        fprintf(stderr, "ERROR: Not exist container list!\n");
        start = NULL;
        return start;
    }
    container *head = start;

    DOCKER *docker = docker_init("v1.41");
    CURLcode response;

    if (!docker) // exception handling
    {
        fprintf(stderr, "ERROR: Failed to connect a docker client!\n");
        start = NULL;
        return start;
    }

    response = docker_get(docker, "http://v1.41/containers/json");

    if (response != CURLE_OK) // response failed
    {
        fprintf(stderr, "ERROR: Failed to get a responce to docker client!\n");
        start = NULL;
        return start;
    }

    cJSON *all_container_info = cJSON_Parse(docker_buffer(docker)); // total json informaiton from json

    if (all_container_info == NULL) // exception handling
    {
        printf("get_list_data(); error on cJSON root struct\n");
        head = NULL;
        return head;
    }

    // parsing is arised in here, temp_ary used for parsing items consisting of ary with ["chars"]
    for (int i = 0; head != NULL; i++)
    {
        // get JSON INFO per subContainer
        cJSON *container_info = cJSON_GetArrayItem(all_container_info, i); // i번째 배열에서 값을 가져와서 저장

        // input values in linked list
        strcpy(head->id, cJSON_GetObjectItem(container_info, "Id")->valuestring);

        //이름이 여러개일 수도 있나?? 일단 하나만 하고 나중에 여러개이면 그에 맞추어 자료구조와 로직을 바꿔야 할 것.
        // cJSON_GetArraySize(cJSON_GetObjectItem(container_info, "Names"));를 통해 배열의 크기 확인 가능...(return int)
        cJSON *Names = cJSON_GetArrayItem(cJSON_GetObjectItem(container_info, "Names"), 0);
        strcpy(head->name, Names->valuestring);
        rid_off_symbol(head->name);

        strcpy(head->image, cJSON_GetObjectItem(container_info, "Image")->valuestring);
        strcpy(head->command, cJSON_GetObjectItem(container_info, "Command")->valuestring);
        head->created = (u_int64_t)cJSON_GetObjectItem(container_info, "Created")->valueint;
        strcpy(head->state, cJSON_GetObjectItem(container_info, "State")->valuestring);
        strcpy(head->status, cJSON_GetObjectItem(container_info, "Status")->valuestring);

        // code 길이 및 memory 압축 위해 바로 child로 접근
        // original approach
        // cJSON *Networks = cJSON_GetObjectItem(container_info, "NetworkSettings");
        // cJSON *Networks = cJSON_GetObjectItem(NetworkSettings, "Networks");
        // cJSON *bridge = cJSON_GetObjectItem(Networks, "bridge");

        cJSON *bridge = cJSON_GetObjectItem(container_info, "NetworkSettings")->child->child;
        strcpy(head->IPAddress, cJSON_GetObjectItem(bridge, "IPAddress")->valuestring);   // input values in linked list
        strcpy(head->MacAddress, cJSON_GetObjectItem(bridge, "MacAddress")->valuestring); // input values in linked list

        head = head->next;
    }
    docker_destroy(docker);

    //printf("get_container_info(): successfully returned...\n");

    return start;
}

container *get_container_usage_info(container *start)
{
    if (start == NULL)
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

    for (int i = 0; head != NULL; i++)
    {
        cJSON *temp;
        strcpy(request, "http://v1.41/containers/");
        strcat(request, head->name);
        strcat(request, "/stats?stream=false");
        response = docker_get(docker, request);

        if (response != CURLE_OK) // response failed
        {
            fprintf(stderr, "ERROR: Failed to get a responce to docker client!\n");
            start = NULL;
            return start;
        }

        cJSON *container_usage_info = cJSON_Parse(docker_buffer(docker));
        if (container_usage_info == NULL) // exception handling
        {
            printf("get_list_data(); error on cJSON root struct\n");
            head = NULL;
            return start;
        }

        // 일단 임시방편으로 연결리스트의 정보를 비워둔다. 연결리스트를 삭제하고 재정의하는 것이 마땅함
        // 그러나 그건 이후에 고민해야 함 이거 때문에 이중연결리스트로 구현해야 할 수 있음

        if (cJSON_GetObjectItem(container_usage_info, "pids_stats")->child == NULL) 
        {
            // Exception handling
            head->is_data = 0;
            head = head->next;
            continue;
        }

        head->is_data = 1;
       
        /* network */
        cJSON *eth0 = cJSON_GetObjectItem(container_usage_info, "networks")->child;
        head->rx_byte = (u_int64_t)cJSON_GetObjectItem(eth0, "rx_bytes")->valuedouble;
        head->tx_byte = (u_int64_t)cJSON_GetObjectItem(eth0, "tx_bytes")->valuedouble;
        head->rx_packets = (u_int64_t)cJSON_GetObjectItem(eth0, "rx_packets")->valuedouble;
        head->tx_packets = (u_int64_t)cJSON_GetObjectItem(eth0, "tx_packets")->valuedouble;

        /* BLOCK */
        cJSON *blkio_stats = cJSON_GetObjectItem(container_usage_info, "blkio_stats");

        // size of bytes
        cJSON *io_service_bytes_recursive = cJSON_GetObjectItem(blkio_stats, "io_service_bytes_recursive");
        if (cJSON_GetArraySize(io_service_bytes_recursive) == 0) //exception handling
        {
            // set value to 0 (read, write, sync, async, discard, total)
            for (int i = 0; i < sizeof(head->blk_byte)/sizeof(u_int64_t); i++)
                head->blk_byte[i] = 0;
        }
        else
        {
            // set value (read, write, sync, async, discard, total)
            for (int i = 0; i < sizeof(head->blk_byte)/sizeof(u_int64_t); i++)
                head->blk_byte[i] = (u_int64_t)cJSON_GetObjectItem(
                    cJSON_GetArrayItem(io_service_bytes_recursive, i), "value")->valuedouble;
        }
        
        // number of block io requests
        cJSON *io_serviced_recursive = cJSON_GetObjectItem(blkio_stats, "io_serviced_recursive");
        if (cJSON_GetArraySize(io_serviced_recursive) == 0) //exception handling
        {
            // set value to 0 (read, write, sync, async, discard, total)
            for (int i = 0; i < sizeof(head->blk_num)/sizeof(u_int64_t); i++)
                head->blk_num[i] = 0;
        }
        else
        {
            // set value (read, write, sync, async, discard, total)
            for (int i = 0; i < sizeof(head->blk_num)/sizeof(u_int64_t); i++)
                head->blk_num[i] = (u_int64_t)cJSON_GetObjectItem(
                    cJSON_GetArrayItem(io_serviced_recursive, i), "value")->valuedouble;
        }

        /*CPU*/
        //cpu_delta = cpu_stats.cpu_usage.total_usage - precpu_stats.cpu_usage.total_usage
        //system_cpu_delta = cpu_stats.system_cpu_usage - precpu_stats.system_cpu_usage
        cJSON *cpu_stats = cJSON_GetObjectItem(container_usage_info, "cpu_stats");
        cJSON *precpu_stats = cJSON_GetObjectItem(container_usage_info, "precpu_stats");
        
        head->cpu_total_usage = (u_int64_t)cJSON_GetObjectItem(cpu_stats->child, "total_usage")->valuedouble;
        head->precpu_total_usage = (u_int64_t)cJSON_GetObjectItem(precpu_stats->child, "total_usage")->valuedouble;
        head->cpu_delta = head->cpu_total_usage - head->precpu_total_usage;
        head->system_cpu_usage = (u_int64_t)cJSON_GetObjectItem(cpu_stats, "system_cpu_usage")->valuedouble;
        head->system_precpu_usage = (u_int64_t)cJSON_GetObjectItem(precpu_stats, "system_cpu_usage")->valuedouble;
        head->system_cpu_delta = head->system_cpu_usage - head->system_precpu_usage;

        //CPU Usage 전체를 100%로 계산한 것 기준임
        //CPU Usage 전체를 800%(1thread당 100%)로 계산하고 싶다면 (double)head->cpu_delta / (double)head->system_cpu_delta) * head->number_cpus * 100.0 수행
        head->cpu_usage = ((double)head->cpu_delta / (double)head->system_cpu_delta) * 100.0;

        /*Memory*/
        cJSON *memory_stats = cJSON_GetObjectItem(container_usage_info, "memory_stats");
        cJSON *memory_stats_stats = cJSON_GetObjectItem(memory_stats, "stats");
        head->memory_stats_usage = (u_int64_t)cJSON_GetObjectItem(memory_stats, "usage")->valuedouble;
        head->memory_stats_cache = (u_int64_t)cJSON_GetObjectItem(memory_stats_stats, "cache")->valuedouble;
        //used memory = memory_stats_usage - memory_stats_cache
        head->used_memory = head->memory_stats_usage - head->memory_stats_cache;
        head->available_memory = (u_int64_t)cJSON_GetObjectItem(memory_stats, "limit")->valuedouble;

        head = head->next;
    }

    //printf("get_network_info(): finished succesfully...\n");
    docker_destroy(docker);

    return start;
}

container *get_total_container_info(container *start)
{
    container *head = start;

    for (int i = 0; head != NULL; i++)
    {
        // 임시방편 예외처리...
        if (head->is_data == 0) //data is non-exist
        {
            // Exception handling
            head = head->next;
            continue;
        }
        
        total_container_info.total_con_num++;
        total_container_info.total_mem_usage += head->used_memory;
        total_container_info.total_cpu_usage += head->cpu_usage;

        //network 사용량과 디스크 사용량은 일단 보류함
        //total_container_info.total_net_usage = 0;
        //total_container_info.total_disk_usage = 0;

        head = head->next;
    }

    return start;
}

void dump_head(container *start) // print all the infomation for containes
{
    container *head = start;
    int dump_count = 1;
    int dump_finish = total_container_info.total_con_num;

    system("clear"); //clear console
    printf("--------------------process ID: %d-------------------------------\n", getpid());
    printf("System Info:\n");
    printf("CPU Usage: %.2f%%, CPU Nums: %d\n", system_info.cpu_usage, system_info.number_cpus);
    //Kib to GB: devide 976600, 출력형식 조정 필요함...
    printf("Mem Usage: %ld\t Total Memory: %ld\n", system_info.used_memory, system_info.total_memory);
    printf("------------------------------------------------------------\n");
    // 전역변수 쓰면서 코드가 고장난건가 왜 total_container에서 system 값이 나옴?
    printf("Total Container Info\n");
    printf("CPU Usage: %.2f%%\n", total_container_info.total_cpu_usage);
    printf("Mem Usage: ");
    div_bibyte_recursive(total_container_info.total_mem_usage, GiB);
    printf("\n");
    printf("------------------------------------------------------------\n");
    
    while (head != NULL)
    {
        // 임시방편 예외처리...
        if (head->is_data == 0) //data is non-exist
        {
            // Exception handling
            head = head->next;
            continue;
        }

        printf("[%d th container info]\n", dump_count++);
        printf("ID: %s\n", head->id);
        printf("NAMES: %s\n", head->name);
        printf("IMAGE: %s\n", head->image);
        printf("Create Time: %ld\n", head->created);
        printf("State: %s\n", head->state);
        printf("IPAddress: %s\n", head->IPAddress);
        printf("MacAddr: %s\n", head->MacAddress);
        //Network I/O Usuage
        //GB부터 recursive 구조로 짜서 MB, KB, Byte까지 단위가 내려갈수 있도록 조치한 코드
        printf("Network I/O: ");
        div_byte_recursive(head->rx_byte, GB); printf("(packets:%ld)/", head->rx_packets);
        div_byte_recursive(head->tx_byte, GB); printf("(packets:%ld)\n", head->tx_packets);
        //Block I/O Usuage
        printf("Block I/O: ");
        div_byte_recursive(head->blk_byte[0], GB);
        printf("(number: %ld)/", head->blk_num[0]);
        div_byte_recursive(head->blk_byte[1], GB);
        printf("(number: %ld)\n", head->blk_num[1]);
        printf("number cpus: %ld CPU usage (%%) %.2lf%%\n", head->number_cpus, head->cpu_usage);
        //Gib부터 recursive 구조로 짜서 Mib, Kib, Byte까지 내려갈수 있도록 조치한 코드
        printf("Memory Usage/LIMIT: ");
        div_bibyte_recursive(head->used_memory, GiB);
        printf("/");
        div_bibyte_recursive(head->available_memory, GiB);
        printf("\n");
        //Memory usage(%) = (used_memory / available_memory) * 100.0
        printf("Memory percent(%%) %.2f%%\n", (double)head->used_memory/(double)head->available_memory * 100);        
        printf("\n\n");
        head = head->next;
    }
    printf("\n(dump_head) all container INFO are printed...\n");
    printf("\n---------------------------------------------------\n\n\n");

    return;
}

/*
void display(Con *head)
{
    container* list = head;
    int pos = 0;

    if (head == NULL)
    {
        printf("display(): no container list\n");
        return;
    }else
    {

        printf("display(): container order print. . . \n\n\n ");
        while (list!= NULL)
        {
            printf("[pos:%d, id:%s, name:%s, pid:%d, cpu usage:%.2f, mem usage:%.2f, net_tx:%.2f, net_rx:%.2f, bl_r:%.2f, bl_w:%.2f ] \n", pos++, list->id, list->name, list->pid, list->CPU_usage, list->mem_usage, list->net_tx_bw, list->net_rx_bw, list->block_w_bw, list->block_r_bw);
            list = list->next;
        }
        if (list == NULL) {
            printf("[NULL]\n");
        }
    }
}
*/
