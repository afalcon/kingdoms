#pragma strict_types
inherit "/std/obj/treasure";

int id, line_count;

string *lines = ({
  "Come they told me ",2.0,
  "pa rum pum pum pum",5.0,
  "A new born King to see, ",2.0,
  "pa rum pum pum pum",5.0,
  "Our finest gifts we bring ",2.0,
  "pa rum pum pum pum",5.0,
  "To lay before the King ",2.0,
  "pa rum pum pum pum ",2.0,
  "rum pum pum pum ",2.0,
  "rum pum pum pum",5.0,
  "So to honor Him ",2.0,
  "pa rum pum pum pum, ",2.0,
  "when we come.",5.0,
  "Little Baby ",2.0,
  "pa rum pum pum pum",5.0,
  "I am a poor boy too, ",2.0,
  "pa rum pum pum pum",5.0,
  "I have no gift to bring ",2.0,
  "pa rum pum pum pum",5.0,
  "That's fit to give our King ",2.0,
  "pa rum pum pum pum ",2.0,
  "rum pum pum pum ",2.0,
  "rum pum pum pum",5.0,
  "Shall I play for you! ",2.0,
  "pa rum pum pum ",2.0,
  "on my drum.",5.0,
  "Mary nodded ",2.0,
  "pa rum pum pum pum",5.0,
  "The ox and lamb kept time ",2.0,
  "pa rum pum pum pum",5.0,
  "I played my drum for Him ",2.0,
  "pa rum pum pum",5.0,
  "I played my best for Him ",2.0,
  "pa rum pum pum pum ",2.0,
  "rum pum pum pum ",2.0,
  "rum pum pum pum",5.0,
  "Then He smiled at me ",2.0,
  "pa rum pum pum pum ",2.0,
  "me and my drum.",5.0,
});

int init_arg(void) {
  tell_object(this_player(), "Cloned: a little blue drum.\n");
  return 1;
}

void reset(int arg) {
  if (arg) return;
  set_name("drum");
  set_short("a little blue drum");
  set_long("It's a happy little blue birthday drum. :o)\n"+
           "Commands: playdrum, stopdrum.\n");
  set_value(1);
  set_weight(0);
}

int drop(void) { return 1; }
int get(void) { return 0; }

void init(void) {
  ::init();
  add_action("do_drum","playdrum");
  add_action("do_nodrum","stopdrum");
}

string find_gender(object ob)
{
  switch(ob->query_gender())
  {
    case 0:
      return "thingie";
      break;
    case 1:
      return "boy";
      break;
    case 2:
      return "girl";
      break;
  }
}

int do_drum(void) {
  object me = environment(this_object());
  if(id) {
    write("Yer already playin', silly.\n");
    return 1;
  }
  write("Ye suddenly turn into a little drummer "+find_gender(me)+".\n");
  tell_room(environment(me),me->query_name()+" suddenly turns into a little drummer "+find_gender(me)+".\n");
  id = set_alarm(0.0, 0.0, "play_song");
  return 1;
}

int do_nodrum(void) {
  object me = environment(this_object());
  if(id) {
    remove_alarm(id);
    id = 0;
    write("Ye stop playin' :o(\n");
    tell_room(environment(me),me->query_name()+" stops playin' :o(\n");
    return 1;
  }
  else {
    write("Ye goofball! Ye aren't playin', silly!\n");
    return 1;
  }
}

void play_song(void) {
  if (line_count < sizeof(lines)) {
    tell_room(environment(environment(this_object())), lines[line_count]+"\n");
    line_count += 1;
    id = set_alarm(lines[line_count], 0.0, "play_song");
    line_count += 1;
  }
  else {
    remove_alarm(id);
    id = 0;
    line_count = 0;
    id = set_alarm(0.0, 0.0, "play_song");
  }
}

string query_auto_load(void) {
  return "/wiz/b/bart/objects/drum:";
}

