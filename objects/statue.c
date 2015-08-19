inherit "/std/obj/treasure";

reset(arg){
  set_weight(99999);
  set_name("statue");
  set_alias("highlander");
  set_value(0);
  set_short("A statue of Highlander");
  set_long("This is a magnificent statue of Highlander, only he seems to be dressed in a Jack costume.\n");
}

get() { 
  notify_fail("You can't get that, you idiot!\n");
  return 0;
}

init(){
  ::init();
  add_action("do_look","look");
}

do_look(arg){
  if(!arg) {
    return 0;
  }
  if (arg=="costume"||arg=="at costume") {
    write("Seems Highlander wants to be as handsome as Jack!\n");
    say(capitalize(this_player()->query_name())+" looks at the statue.\n");
    return 1;
  }
  if (arg=="under kilt") {
    int hehe = 2 + random(3);
    write("You look under the statue's kilt and discover a thingy that is only "+hehe+" centimeters long!\n");
    say(capitalize(this_player()->query_name())+" looks under the statue's kilt and sees a thingy that is only "+hehe+" centimeters long.\n");
    return 1;
  }
  return 0;
}
