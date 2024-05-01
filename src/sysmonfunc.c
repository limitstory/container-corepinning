#include "sysmonfunc.h"

void get_process_resource_data()
{
    // awk 사용방법을 습득하는 것이 system 지표 뽑아내는데 좋을 것 같다.
    // popen & strok로 난잡한 코드를 짜느니 awk로 미리 값을 전처리하고 그 값을 저장하는 것이 좋아보임 
    char *topcpu = "top -bn 2 -d 0.01 | grep '^%Cpu' | tail -n 1 | awk '{print $2+$4+$6}'";
    char *get_number_cpus = "grep -c processor /proc/cpuinfo";
    char *freemem = "free | grep 'Mem'";
    char *freemem1 = "free | grep 'Mem' | awk '{print $2,$3,$4,$5,$6}'";

    char buff[BUFF_SIZE];
    FILE *fp;
    char *ptr;
    
    fp = popen(topcpu, "r");
    
    if (NULL == fp)
        perror("Failed popen()");

    fgets(buff, BUFF_SIZE, fp); //get CPU info

    system_info.cpu_usage = atof(buff);
    pclose(fp);

    // get number of CPUs
    fp = popen(get_number_cpus, "r");

    if (NULL == fp)
        perror("Failed popen()");

    fgets(buff, BUFF_SIZE, fp); //get number of CPUs
    system_info.number_cpus = atoi(buff);
    pclose(fp);

    /* 
    내용이 입력된 행을 선택하고, 행의 데이터를 split하여 값을 추출하는 logic
    
    // index 3번째 cpu 정보 4번째 메모리 정보 5번째 swap 정보
    //여기서 내용 쪼개서 객체에 집어넣어야 한다.

    //for (int i = 0; i < 3; i++)
        fgets(buff, BUFF_SIZE, fp); //get CPU info
    printf( "%s\n", buff);

    
    //ptr = strtok(buff, " "); // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    ptr = strtok(NULL, " ");
    printf("%s\n", ptr);
    system_info.user_cpu_usage = atof(ptr);

    ptr = strtok(NULL, " ");
    ptr = strtok(NULL, " ");
    system_info.system_cpu_usage = atof(ptr);
*/

    fp = popen(freemem, "r");
    
    if (NULL == fp)
        perror("Failed popen()");

    fgets(buff, BUFF_SIZE, fp); //get memory info (KiB)
    
    ptr = strtok(buff, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    
    ptr = strtok(NULL, " ");
    system_info.total_memory = (u_int64_t)atol(ptr);
    for (int i = 0; i < 4; i++)
         ptr = strtok(NULL, " ");
    system_info.used_cache = (u_int64_t)atol(ptr);
    ptr = strtok(NULL, " ");
    system_info.available_memory = (u_int64_t)atol(ptr);

    system_info.used_memory = system_info.total_memory - system_info.available_memory;

    pclose(fp);
}