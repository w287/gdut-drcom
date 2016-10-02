#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "auth.h"
#include "config.h"

static void print_help(char * name);

int main(int argc, char *argv[])
{
    char conf_file_name[256] = {0};

    if (argc == 1)
    {
        print_help(argv[0]);
        exit(-1);
    }

    int opt;
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"help",                no_argument,        0,  'h'},
            {"config-file",         required_argument,  0,  'c'},
            {"remote-ip",           required_argument,  0,  0},
            {"remote-port",         required_argument,  0,  1},
            {"keep-alive1-flag",    required_argument,  0,  2},
            {0,             0,                  0,  0},
        };
        opt = getopt_long(argc, argv, "hc:", long_options, &option_index);
        if (opt == -1)
        {
            break;
        }
        switch (opt)
        {
            case 0:     //remote-ip
                strcpy(drcom_config.remote_ip, optarg);
                break;
            case 1:     //remote_port
                drcom_config.remote_port = atoi(optarg);
                break;
            case 2:     //keep_alive1_flag
                sscanf(optarg, "%02hhx", &drcom_config.keep_alive1_flag);
                break;
            case 'c':
                strcpy(conf_file_name, optarg);
                parse_config(conf_file_name);
                break;
            case 'h':
                print_help(argv[0]);
                exit(0);
                break;
            case '?':
                break;
            default:
                break;
        }
    }
//    if (!conf_file_name[0] == '\0')
//    {
//        parse_config(conf_file_name);
//    }
#ifdef DEBUG
    fprintf(stdout, "drcom_config.remote_ip = %s\n", drcom_config.remote_ip);
    fprintf(stdout, "drcom_config.remote_port = %d\n", drcom_config.remote_port);
    fprintf(stdout, "drcom_config.keep_alive1_flag = %02hhx\n", drcom_config.keep_alive1_flag);
    fflush(stdout);
#endif

    auth();

    return 0;
}

static void print_help(char *name)
{
    fprintf(stdout, "gdut-drcom\n");
    fprintf(stdout, "  A third-partydrcom client for gdut.\n\n");
    fprintf(stdout, "usage:\n");
    fprintf(stdout, "  %s\n", name);
    fprintf(stdout, "    --remote-ip <ip addr>\t\tThe server ip.\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    [--remote-port <port>]\t\tThe server port, default as 61440.\n");
    fprintf(stdout, "    [--keep-alive1-flag <flag>]\t\tThe keep alive 1 packet's flag,"
            "\t\t\t\t\t\t\t\t    default as 00.\n");
    fprintf(stdout, "    [-c, --config-file <file>]\t\tThe path to config file. "
            "\t\t\t\t\t\t\t\t    default as /etc/gdut-drcom.conf\n");
    fprintf(stdout, "    [-h, --help]\t\t\tPrint this message.\n");
}

