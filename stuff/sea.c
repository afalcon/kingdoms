inherit "/std/room/room";

reset(arg) {
  if (arg) return;
  set_light(1);
  short_desc = "Swimming at sea";
  long_desc = "You are swimming for your life at sea.\n";
  dont_clean_up =1;
}
