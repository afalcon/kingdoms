#include "/include/levels.h"
#define DO(X) if(err = catch(X)) write(err)
#define CAP(X) capitalize(X)
inherit "/std/obj/treasure";

mixed err;

init_arg() {
  tell_object(this_player(), "Cloned: a little blue exec thingy.\n");
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("exec");
  set_short("a little blue exec thingy");
  set_long("Syntax: ex <code>\n");
  set_weight(1);
  set_value(1);
}

int drop() { return 1; }
int get() { return 0; }


init() {
  if(environment(this_object())->query_real_name() != "bart") {
    write("A little blue cow says: Moo. Make yer own little blue exec thingy.\n");
    this_object()->destroy();
  }
  ::init();
  if(this_player()->query_real_name() == "bart") {
    add_action("do_exec", "ex");
  }
}

do_exec(string str) {
  mixed ret;
  string err, file, inc;
    
  if(!str) {
    return notify_fail("Usage:  ex <nerdy code> \n");
  }

  file = "/players/"+this_player()->query_real_name()+"/tmpcalc.c";

  if(str || file_size(file) == -1) {
    rm(file);
    if (find_object(file)) {
      destruct(find_object(file));
    }
    inc = "/players/"+this_player()->query_real_name()+"/defines.h";
    if (file_size(inc) > 0) {
      write_file(file, "#include \"/" + inc + "\"\n");
    }
    write_file(file,
      "inherit \"\/obj\/treasure\";\n"+
      "\n"+
      "query_calc(){ "+str+" }\n");
    }
    if(err=catch(ret = file->query_calc())) {
      write(err);
    }
    write("Ok.\n");
    rm(file);
    return 1;
}

query_auto_load() {
  return "/wiz/b/bart/tools/exec:";
}

