#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "thread.h"

static pthread_t monitor_tid;
static int running = 1;

static void *monitor_loop(void *arg)
{
    (void)arg;
    while (running)
    {
        sleep(10);
        if (running)
            printf("\n[Monitor] ShellForge is running...\n");
    }
    return NULL;
}

void start_monitor_thread(void)
{
    running = 1;
    if (pthread_create(&monitor_tid, NULL, monitor_loop, NULL) != 0)
        perror("pthread_create");
    pthread_detach(monitor_tid);
}

void stop_monitor_thread(void)
{
    running = 0;
}
