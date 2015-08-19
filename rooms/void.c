#pragma save_binary
inherit "/std/room/room";

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_new_light(10);
  set_short("Void");
  set_long("You are uhm, in the void. This is where people end up when "+
"the someone screws up.  It's also a place where Bart dumps all his useless "+
"crap.\n");
  add_property("indoors");
  add_exit("/areas/Lars/Lars/o/Rooms/church","church");
}

