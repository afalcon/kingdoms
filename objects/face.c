#pragma save_binary
inherit "/std/obj/treasure";

init_arg() {
  tell_object(this_player(), "Cloned: a little blue face.\n");
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("face");
  set_short("a little blue face");
  set_long("It's an ugly face.\n");
  set_value(0);
  set_weight(0);
}

int drop() { return 1; }
int get() { return 0; }

init() {
  if(environment(this_object())->query_real_name() != "bart") {
    write("A little blue face says: Hehehe. No, you are too ugly.\n");
    this_object()->destroy();
  }
  ::init();
}

extra_look() { 
  return 
"   |\\/\\/\\/|  \n"+
"   |      |  \n"+
"   |      |  \n"+
"   | (o)(o)  \n"+
"   @      _) \n"+
"    | ,___|                Bart says: R.E.M. rules! They rule!\n"+
"    |   /    \n"+
"    /___\\    \n"+
" ./       \\";
}

query_auto_load() {
  return "/wiz/b/bart/objects/face:";
}

