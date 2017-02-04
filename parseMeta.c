#include "parseMeta.h"

struct Points *parseMeta(char* input_file[])
  {
    fflush(stdout);
    struct Points *meta_data;
    int iterator=0;
    int tmp=0;
    int number_of_lines=0;
    int number_of_delims=0;
    char buffer[350];
    const char *line_check;
    char *file_letter;
    char *operator;
    char *cycle_time;
    char *sample_proc;
    int *delims_per_line;
    FILE *meta_file;

    meta_file = fopen(input_file[1], "r");
    if (meta_file == NULL){
      exit(1);
    }


    // getting number of lines in file
    while(!feof(meta_file))
      {
        tmp = fgetc(meta_file);
        if (tmp == '\n')
          {
            number_of_lines+=1;

          }
      }


    rewind(meta_file);

    delims_per_line = malloc(sizeof(int)*number_of_lines-1);

    // Getting the number of processes per line
    for (iterator = 0; iterator<number_of_lines; iterator++)
      {
        fgets(buffer, 350, meta_file);
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


    rewind(meta_file);



    fgets(buffer, 350, meta_file);
  for (iterator = 1; iterator < number_of_lines; iterator++)
      {
        fgets(buffer, 350, meta_file);
        sample_proc = strtok(buffer, ";");
        printf("Starts Here %s\n", sample_proc);
        char* throwaway = sample_proc;
        printf("COPIES HERE %s\n", throwaway);
        file_letter = strtok(throwaway, "(");
        printf("%s\n", file_letter);
        printf("letter Here %s\n", sample_proc);
        operator = strtok(NULL, ")");
        printf("%s\n", operator);
        printf("operator Here %s\n", sample_proc);
        cycle_time = strtok(NULL, ".");
        printf("%s\n", cycle_time);
        printf("cycle Here %s\n", sample_proc);
        printf("blows up here: %s\n", sample_proc);
        for (tmp = 0; tmp < delims_per_line[iterator]-1; tmp++)
          {
            sample_proc = strtok(NULL, ";");
            if (tmp == delims_per_line[iterator]-2)
              {
                sample_proc = strtok(sample_proc, "\n");
                const char* removed_space = sample_proc;

                while(*removed_space != '\0' && isspace(*removed_space))
                {
                  ++removed_space;
                }
                size_t len = strlen(removed_space)+1;
                memmove(sample_proc, removed_space, len);
                //printf("%s\n", sample_proc);
              }
              const char* removed_space = sample_proc;

              while(*removed_space != '\0' && isspace(*removed_space))
              {
                ++removed_space;
              }
              size_t len = strlen(removed_space)+1;
              memmove(sample_proc, removed_space, len);
              //printf("%s\n", sample_proc);
            printf("%s\n", sample_proc);
          }
      }
    /*fgets(buffer, 350, meta_file);
    sample_proc = strtok(buffer, ";");
    printf("%s\n", sample_proc);
    sample_proc = strtok(NULL, ";");
    printf("%s\n", sample_proc);
    sample_proc = strtok(NULL, ";");
    printf("%s\n", sample_proc);
    sample_proc = strtok(NULL, ";");
    printf("%s\n", sample_proc);
    sample_proc = strtok(sample_proc, "\n");
    printf("%s\n", sample_proc);
    const char* removed_space = sample_proc;

    while(*removed_space != '\0' && isspace(*removed_space))
    {
      ++removed_space;
    }
    size_t len = strlen(removed_space)+1;
    memmove(sample_proc, removed_space, len);
    printf("%s\n", sample_proc);

    file_letter = strtok(sample_proc, "(");
    printf("%s\n", file_letter);
    operator = strtok(NULL, ")");
    printf("%s\n", operator);
    cycle_time = strtok(NULL, ".");
    printf("%s\n", cycle_time);

//*/

    meta_data = malloc(sizeof(struct Points) * number_of_delims+1);

    fclose(meta_file);
    return meta_data;

  }
