#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

int clock(listType *Lptr, int seconds);
int add_pid(listType *Lptr, struct timer item);
int remv_pid(listType *Lptr, int pid);

int main() {
    struct timer T;
    listType list;
    listType *Lptr = &list;
    int param_no, pid, time;
    char input[64], cmd[32];

    Init(Lptr);

    while (1) {
        printf("=== Input ===\n> ");
        bzero(input, sizeof(input));
        fgets(input, sizeof(input), stdin);
        param_no = sscanf(input, "%s %d %d", cmd, &time, &pid);

        if (strcmp(cmd, "add") == 0) {
            if (param_no < 3) {
                puts("Usage error : add <time> <pid>\n");
                continue;
            }

            T.Time = time;
            T.Pid = pid;
            add_pid(Lptr, T);
            PrintList(Lptr);
        }
        else if (strcmp(cmd, "clock") == 0) {
            if (param_no != 2) {
                puts("Usage error : clock <time>\n");
                continue;
            }

            clock(Lptr, time);
        }
        else if (strcmp(cmd, "remove") == 0) {
            if (param_no != 2) {
                puts("Usage error : remove <pid>\n");
                continue;
            }

            remv_pid(Lptr, time);  // pid
            PrintList(Lptr);
        }
        else if (strcmp(cmd, "print") == 0) {
            if (Length(Lptr) == 0) {
                puts("List is empty");
            }
            else
                PrintList(Lptr);
        }
        else if (strcmp(cmd, "exit") == 0) {
            puts("Exiting...\n");
            Deconst(Lptr);
            break;
        }
        else if (strcmp(cmd, "help") == 0) {
            puts("[ Usage ]");
            puts("add <time> <pid>");
            puts("clock <time>");
            puts("remove <pid>");
            puts("print");
            puts("help");
            puts("exit");
        }
        else {
            puts("Unknown command");
            puts("Use \"help\" to see commands or \"exit\" to exit");
        }

        puts("");
    }
}

int add_pid(listType *Lptr, struct timer item) {
    struct timer temp;
    int time = 0, i = 0, tmp;

    if (item.Time == 0) {
        puts("Can't add item : time is 0");
        return 0;
    }
    if (FindPid(Lptr, item.Pid) != -1) {
        printf("Pid(%d) is already in list\n", item.Pid);
        return 0;
    }

    for (; i < Length(Lptr); i++) {
        Retrieve(Lptr, i, &temp);
        time += temp.Time;

        if (time < item.Time) {
            continue;
        }
        else if (time == item.Time) {
            i++;
            break;
        }
        else {
            item.Time -= time - temp.Time;
            Insert(Lptr, i, item);
            Update_i(Lptr, ++i, -item.Time);
            return 1;
        }
    }

    item.Time -= time;
    Insert(Lptr, i, item);
}

int clock(listType *Lptr, int seconds) {
    struct timer temp;
    char pid[128];
    int i;

    if (seconds)
        puts("** Starting clock emulation");
    else
        return -1;

    for (i = 0; i < seconds; i++) {
        printf("** Time Passed (%ds)", i + 1);
        strcpy(pid, " /");

        if (Length(Lptr) == 0) {
            puts("** Exiting emulation : empty list");
            return 0;
        }

        Update_i(Lptr, 0, -1);

        while (1) {
            if (Length(Lptr) == 0) {
                printf("%s\n", pid);
                puts("** Exiting emulation : empty list");
                return 0;
            }

            Retrieve(Lptr, 0, &temp);
            if (temp.Time == 0) {
                Delete(Lptr, 0, NULL);
                sprintf(pid, "%s %d", pid, temp.Pid);
            }
            else {
                printf("%s\n", pid);
                PrintList(Lptr);
                puts("");
                break;
            }
        }

        sleep(1);
    }
}

int remv_pid(listType *Lptr, int pid) {
    int i = 0, pos, time;
    struct timer temp;

    if (Length(Lptr) == 0) {
        puts("List is empty");
        return 0;
    }

    if ((pos = FindPid(Lptr, pid)) < 0) {
        printf("Can't find pid : %d\n", pid);
        return -1;
    }

    Delete(Lptr, pos, &temp);
    printf("** Deleted pid : %d (time left : %d)\n", temp.Pid, temp.Time);

    if (pos <= Length(Lptr) - 1) {
        Update_i(Lptr, pos, temp.Time);
    }
}