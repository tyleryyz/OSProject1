#include "parseConfig.h"

char **parseConfig(char* argv[])
  {
    const char config_delim[2] = ":";
    const char version_delim[2] = ".";
    const char space_delim[2] = " ";
    char **config_data = malloc(9 * sizeof(char*));
    char str_buffer[60];
    char line_buffer[60];
    char data_buffer[60];
    char *version_number;
    char *file_path;
    char *sched_code;
    //char *quant_time;
    //char *mem_avail;
    //char *proc_cycle_time;
    //char *io_cycle_time;
    //char *log_to;
    //char *log_file_path;
    char * filename = argv[1];
    int version_number_check;
    // checks for correct file ext.

    if (strstr(filename, ".cnf") == NULL)
      {
        config_data[0] = malloc(strlen("ERROR[0]")+1);
        strcpy(config_data[0], "ERROR[0]");
        return config_data;
      }
    // begin parsing
    FILE* config_file = fopen(argv[1], "r");
    fgets(str_buffer, 60, config_file);
    fscanf(config_file, "%s %s", line_buffer, data_buffer);

    // parsing version number

    version_number = strtok(data_buffer, version_delim);

    version_number_check = atoi(version_number);

    if (version_number_check == 0 && strcmp(version_number, "0"))
      {
        config_data[0] = malloc(strlen("ERROR[0]")+1);
        strcpy(config_data[0], "ERROR[0]");
        fclose(config_file);
        return config_data;
      }

    else if (version_number_check >= 10)
      {
        config_data[0] = malloc(strlen("ERROR[0]")+1);
        strcpy(config_data[0], "ERROR[0]");
        fclose(config_file);
        return config_data;
      }

    config_data[0] = malloc(strlen(version_number)+1);
    strcpy(config_data[0], version_number);
    fgetc(config_file);

    // parsing file path

    fgets(str_buffer, 60, config_file);
    file_path = strtok(str_buffer, config_delim);
    file_path = strtok(NULL, space_delim);
    file_path = strtok(file_path, "\n");
    printf("%s", file_path);
    if (strstr(file_path, ".mdf") == NULL)
      {
        config_data[1] = malloc(strlen("ERROR[0]")+1);
        strcpy(config_data[1], "ERROR[0]");
        fclose(config_file);
        return config_data;
      }
    config_data[1] = malloc(strlen(file_path)+1);
    strcpy(config_data[1], file_path);

    //parsing CPU Scheduling Code

    fgets(str_buffer, 60, config_file);
    sched_code = strtok(str_buffer, config_delim);
    sched_code = strtok(NULL, space_delim);
    sched_code = strtok(sched_code, "\n");
    if ((strcmp(sched_code, "NONE") !=0) && (strcmp(sched_code, "FCFS-N")!=0) &&
        (strcmp(sched_code, "SJF-N")!=0) && (strcmp(sched_code, "SRTF-P")!=0) &&
        (strcmp(sched_code, "FCFS-P")!=0) && (strcmp(sched_code, "RR-P")!=0))
        {
          config_data[2] = malloc(strlen("ERROR[0]")+1);
          strcpy(config_data[2], "ERROR[0]");
          fclose(config_file);
          return config_data;
        }
    printf("here!!!");
    if (strcmp(sched_code, "NONE")==0)
      {
        config_data[2] = malloc(strlen("FCFS-N")+1);
        strcpy(config_data[2], "FCFS-N");
      }
    printf("here!!!");
    config_data[1] = malloc(strlen(sched_code)+1);
    strcpy(config_data[1], sched_code);




    fclose(config_file);
    return config_data;
  }
