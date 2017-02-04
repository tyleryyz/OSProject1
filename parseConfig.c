#include "parseConfig.h"

char **parseConfig(char* argv[])
  {
    char **config_data = malloc(9 * sizeof(char*));
    const char config_delim[2] = ":";
    const char version_delim[2] = ".";
    const char space_delim[2] = " ";
    char str_buffer[60];
    char line_buffer[60];
    char data_buffer[60];
    char *version_number;
    char *file_path;
    char *sched_code;
    char *quant_time;
    char *mem_avail;
    char *proc_cycle_time;
    char *io_cycle_time;
    char *log_to;
    char *log_file_path;
    char * filename = argv[1];
    int version_number_check;
    int quant_time_check;
    int mem_avail_check;
    int proc_cycle_check;
    int io_cycle_check;

    // checks for correct file ext.

    if (strstr(filename, ".cnf") == NULL)
      {
        config_data[0] = malloc(strlen("ERROR[0]")+1);
        strcpy(config_data[0], "ERROR[0]");
        return config_data;
      }

    // begin parsing

    FILE *config_file = fopen(argv[1], "r");

    if (config_file == NULL)
      {
        config_data[0] = malloc(strlen("ERROR[1]")+1);
        strcpy(config_data[0], "ERROR[1]");
        return config_data;
      }

    fgets(str_buffer, 60, config_file);
    fscanf(config_file, "%s %s", line_buffer, data_buffer);

    // parsing version number

    version_number = strtok(data_buffer, version_delim);
    version_number_check = atoi(version_number);

    if (version_number_check == 0 && strcmp(version_number, "0"))
      {
        config_data[0] = malloc(strlen("ERROR[2]")+1);
        strcpy(config_data[0], "ERROR[2]");
        fclose(config_file);
        return config_data;
      }

    else if (version_number_check > 10 || version_number_check <= 0 )
      {
        config_data[0] = malloc(strlen("ERROR[2]")+1);
        strcpy(config_data[0], "ERROR[2]");
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
    if (strstr(file_path, ".mdf") == NULL)
      {
        config_data[1] = malloc(strlen("ERROR")+1);
        strcpy(config_data[1], "ERROR");
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

    if ((strcmp(sched_code, "NONE") != 0) && (strcmp(sched_code, "FCFS-N") != 0)
        && (strcmp(sched_code, "SJF-N") != 0) && (strcmp(sched_code, "SRTF-P") != 0)
        && (strcmp(sched_code, "FCFS-P") != 0) && (strcmp(sched_code, "RR-P") != 0))
          {
            config_data[2] = malloc(strlen("ERROR")+1);
            strcpy(config_data[2], "ERROR");
            fclose(config_file);
            return config_data;
          }
    if (strcmp(sched_code, "NONE") == 0)
      {
        config_data[2] = malloc(strlen("FCFS-N")+1);
        strcpy(config_data[2], "FCFS-N");
      }
    else
      {
        config_data[2] = malloc(strlen(sched_code)+1);
        strcpy(config_data[2], sched_code);
      }

    // Parsing Quantum Time

    fgets(str_buffer, 60, config_file);
    quant_time = strtok(str_buffer, config_delim);
    quant_time = strtok(NULL, space_delim);
    quant_time = strtok(quant_time, "\n");
    quant_time_check = atoi(quant_time);

    if (quant_time_check == 0 && strcmp(quant_time, "0"))
      {
        config_data[3] = malloc(strlen("ERROR")+1);
        strcpy(config_data[3], "ERROR");
        fclose(config_file);
        return config_data;
      }

    else if (quant_time_check > 100 || quant_time_check < 0)
      {
        config_data[3] = malloc(strlen("ERROR")+1);
        strcpy(config_data[3], "ERROR");
        fclose(config_file);
        return config_data;
      }

    config_data[3] = malloc(strlen(quant_time)+1);
    strcpy(config_data[3], quant_time);

    // Parsing Memory Available

    fgets(str_buffer, 60, config_file);
    mem_avail = strtok(str_buffer, config_delim);
    mem_avail = strtok(NULL, space_delim);
    mem_avail = strtok(mem_avail, "\n");
    mem_avail_check = atoi(mem_avail);

    if (mem_avail_check == 0 && strcmp(mem_avail, "0"))
      {
        config_data[4] = malloc(strlen("ERROR")+1);
        strcpy(config_data[4], "ERROR");
        fclose(config_file);
        return config_data;
      }

    else if (mem_avail_check > 1048576 || mem_avail_check < 0)
      {
        config_data[4] = malloc(strlen("ERROR")+1);
        strcpy(config_data[4], "ERROR");
        fclose(config_file);
        return config_data;
      }

    config_data[4] = malloc(strlen(mem_avail)+1);
    strcpy(config_data[4], mem_avail);

    // Parsing Processor Cycle Time

    fgets(str_buffer, 60, config_file);
    proc_cycle_time = strtok(str_buffer, config_delim);
    proc_cycle_time = strtok(NULL, space_delim);
    proc_cycle_time = strtok(proc_cycle_time, "\n");
    proc_cycle_check = atoi(proc_cycle_time);

    if (proc_cycle_check == 0 && strcmp(proc_cycle_time, "0"))
      {
        config_data[5] = malloc(strlen("ERROR")+1);
        strcpy(config_data[5], "ERROR");
        fclose(config_file);
        return config_data;
      }

    else if (proc_cycle_check > 1000 || proc_cycle_check < 1)
      {
        config_data[5] = malloc(strlen("ERROR")+1);
        strcpy(config_data[5], "ERROR");
        fclose(config_file);
        return config_data;
      }

    config_data[5] = malloc(strlen(proc_cycle_time)+1);
    strcpy(config_data[5], proc_cycle_time);

    // Parsing I/O Cycle Time

    fgets(str_buffer, 60, config_file);
    io_cycle_time = strtok(str_buffer, config_delim);
    io_cycle_time = strtok(NULL, space_delim);
    io_cycle_time = strtok(io_cycle_time, "\n");
    io_cycle_check = atoi(io_cycle_time);

    if (io_cycle_check == 0 && strcmp(io_cycle_time, "0"))
      {
        config_data[6] = malloc(strlen("ERROR")+1);
        strcpy(config_data[6], "ERROR");
        fclose(config_file);
        return config_data;
      }

    else if (io_cycle_check > 10000 || io_cycle_check < 1)
      {
        config_data[6] = malloc(strlen("ERROR")+1);
        strcpy(config_data[6], "ERROR");
        fclose(config_file);
        return config_data;
      }

    config_data[6] = malloc(strlen(io_cycle_time)+1);
    strcpy(config_data[6], io_cycle_time);

    // Parsing Log To

    fgets(str_buffer, 60, config_file);
    log_to = strtok(str_buffer, config_delim);
    log_to = strtok(NULL, space_delim);
    log_to = strtok(log_to, "\n");

    if ((strcmp(log_to, "Monitor")!=0) && (strcmp(log_to, "Both")!=0)
        && (strcmp(log_to, "File")!=0))
          {
            config_data[7] = malloc(strlen("ERROR")+1);
            strcpy(config_data[7], "ERROR");
            fclose(config_file);
            return config_data;
          }
    else
      {
        config_data[7] = malloc(strlen(log_to)+1);
        strcpy(config_data[7], log_to);
      }

    // Parsing Log File Path

    fgets(str_buffer, 60, config_file);
    log_file_path = strtok(str_buffer, config_delim);
    log_file_path = strtok(NULL, space_delim);
    log_file_path = strtok(log_file_path, "\n");

    if (strstr(log_file_path, ".lgf") == NULL)
      {
        config_data[8] = malloc(strlen("ERROR")+1);
        strcpy(config_data[8], "ERROR");
        fclose(config_file);
        return config_data;
      }

    config_data[8] = malloc(strlen(log_file_path)+1);
    strcpy(config_data[8], log_file_path);


    fclose(config_file);
    return config_data;
  }
