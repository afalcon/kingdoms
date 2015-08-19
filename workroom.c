#pragma strict_typing
inherit "/std/room/room";

object bart, mousie, doggie, kitty, otter, bear;
object cow;

void reset(int arg) {
  if(!present("mouse")) {
    mousie = make("/areas/Bird/Wonderland/o/Monster/mouse");
  }
}

void create_object()
{
  set_new_light(10);
  set_short("Bart's workroom");
  set_long("\n\n\n\n\n\n\n\n");
  add_property("indoors");
  add_property("no_fight");
  add_exit("/wiz/a/aslan/workroom","down");
  set_skip_obvious(1);
  reset(0);
}

