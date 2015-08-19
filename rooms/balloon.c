#include "/wiz/b/bart/include/defines.h"
inherit "/wiz/b/bart/std/balloon";

reset(arg)
{
  ::reset(arg);
  if (arg) return;
  set_dest("/areas/Northlands/Highlands/o/workroom");
  set_dest2("/wiz/b/bart/workroom");
  set_name_dest("high's workroom");
  set_name_dest2("bart's workroom");
  set_docked_time(100);
  set_fly_time(100);
  set_balloon_name("a happy balloon");
  set_light(1);
  set_short("a happy balloon");
  set_long("This is a happy balloon\n");
  set_skip_obvious(1);
}

