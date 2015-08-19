#include "/wiz/b/bart/include/defines.h"
inherit "/wiz/b/bart/std/fishing_pole";
 
reset(arg) {
  if(arg) return;
  set_name("stick");
  set_alias("fishing_pole");
  set_long("A bamboo stick with a piece of string connected to the end.\nAt the end of the string is a hook.  What a primitive looking fishing tool!\n");
  set_value(20);
  set_weight(2);
  set_pole_class(10);
}
