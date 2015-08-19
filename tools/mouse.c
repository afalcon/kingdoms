#pragma save_binary
#define EASTERN 6
#define CENTRAL 7
#define MOUNTAIN 8
#define PACIFIC 9
#define MAGIC 3600
inherit "/std/obj/treasure";

int adjust;

init_arg() {
  tell_object(this_player(), "Cloned: a little blue mouse.\n");
  adjust = MAGIC * PACIFIC;
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("mouse");
  set_short("a little blue mouse");
  set_long("It's a mickey mouse watch. Type \"date\" or \"dates\" to use it.\n");
  set_value(0);
  set_weight(0);
}

int drop() { return 1; }
int get() { return 0; }

init() {
  if(environment(this_object())->query_real_name() != "bart") {
    if(environment(this_object())->query_real_name() != "aslan") {
      write("A little blue mouse says: Get your own mickey mouse watch!\n");
      this_object()->destroy();
    }
  }
  ::init();
  if(this_player()->query_real_name() == "bart" || 
     this_player()->query_real_name() == "aslan") {
    add_action("do_date","date");
    add_action("do_dates","dates");
  }
}

do_date() {
  write(ctime(time()-adjust)+"\n");
  return 1;
}

do_dates(string z) {
  write("Sweden:   "+ctime(time())+"\n");
  adjust = MAGIC * EASTERN;
  write("Eastern:  "+ctime(time()-adjust)+"\n");
  adjust = MAGIC * CENTRAL;
  write("Central:  "+ctime(time()-adjust)+"\n");
  adjust = MAGIC * MOUNTAIN;
  write("Mountain: "+ctime(time()-adjust)+"\n");
  adjust = MAGIC * PACIFIC;
  write("Pacific:  "+ctime(time()-adjust)+"\n");
  return 1;
}

query_auto_load() {
  return "/wiz/b/bart/tools/mouse:";
}

