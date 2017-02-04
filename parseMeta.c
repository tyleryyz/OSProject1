#include "parseMeta.h"

struct Points *parseMeta(char* input_file[])
  {
    fflush(stdout);
    struct Points *meta_data;
    //char meta_line[100];
    //char *buffer;
    int iterator;
    int number_of_lines;
    int number_of_delims;
    char buffer[100];
    const char *line_check;
    char *file_letter;
    char *operator;
    char *cycle_time;
    char *sample_proc;
    int *delims_per_line;

    FILE* meta_file = fopen(input_file[1], "r");

    // getting number of lines in file
    while(fgets(buffer, 100, meta_file)!=NULL)
      {
        number_of_lines++;
      }
    printf("%d\n", number_of_lines);
    fclose(meta_file);
    FILE* meta_file1 = fopen(input_file[1], "r");

    delims_per_line = malloc(sizeof(int)*number_of_lines-2);

    // Getting the number of processes per line
    for (iterator = 1; iterator<number_of_lines -1; iterator++)
      {
        fgets(buffer, 100, meta_file1);
        line_check = buffer;
        while ((line_check = strstr(line_check, ";")))
          {
            number_of_delims++;
            line_check++;
          }
        delims_per_line[iterator] = number_of_delims;
        if(iterator == number_of_lines -2)
          {
            number_of_delims++;
            delims_per_line[iterator] = number_of_delims;
          }
        number_of_delims = 0;
      }

    fclose(meta_file1);
    FILE* meta_file2 = fopen(input_file[1], "r");

  //  for (iterator = 2; iterator < number_of_lines-1; iterator++){
    //  printf("line: %d delims per line: %d\n", iterator, delims_per_line[iterator]);
    //}


    fgets(buffer, 100, meta_file2);
    fgets(buffer, 100, meta_file2);
    sample_proc = strtok(buffer, ";");
    printf("%s\n", sample_proc);

    file_letter = strtok(NULL, ";");
    printf("%s\n", file_letter);



    meta_data = malloc(sizeof(struct Points) * number_of_delims+1);

    fclose(meta_file2);
    return meta_data;

  }
