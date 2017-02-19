#include <string.h>
#include <stdlib.h>
#include "parseConfig.h"
#include "parseMeta.h"

int main(int argc, char *argv[])
  {
    char** parsed_config_data;
    char** parsed_meta_data_points;


    // command line argument checking
    if (argc < 2)
      {
        fprintf(stderr, "ERROR: must include config file\n");
        return(1);
      }
    else if (argc > 2)
      {
        fprintf(stderr, "ERROR: too many arguments passed\n");
        return(1);
      }

    // calling the parser on the configuration file
    parsed_config_data = parseConfig(argv);

    // error checking for configuration file
    if (parsed_config_data[0] == NULL)
      {
        fprintf(stderr, "ERROR: no data parsed, bad config file\n");
        return(1);
      }

    else if (!strcmp(parsed_config_data[0], "ERROR[0]"))
      {
        fprintf(stderr, "ERROR: Incorrect config file type (must be .cnf)\n");
        return(1);
      }

    else if (!strcmp(parsed_config_data[0], "ERROR[1]"))
      {
        fprintf(stderr, "ERROR: No file opened (must be .cnf)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[0], "ERROR[2]"))
      {
        fprintf(stderr, "ERROR: Version number too high/incorrect data (must be a value between 0 and 10 inclusive)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[1], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect file type in file (must be .mdf)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[2], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect schedule code (must be NONE, FCFS-N, SJF-N, SRTF-P, FCFS-P, RR-P)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[3], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect value for quantum time (must be a value between 0 and 100 inclusive)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[4], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect value for memory available (must be a value between 0 and 1,048,576 inclusive)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[5], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect value for processor cycle time (must be a value between 1 and 1,000 inclusive)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[6], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect value for I/O cycle time (must be a value between 1 and 10,000 inclusive)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[7], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect value for log to (must be Monitor, File, or Both)\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[8], "ERROR"))
      {
        fprintf(stderr, "ERROR: Incorrect file type for log file path (must be .lgf)\n");
        return(1);
      }

    //parsing meta data
    parsed_meta_data_points = parseMeta(parsed_config_data);

    //outputting parsed config data
    printf("\nConfiguration File Data\n");
    printf("Version/Phase: %s\n", parsed_config_data[0]);
    printf("File Path: %s\n", parsed_config_data[1]);
    printf("CPU Scheduling Code: %s\n", parsed_config_data[2]);
    printf("Quantum Time (cycles): %s\n", parsed_config_data[3]);
    printf("Memory Available (KB): %s\n", parsed_config_data[4]);
    printf("Processor Cycle Time (msec): %s\n", parsed_config_data[5]);
    printf("I/O Cycle Time (msec): %s\n", parsed_config_data[6]);
    printf("Log To: %s\n", parsed_config_data[7]);
    printf("Log File Path: %s\n", parsed_config_data[8]);


    free(parsed_meta_data_points);
    free(parsed_config_data);
    return(0);
  }
