#include <actions.h>
#include <stdio.h>

int set_check_interval(const char *n_value)
{
  printf("set check\n");
}

int set_parse_interval(const char *n_value)
{
  printf("set parse\n");
}

int set_default_dir_path(const char *n_path)
{
  printf("set default\n");
}

int set_enable_default_dir(const char *n_state)
{
  printf("set enable\n");
}

int set_debug_log(const char *n_state)
{
  printf("set debug\n");
}

int add_check(const char *path)
{
  printf("add check\n");
}

int add_target(const char *ext, const char *path)
{
  printf("add target\n");
}

int add_exclude(const char *ext, const char *path)
{
  printf("add exclude\n");
}

int remove_check(const char *row)
{
  printf("remove check\n");
}

int remove_target(const char *row)
{
  printf("remove_target");
}

int remove_exclude(const char *row)
{
  printf("remove exclude");
}

int list_options()
{
  printf("list opt");
}

int list_checks()
{
  printf("list check");
}
  
int list_targets()
{
  printf("list targets");
}

int list_excludes()
{
  printf("list excludes");
}
