#include "parseMeta.h"

struct Points *parseMeta(char* input_file[], int* count)
  {
    fflush(stdout);
    struct Points *meta_data;
    int iterator=0;
    int tmp=0;
    int number_of_lines=0;
    int number_of_delims=0;
    int tempiterator=0;
    int operator_iterator=0;
    int cycle_time_iterator=0;
    char buffer[350];
    const char *line_check;
    char file_letter;
    char *operator;
    char *cycle_time;
    char *sample_proc;

    int cycle_time_int;
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

    meta_data = malloc(sizeof(struct Points) * number_of_delims+1);

    operator = malloc(25*sizeof(char)+1);
    cycle_time = malloc(25*sizeof(char)+1);
    fgets(buffer, 350, meta_file);
    for (iterator = 1; iterator < number_of_lines-1; iterator++)
        {
          fgets(buffer, 350, meta_file);
          sample_proc = strtok(buffer, ";");
          RemoveSpaces(sample_proc);


          //--------------------------------------------------------------------
          //-------------------------FIRST PARSE--------------------------------
          //--------------------------------------------------------------------
          memset(operator, 0, strlen(operator));
          memset(cycle_time, 0, strlen(cycle_time));

          tempiterator = 0;
          operator_iterator = 0;
          cycle_time_iterator = 0;
          for (tempiterator = 0; tempiterator<strlen(sample_proc); tempiterator++){
            while (sample_proc[tempiterator] != '('){
              if (sample_proc[tempiterator] == '('){
                break;
              }
              file_letter = sample_proc[tempiterator];
              tempiterator++;
            }
            while (sample_proc[tempiterator++] != ')'){

              if (sample_proc[tempiterator] == ')'){
                break;
              }
              operator[operator_iterator++] = sample_proc[tempiterator];
            }
            operator[operator_iterator++] = '\0';
            tempiterator++;
            while (sample_proc[tempiterator] != '\0' && sample_proc[tempiterator] != '.'){

              if (sample_proc[tempiterator] == '.' || sample_proc[tempiterator] == '\0'){

                break;
              }
              cycle_time[cycle_time_iterator++] = sample_proc[tempiterator];
              tempiterator++;
            }
          }

        cycle_time_int = atoi(cycle_time);
        meta_data[(*count)].file_letter = file_letter;
        meta_data[(*count)].operation = (char*)malloc(strlen(operator)*sizeof(char));
        meta_data[(*count)].operation = operator;
        meta_data[(*count)].cycle_time = cycle_time_int;
        (*count)++;
        //--------------------------------------------------------------------
        //-------------------------END PARSE--------------------------------
        //--------------------------------------------------------------------

          for (tmp = 0; tmp < delims_per_line[iterator]-1; tmp++)
            {
              sample_proc = strtok(NULL, ";");
              RemoveSpaces(sample_proc);

              if (tmp == delims_per_line[iterator]-2)
                {
                  sample_proc = strtok(sample_proc, "\n");
                  RemoveSpaces(sample_proc);
                }
              RemoveSpaces(sample_proc);


              //--------------------------------------------------------------------
              //-------------------------SECOND PARSE--------------------------------
              //--------------------------------------------------------------------
              memset(operator, 0, strlen(operator));
              memset(cycle_time, 0, strlen(cycle_time));

              tempiterator = 0;
              operator_iterator = 0;
              cycle_time_iterator = 0;
              for (tempiterator = 0; tempiterator<strlen(sample_proc); tempiterator++){
                while (sample_proc[tempiterator] != '('){
                  if (sample_proc[tempiterator] == '('){
                    break;
                  }
                  file_letter = sample_proc[tempiterator];
                  tempiterator++;
                }
                while (sample_proc[tempiterator++] != ')'){

                  if (sample_proc[tempiterator] == ')'){
                    break;
                  }
                  operator[operator_iterator++] = sample_proc[tempiterator];
                }
                operator[operator_iterator++] = '\0';
                tempiterator++;
                while (sample_proc[tempiterator] != '\0' && sample_proc[tempiterator] != '.'){

                  if (sample_proc[tempiterator] == '.' || sample_proc[tempiterator] == '\0'){

                    break;
                  }
                  cycle_time[cycle_time_iterator++] = sample_proc[tempiterator];
                  tempiterator++;
                }
              }

            cycle_time_int = atoi(cycle_time);
            printf("file_letter: %c\n", file_letter);
            printf("operator: %s\n", operator);
            printf("cycle_time: %d\n", cycle_time_int);
            printf("count: %d\n", (*count));
            meta_data[(*count)].file_letter = file_letter;
            printf("file letter being stored: %c\n", meta_data[(*count)].file_letter);
            strcat(operator, "\0");
            iterator = 0;
            for (iterator = 0; iterator < strlen(operator); iterator++){
              printf("%c\n", operator[iterator]);
            }

            meta_data[(*count)].operation = (char*)malloc(strlen(operator)*sizeof(char));
            meta_data[(*count)].operation = operator;
            printf("operation being stored: %s\n", meta_data[(*count)].operation);
            meta_data[(*count)].cycle_time = cycle_time_int;
            printf("cycle time being stored: %d\n", meta_data[(*count)].cycle_time);
            (*count)++;
            //--------------------------------------------------------------------
            //-------------------------END PARSE--------------------------------
            //--------------------------------------------------------------------
            }
        }
        iterator = 0;
        for (iterator = 0; iterator < (*count); iterator++)
          {
            printf("count: %d\n", iterator);
            printf("file letter start: %c\n", meta_data[iterator].file_letter);
            printf("operation: %s\n", meta_data[iterator].operation);
            printf("cycle time: %d\n", meta_data[iterator].cycle_time);
          }
    fclose(meta_file);
    return meta_data;
}

void RemoveSpaces(char* string)
{
  char* temp1 = string;
  char* temp2 = string;
  while(*temp2 != 0)
  {
    *temp1 = *temp2++;
    if(*temp1 != ' ')
      temp1++;
  }
  *temp1 = 0;
}
