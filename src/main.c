#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <jansson.h>

#define MAX_INPUT 100

typedef struct
{
  char department[20];
  char name[50];
  char job_title[50];
  int position;
  char emp_status[20];
} employee_s;

employee_s *employees_s;

char opt[MAX_INPUT];
char buff_opt[MAX_INPUT];
int n_employees = 0;

int read_json_data(const char *file_name, const char *dep)
{
  FILE *fd = fopen(file_name, "r");
  if (fd == NULL)
  {
    printf("failed to open file\n");
    return 1;
  }

  char buffer[4080];
  memset(buffer, 0x00, sizeof(buffer));
  fread(buffer, 1, sizeof(buffer), fd);

  fclose(fd);

  json_t *obj_js;
  json_error_t error;
  obj_js = json_loads(buffer, 0, &error);
  json_t *employees = json_object_get(obj_js, "employee");

  for (size_t i = 0; i < json_array_size(employees); i++)
  {
    json_t *employee = json_array_get(employees, i);
    json_t *name = json_object_get(employee, "name");
    json_t *job = json_object_get(employee, "job_title");
    json_t *position = json_object_get(employee, "position_level");
    json_t *emp_stat = json_object_get(employee, "employment_status");
    n_employees++;
    char buff_post[20];
    memset(buff_post, 0x00, sizeof(buff_post));
    employees_s = realloc(employees_s, n_employees * sizeof(employee_s));
    strcpy(employees_s[n_employees - 1].department, dep);
    strcpy(employees_s[n_employees - 1].name, json_string_value(name));
    strcpy(employees_s[n_employees - 1].job_title, json_string_value(job));
    strcpy(buff_post, json_string_value(position));
    employees_s[n_employees - 1].position = atoi(buff_post);
    strcpy(employees_s[n_employees - 1].emp_status, json_string_value(emp_stat));
  }

  json_decref(obj_js);

  return 0;
}

int get_position_level(char *buff)
{
  int ibuff = atoi(buff);
  printf("\nemployee with position level %i\n", ibuff);
  for (int i = 0; i < n_employees; i++)
  {
    if (employees_s[i].position == ibuff)
    {
      printf("--------------------------------------------\n");
      printf("department: %s\n", employees_s[i].department);
      printf("name      : %s\n", employees_s[i].name);
      printf("job title : %s\n", employees_s[i].job_title);
      printf("pos level : %i\n", employees_s[i].position);
      printf("emp status: %s\n", employees_s[i].emp_status);
      printf("\n");
    }
  }
  return 0;
}

int get_job_title(char *buff)
{
  int flag_get_data = 0;
  printf("\nemployee with job title %s\n", buff);
  for (int i = 0; i < n_employees; i++)
  {
    if (memcmp(employees_s[i].job_title, buff, strlen(buff)) == 0)
    {
      flag_get_data = 1;
      printf("--------------------------------------------\n");
      printf("department: %s\n", employees_s[i].department);
      printf("name      : %s\n", employees_s[i].name);
      printf("job title : %s\n", employees_s[i].job_title);
      printf("pos level : %i\n", employees_s[i].position);
      printf("emp status: %s\n", employees_s[i].emp_status);
      printf("\n");
    }
  }
  if (!flag_get_data)
  {
    printf("sorry there is no such a %s job title\n", buff);
  }
  return 0;
}

int get_employment_status(char *buff)
{
  int ibuff = atoi(buff);
  const char *emp_stat[4] = {"contract", "casual", "part-time", "full-time"};
  printf("\nemployee with employment status %s\n", emp_stat[ibuff - 1]);
  for (int i = 0; i < n_employees; i++)
  {
    if (memcmp(employees_s[i].emp_status, emp_stat[ibuff - 1], strlen(emp_stat[ibuff - 1])) == 0)
    {
      printf("--------------------------------------------\n");
      printf("department: %s\n", employees_s[i].department);
      printf("name      : %s\n", employees_s[i].name);
      printf("job title : %s\n", employees_s[i].job_title);
      printf("pos level : %i\n", employees_s[i].position);
      printf("emp status: %s\n", employees_s[i].emp_status);
      printf("\n");
    }
  }
  return 0;
}

int get_department(char *buff)
{
  int ibuff = atoi(buff);
  const char *dep[3] = {"marketing", "production", "rnd"};
  printf("\nemployee with department %s\n", dep[ibuff - 1]);
  for (int i = 0; i < n_employees; i++)
  {
    if (memcmp(employees_s[i].department, dep[ibuff - 1], strlen(dep[ibuff - 1])) == 0)
    {
      printf("--------------------------------------------\n");
      printf("department: %s\n", employees_s[i].department);
      printf("name      : %s\n", employees_s[i].name);
      printf("job title : %s\n", employees_s[i].job_title);
      printf("pos level : %i\n", employees_s[i].position);
      printf("emp status: %s\n", employees_s[i].emp_status);
      printf("\n");
    }
  }
  return 0;
}

int get_name(char *buff)
{
  int flag_get_data = 0;
  printf("\nemployee with name %s\n", buff);
  for (int i = 0; i < n_employees; i++)
  {
    if (memcmp(employees_s[i].name, buff, strlen(buff)) == 0)
    {
      flag_get_data = 1;
      printf("--------------------------------------------\n");
      printf("department: %s\n", employees_s[i].department);
      printf("name      : %s\n", employees_s[i].name);
      printf("job title : %s\n", employees_s[i].job_title);
      printf("pos level : %i\n", employees_s[i].position);
      printf("emp status: %s\n", employees_s[i].emp_status);
      printf("\n");
    }
  }

  if (!flag_get_data)
  {
    printf("sorry there is no employee named %s\n", buff);
  }
  return 0;
}

int main(int argc, char **argv)
{
  read_json_data("employee_data/dep_rnd.json", "rnd");
  read_json_data("employee_data/dep_mark.json", "marketing");
  read_json_data("employee_data/dep_prod.json", "production");

  for (int i = 0; i < n_employees; i++)
  {
    printf("--------------------------------------------\n");
    printf("department: %s\n", employees_s[i].department);
    printf("name      : %s\n", employees_s[i].name);
    printf("job title : %s\n", employees_s[i].job_title);
    printf("pos level : %i\n", employees_s[i].position);
    printf("emp status: %s\n", employees_s[i].emp_status);
    printf("\n");
  }

  memset(opt, 0x00, sizeof(opt));
  memset(buff_opt, 0x00, sizeof(buff_opt));

  printf("--------------------------------------------\n");
  printf("Choose the filter using option number\n");
  printf("1. Position level\n");
  printf("2. Job title\n");
  printf("3. Employment status\n");
  printf("4. Department\n");
  printf("5. Name\n");
  printf("--------------------------------------------\n\n");

  printf("input ->");
  fgets(opt, MAX_INPUT, stdin);

  if ((strlen(opt) > 0) && (opt[strlen(opt) - 1] == '\n'))
    opt[strlen(opt) - 1] = '\0';

  switch (opt[0])
  {
  case '1':
    printf("Please enter the position level\n");
    printf("1. level 1\n");
    printf("2. level 2\n");
    printf("3. level 3\n");
    printf("4. level 4\n");
    printf("5. level 5\n");
    printf("input ->");
    fgets(buff_opt, MAX_INPUT, stdin);
    if ((strlen(buff_opt) > 0) && (buff_opt[strlen(buff_opt) - 1] == '\n'))
      buff_opt[strlen(buff_opt) - 1] = '\0';
    get_position_level(buff_opt);
    break;

  case '2':
    printf("Please enter the Job title\n");
    printf("input ->");
    fgets(buff_opt, MAX_INPUT, stdin);
    if ((strlen(buff_opt) > 0) && (buff_opt[strlen(buff_opt) - 1] == '\n'))
      buff_opt[strlen(buff_opt) - 1] = '\0';
    get_job_title(buff_opt);
    break;

  case '3':
    printf("Please enter the Employment status\n");
    printf("1. Contract\n");
    printf("2. Casual\n");
    printf("3. Part-Time\n");
    printf("4. Full-Time\n");
    printf("input ->");
    fgets(buff_opt, MAX_INPUT, stdin);
    if ((strlen(buff_opt) > 0) && (buff_opt[strlen(buff_opt) - 1] == '\n'))
      buff_opt[strlen(buff_opt) - 1] = '\0';
    get_employment_status(buff_opt);
    break;

  case '4':
    printf("Please enter the Department\n");
    printf("1. Marketing\n");
    printf("2. Production\n");
    printf("3. RnD\n");
    printf("input ->");
    fgets(buff_opt, MAX_INPUT, stdin);
    if ((strlen(buff_opt) > 0) && (buff_opt[strlen(buff_opt) - 1] == '\n'))
      buff_opt[strlen(buff_opt) - 1] = '\0';
    get_department(buff_opt);
    break;

  case '5':
    printf("Please enter Employee name\n");
    printf("input ->");
    fgets(buff_opt, MAX_INPUT, stdin);
    if ((strlen(buff_opt) > 0) && (buff_opt[strlen(buff_opt) - 1] == '\n'))
      buff_opt[strlen(buff_opt) - 1] = '\0';
    get_name(buff_opt);
    break;

  default:
    printf("There is no such as option\n");
    break;
  }
  if (employees_s)
  {
    free(employees_s);
    employees_s = NULL;
  }

  return 0;
}