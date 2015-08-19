#pragma save_binary
inherit "/std/room/room";

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_new_light(10);
  set_short("Sky");
  set_long("You are uhm, in the sky. Peer.\n");
  add_exit("/areas/Lars/Lars/o/Rooms/church","church");
}

