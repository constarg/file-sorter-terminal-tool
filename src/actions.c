#include <actions.h>
#include <stdio.h>

void set_check_interval(const char *n_value)
{
  printf("set check\n");
}

void set_parse_interval(const char *n_value)
{
  printf("set parse\n");
}

void set_default_dir_path(const char *n_path)
{
  printf("set default\n");
}

void set_enable_default_dir(const char *n_state)
{
  printf("set enable\n");
}

void set_debug_log(const char *n_state)
{
  printf("set debug\n");
}

void add_check(const char *path)
{
  printf("add check\n");
}

void add_target(const char *ext, const char *path)
{
  printf("add target\n");
}

void add_exclude(const char *ext, const char *path)
{
  printf("add exclude\n");
}

void remove_check(const char *row)
{
  printf("remove check\n");
}

void remove_target(const char *row)
{
  printf("remove_target");
}

void remove_exclude(const char *row)
{
  printf("remove exclude");
}

void list_options()
{
  printf("list opt");
}

void list_checks()
{
  printf("list check");
}
  
void list_targets()
{
  printf("list targets");
}

void list_excludes()
{
  printf("list excludes");
}
