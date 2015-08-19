#include "/wiz/b/bart/include/defines.h"
#include <levels.h>
#define EASTERN 6
#define CENTRAL 7
#define MOUNTAIN 8
#define PACIFIC 9
#define MAGIC 3600
#define DO(X) if(err = catch(X)) write(err)
#define CAP(X) capitalize(X)
inherit "/std/clone/bag";

mixed err;
int total, tot_files, tot_dirs;
string failed_file = "";
string cre1; object cre2;
int adjust = 0;
string timezone = "local";
status noforce = 0;
status unsnoopable = 0;

init_arg(str) {
  tell_object(this_player(), "Cloned: a little blue hat.\n");
  do_timezone(str);
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("hat");
  set_alias("thisisbartshatblahblahblah");
  set_weight(0);
  set_value(0);
}

short() {
  return "a little blue hat";
}

long() {
  write(
"****************************** Hat commands *****************************\n"+
" Check <who> <fun> - checks the return values for functions.             \n"+
" bag <who>         - stuffs someone in a bag...er, in the hat.           \n"+
" back              - moves the owner back to the last room.              \n"+
" date              - shows current time & date, unix style.              \n"+
" dates             - shows time / date for different time zones.         \n"+
" du                - shows disk usage stats in a directory.              \n"+
" flex!             - raises your stats to the maximum value.             \n"+
" fresh             - compiles the current room, w/o moving you.          \n"+
" goback            - takes you from the void to the old room that failed.\n"+
" loaddir           - loads all files in the current directory.           \n"+
" noforce (or nf)   - prevents other wizards from forcing you.            \n"+
" nosnoop (or ns)   - discourages others from snooping you.               \n"+
" owho              - shows the good old who command.                     \n"+
" pwiz/psay/ptell   - lets you communicate in piglatin.                   \n"+
" renew             - destructs an object and clones a new one.           \n"+
" swiz/ssay/stell   - lets you communicate in sheeplatin.                 \n"+
" timezone <zone>   - changes the time zone used in <date/s>.             \n"+
" updir             - updates all files in the current directory.         \n"+
" yesforce (or yf)  - allows other wizards to force you.                  \n"+
" yessnoop (or ys)  - stops the spam.                                     \n"+
"*************************************************************************\n");
  if(this_player()->query_real_name() == "bart") {
    write("Special commands for Bart: ex <code>\n");
  }
  return 1;
}

extra_look() { 
  if (environment(this_object())->query_real_name() == "bart") {
    return 
"             WW \n"+
"            /__\\ \n"+
"           | oo | \n"+
"          (|_()_|) \n"+
"            \\__/ \n"+
"           /|\\/|\\ \n"+
"          ||||||||        Bert says: R.E.M. rules! They rule!\n"+
"          ||||||||\n"+
"         .||||||||";
}
  else {
    return environment(this_object())->query_name()+" is an R.E.M. fan";
  }
}

int drop() { return 1; }
int get() { return 0; }

void init() {
  if (this_player() &&
      this_player()->query_level() < NEWBIE &&
      environment(this_object()) == this_player()) {
    this_object()->destroy();
    return;
  }
  if(this_player()->query_real_name() == "bart") {
    add_action("do_exec", "ex");
  }
  if(this_player()->query_level() > NEWBIE) {
    add_action("do_Check", "Check");
    add_action("do_bag","bag");
    add_action("do_back","back");
    add_action("do_date","date");
    add_action("do_dates","dates");
    add_action("do_du", "du");
    add_action("do_flex", "flex!");
    add_action("do_fresh", "fresh");
    add_action("do_goback", "goback");
    add_action("do_loaddir", "loaddir");
    add_action("do_look","look");
    add_action("prevent_force","noforce");
    add_action("prevent_force","nf");
    add_action("do_nosnoop","nosnoop");
    add_action("do_nosnoop","ns");
    add_action("do_who", "owho");
    add_action("do_psay","psay");
    add_action("do_ptell","ptell");
    add_action("do_ptell","pask");
    add_action("do_pwiz","pwiz");
    add_action("do_renew","renew");
    add_action("do_ssay","ssay");
    add_action("do_stell","stell");
    add_action("do_stell","sask");
    add_action("do_swiz","swiz");
    add_action("do_timezone","timezone");
    add_action("do_updir", "updir");
    add_action("do_wear", "wear");
    add_action("allow_force","yesforce");
    add_action("allow_force","yf");
    add_action("do_yessnoop","yessnoop");
    add_action("do_yessnoop","ys");
    add_action("no_force", "", 1);
  }
}

int do_wear(string str) {
  if(!str) {
    return 0;
  }
  if(str == "little blue hat" ||
     str == "blue hat" ||
     str == "hat") {
    notify_fail("The little blue hat is too small for your big fat head.\n");
    return 0;
  }
  return 0;
}

int sort_by_level(object u1, object u2) {
   int level1, level2;
   string name1, name2;
   
   level1 = (int)u1->query_level();
   level2 = (int)u2->query_level();
   if (level1 == level2) {
      name1 = (string)u1->query_name();
      name2 = (string)u2->query_name();
      if (!name1) name1 = "<login>";
      if (!name2) name2 = "<login>";
      if (name1 == name2)
         return 0;
      if (name1 < name2)
         return -1;
      else
         return 1;
   }
   if (level1 > level2)
      return -1;
   else
      return 1;
}

do_Check(str) {
  string *return_value;
  object ob;
  int    arr;
  string blah, what, func, arg, crap, name, lev, loc, tmp_loc, ret, tmp_ret;
  int    size, i, func_type, iarg;

  if (!str || str == "") {
    write("Usage: Check <object> <function> [arg]\n"+
          "This function will call the routine <function> in all objects "+
          "in <object>'s inventory. It will list the return values for "+
          "each call. There are five special <object>'s: "+
          "'all', 'mortals', 'immortals', 'wizards' and 'arches'.\n");
    return 1;
  }
    
  if (sscanf(str, "-e %s %s", what, crap) == 2)
    func_type = 1;
  else if(sscanf(str, "%s %s", what, crap) != 2)
    return do_Check(0);		/* get usage */
    
  str = crap;
  if (sscanf(str, "%s %s", func, arg) != 2)
    func = str;

  if (func == "command") {
    write("No. No. No, you can use this tool to cheat.\n");
    return 1;
  }

  if (func == "destroy") {
    write("No. No. No, you can use this tool to cheat.\n");
    return 1;
  }
    
  if (sscanf(func, "set%s", blah) == 1) {
    write("No. No. No, you can use this tool to cheat.\n");
    return 1;
  }
    
  if (what == "all") {
    arr = users();
  } 
  else if (what == "mortals" || what == "players") {
    arr = filter(users(), "ismortal", this_object());
  } 
  else if (what == "immortals") {
    arr = filter(users(), "isimmortal", this_object());
  } 
  else if (what == "wizards" || what == "wiz") {
    arr = filter(users(), "iswiz", this_object());
  } 
  else if (what == "arches" || what == "arch") {
    arr = filter(users(), "isarch", this_object());
  } 
  else {
    ob = find_object(what);
    if (!ob) {
      write("Couldn't find '" + what + "'.\n");
      return 1;
    }
    arr = all_inventory(ob);
  }
    
  if (!pointerp(arr) || sizeof(arr) == 0) {
    write(what +" contains no objects.\n");
    return 1;
  }
    
  if (!arg || arg == "")
    return_value = Check(arr, func, 0, func_type);
  else if (sscanf(arg, "%d", iarg))
    return_value = Check(arr, func, iarg, func_type);
  else
    return_value = Check(arr, func, arg, func_type);
    
  size = sizeof(return_value);
    
  if (size) {
    write("Function: "+str+"\n");
    write(sprintf("%|6s %|14s %|30s %s\n", "Lev", "Name", "Location", "Result"));
    for (i = 0; i < size; ++i) {
      if(return_value[i]->query_invis()) {
        name = "("+capitalize(return_value[i]->query_real_name())+")";
      }
      else {
        name = capitalize(return_value[i]->query_real_name());
      }
      lev = "["+return_value[i]->query_level()+"]";
      if (!name) {
        name = "Login";
      }
      if ((environment(return_value[i]))) {
        loc = file_name(environment(return_value[i]));
        if (sscanf(loc,"/players/%s",tmp_loc) == 1) {
          loc = "~"+ tmp_loc;
        }
        if (sscanf(loc,"/room/%s",tmp_loc) == 1) {
          loc = tmp_loc;
        }
      }
      else {
        loc = "Unknown";
      }
      ret = return_value[++i];
      if(stringp(ret)) {
        if (sscanf(ret,"players/%s",tmp_ret) == 1) {
          ret = "~"+ tmp_ret;
        }
        if (sscanf(ret,"room/%s",tmp_ret) == 1) {
          ret = tmp_ret;
        }
      }
      if(strlen(loc) < 30) {
        write(sprintf("%-6s %|14s %|29s %-=25O\n", lev, name, loc, ret));
      }
      else {
        write(sprintf("%-6s %|14s %-=29s %-=25O\n", lev, name, loc, ret));
      }
    }
  }
  return 1;
}

/*
 * obj    -> an array of objects
 * myfunc -> the function all the objects will be called *with*
 * myarg  -> the argument to myfunc if func_type is false
 * func_type -> If true an efun is called, else an lfun is called.
 *
 * If 'func_type' is true an efun will be called with 'obj[i]' as argument,
 * else a local function 'myfunc' in 'obj[i]' will be called with 'myarg'
 * as argument.
 */
Check(obj, myfunc, myarg, func_type) {
  object return_value;
  int i, size;
  string myerror;
   
  if (!pointerp(obj) || sizeof(obj) == 0 || !myfunc || myfunc == "")
    return_value = ({});
  else {
/*
  obj = sort_array(obj, "sort_by_level", this_object());
*/
  size = sizeof(obj);
  return_value = allocate(size*2);
  if (func_type) {
    string myfile;
    object fileob;
	    
    myfile = get_temp_file_name();

    /* Destruct the object identifying to 'myfile' if one
     * is already loaded into memory
     */
    if ((fileob = find_object(myfile)))
      fileob->destroy();

    write_file(myfile, "myfunc(obj) { return " + myfunc + "(obj); }\n");

    /* load the new file
     */
    myerror = catch(call_other(myfile, "??"));
    rm(myfile);
/*
    if(TEST(myerror)) {
      Error("Check2:"+myerror);
      return ({});
    }
*/
    fileob = find_object(myfile);
    for(i = 0; i < size; ++i) {
      return_value[i*2]   = obj[i];
      return_value[i*2+1] = call_other(fileob, "myfunc", obj[i]);
    }
    /* clean up */
    fileob->destroy();
    } 
  else 
    for (i = 0; i < size; ++i) {
      return_value[i*2]   = obj[i];
      return_value[i*2+1] = call_other(obj[i],myfunc, myarg);
    }
  }
  return return_value;
}

isarch(ob) { return ob->query_level() >= ARCH; }

iswiz(ob) { return ob->query_level() >= MAXMORTAL &&
                   ob->query_level() < ARCH; }

ismortal(ob) { return ob->query_level() <= MAXMORTAL; }

isimmortal(ob) { return ob->query_level() > MAXMORTAL; }

get_temp_file_name() {
    int i;

    while(file_size("/tmp/Clean"+i+".c") != -1)
	++i;
    return "/tmp/Clean"+i+".c";
}

static do_updir() {
  object ob;
  string dir;
  string *files;
  int i;

  dir = "/" + this_player()->query_path();
  files = get_dir(dir + "/*.c") + get_dir(dir + "/*.o");
  for(i=0; i<sizeof(files); i++) {
    ob = find_object(dir+"/"+files[i][0..-3]);
    if(ob) {
      write("Updating "+dir+"/"+files[i]+"\n");
	    ob->destroy();
    }
  }
  return 1;
}

static do_loaddir() {
  object ob;
  string dir;
  string *files;
  int i;

  dir = "/" + this_player()->query_path();
  files = get_dir(dir + "/*.c") + get_dir(dir + "/*.o");
  for(i=0; i<sizeof(files); i++) {
    ob = find_object(dir+"/"+files[i][0..-3]);
    if(!ob) {
      write("Loading "+dir+"/"+files[i]+"\n");
      DO((dir+"/"+files[i][0..-3])->load_me());
    }
  }
  return 1;
}

do_renew(string str) {
  string file;
  object thingy, env;
  if(!str) {
    notify_fail("Syntax: renew <object>\n");
    return 0;
  }
  if(thingy = present(str,environment(this_object()))) {
    env = environment(this_object());
  }
  else {
    if(thingy = present(str,environment(environment(this_object())))) {
      env = environment(environment(this_object()));
    }
  }
  if(!thingy) {
    write("There's no "+str+" here, dude.\n");
    return 1;
  }
  if(interactive(thingy)) {
    write("Hehe, you're evil.\n");
    return 1;
  }
  if(thingy->is_room()) {
    write("Hehe, use \"fresh\" instead.\n");
    return 1;
  }
  file = explode(file_name(thingy)+"#","#")[0];
  transfer(thingy,"/wiz/b/bart/rooms/void");
  write("Destroying: "+file_name(thingy)+".\n");
  thingy->destroy();
  write("Updating: "+file+".\n");
  file->destroy();
  thingy = 0;
  DO(file->load_me());
  if (thingy = clone_object(file)) {
    if(env != this_player()) {
      write("Cloning: "+file_name(thingy)+".\n");
    }
    move_object(thingy,env);
    return 1;
  }
  else {
    write("Error loading "+file+".\n");
    return 1;
  }
}


do_who(str) {
  return "/wiz/b/bart/objects/who"->do_who(str);
}

do_flex() {
  int num;
  int max_stat = 80;

  num = this_player()->query_str();
  this_player()->add_tmp_str(max_stat - num);
  num = this_player()->query_dex();
  this_player()->add_tmp_dex(max_stat - num);
  num = this_player()->query_int();
  this_player()->add_tmp_int(max_stat - num);
  num = this_player()->query_con();
  this_player()->add_tmp_con(max_stat - num);
  num = this_player()->query_siz();
  this_player()->add_tmp_siz(max_stat - num);
  num = this_player()->query_dic();
  this_player()->add_tmp_dic(max_stat - num);
  num = this_player()->query_qui();
  this_player()->add_tmp_qui(max_stat - num);
  num = this_player()->query_mem();
  this_player()->add_tmp_mem(max_stat - num);
  num = this_player()->query_elo();
  this_player()->add_tmp_elo(max_stat - num);
  num = this_player()->query_res();
  this_player()->add_tmp_res(max_stat - num);
  this_player()->heal_self(10000);
  write("You find a telephone booth and put on your Superman costume.\n");
  return 1;
}

static int do_fresh() {
  object room;
  object *stuff;
  object *people;
  string file;
  int i;

  room = environment(this_player());

  if(living(room) && interactive(room)) {
    write("Don't think that's a good idea....\n");
    return 1;
  }

  file = explode(file_name(room)+"#","#")[0];

  if (file_name(room) == "/wiz/b/bart/rooms/void") {
    write("Uhm, no.\n");
    return 1;
  }

  write("Freshing: " + file_name(room) + "\n");
  stuff = all_inventory(room);

  "/wiz/b/bart/rooms/void"->load_me();
  people = ({ });

  for (i = 0; i < sizeof(stuff); i++) {
    if(living(stuff[i]) && !(stuff[i]->query_npc())) {
      transfer(stuff[i],"/wiz/b/bart/rooms/void");
      people += ({ stuff[i] });
    }
  }

  room->destroy();
  DO(file->load_me());
  if (room = find_object(file)) {
    for (i = 0; i < sizeof(people); i++) {
      transfer(people[i],room);
    }
    tell_room(room,"The ground shivers for a moment.\n");
    return 1;
  }
  else {
    failed_file = file;
    tell_room("/wiz/b/bart/rooms/void","Dooh!  Someone screwed up.  Type \"church\" to get out, or \"goback\", the one who freshed should type it, after fixing the bug.\n");
    return 1;
  }
}

do_goback() {
  object room;
  string file = failed_file;
  if(!file) {
    write("You can't use this command until you screw up.\n");
    write("So, what are you waiting for?\n");
    return 1;
  }
  if (file_name(environment(this_player())) == "/wiz/b/bart/rooms/void") {
    DO(file->load_me());
    if (room = find_object(file)) {
      transfer(this_player(),room);
      tell_room(room,"Moved to your previous buggy room.\n");
      failed_file == "";
      return 1;
    }
    else {
      write("The room still has some bugs.\nType \"church\" to get out, or \"goback\" after fixing the bug.\n");
      return 1;
    }
  }
  else {
    write("You are not in the void, so you can't use this command.\n");
    return 1;
  }
}

static do_du() {
  int i;
  string *list;
  string arg, path;
  arg = "/"+this_player()->query_path()+"/*";
  path = "/"+this_player()->query_path()+"/";
  total = 0;
  tot_files = 0;
  tot_dirs = 0;
  list = get_dir(arg);
  for (i = 0; i < sizeof(list); i++) {
    if(list[i] == "." || list[i] == "..") {
      total = total;
    }
    else {
      if(file_size(path+list[i]) == -2) {
        tot_dirs++;
        total += 512;
      }
      else {
        tot_files++;
        total += file_size(path+list[i]);
      }
    }
  }
  write("Disk usage: "+total/1024+"."+(total%1024)/10+" kbytes in "+tot_files);
  if(tot_files == 1) {
    write(" file and ");
  }
  else {
    write(" files and ");
  }
  write(tot_dirs);
  if(tot_dirs == 1) {
    write(" directory.\n");
  }
  else {
    write(" directories.\n");
  }
  return 1;
}

do_bag(str) {
  object bagged;
  if(!str) {
    notify_fail("Oops!\n");
    return 0;
  }
  str = lower_case(str);
  if(str == "bart") {
    write("Oops!\n");
    return 1;
  }
  bagged = find_player(str);
  if(!bagged) {
    write("Can't find "+capitalize(str)+", dude.\n");
    return 1;
  }
  else {
    transfer(bagged, this_object());
    write("Moved "+capitalize(bagged->query_real_name())+" to a little blue hat.\n");
    say(this_player()->query_name()+" stuffs "+capitalize(bagged->query_real_name())+" in "+this_player()->query_possessive()+" little blue hat.\n");
    return 1;
  }
}

do_back() {
  if(this_player()->query_last_room()) {
    transfer(this_player(),this_player()->query_last_room());
  }
  else {
    transfer(this_player(),"/areas/Lars/Lars/o/Rooms/church");
  }
  write("Ok.\n");
  return 1;
}

do_look() {
  if(present(this_player(),this_object())) {
    write("Hehe, don't get mad, get bagged.\n");
    write("Type \"back\" to get back to your previous room.\n");
    return 0;
  }
  return 0;
}

int allow_force() {
  noforce = 0;
  write("Anti-force turned off.\n");
  write("You can now be forced.\n");
  return 1;
}

int prevent_force() {
  noforce = 1;
  write("Anti-force turned on.\n");
  write("No one can force you now.\n");
  return 1;
}

int no_force(string s) {
  if(noforce) {
    if (this_interactive() != this_player()) {
      write(this_interactive()->query_real_name()+" tried to force you to do something..."+query_verb()+" "+s+"\n");
      tell_object(this_interactive(), "\a\a\aForcing "+CAP(this_player()->query_real_name())+" isn't cool! =\(\n");
      return 1;
    }
  }
}

do_nosnoop() {
  if(unsnoopable) {
    write("The anti-snooper is already turned on, dude.\n");
    return 1;
  }
  write("Anti-snooper turned on.\n");
  set_alarm(1.0, 0.0, "display_spam");
  return 1;
}

do_yessnoop() {
  if(unsnoopable) {
    remove_alarm(unsnoopable);
    unsnoopable = 0;
    write("Anti-snooper turned off.\n");
    return 1;
  }
  else {
    write("The anti-snooper wasn't turned on, dude.\n");
    return 1;
  }
}

display_spam() {
  write(read_file("/wiz/b/bart/doc/snoop"));
  unsnoopable = set_alarm(20.0, 0.0, "display_spam");
}

do_psay(str) {
  int i;
  object *people;
  string letter, word, original, result, last;
  if(!str) {
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))];
    word = word+letter+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    word = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    word = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    word = str[1..strlen(str)-2];
  }
  word = word+letter+"a";
  word = lower_case(word);
  result += word;
  write("You mumble: "+result+""+last+"\n");
  say(CTPQN+" mumbles: "+result+""+last+"\n");
  people = all_inventory(environment(this_player()));
  for (i = 0; i < sizeof(people); i++) {
    if((present("thisisbartshatblahblahblah",people[i]) ||
       present("piglatinlanguage",people[i])) &&
       this_player() != people[i]) {
      tell_object(people[i],CTPQN+"'s piglatin roughly translates to: \""+original+"\"\n");
    }
  }
  return 1;
}

do_ptell(str) {
  int i;
  object target;
  string letter, last, result, original, who, word;
  if(!str) {
    return 0;
  }
  if(sscanf(str,"%s %s", who, str) != 2) { 
    write(CAP(query_verb())+" who?\n");
    return 1;
  }
  target = find_living(lower_case(who));
  if(!target) {
    write(CAP(who)+" is not here.\n");
    return 1;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))];
    word = word+letter+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    word = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    word = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    word = str[1..strlen(str)-2];
  }
  word = word+letter+"a";
  word = lower_case(word);
  result += word;
  if(this_player()->query_talk_pool() < 5) {
    write("You are low on talk points.\n");
    return 1;
  }
  if(target->query_level() <= MAXMORTAL &&
     this_player()->query_level() <= MAXMORTAL) {
    this_player()->add_talk_pool(-5);
  }
 
  write("You "+query_verb()+" "+target->query_name()+": "+result+""+last+"\n");
  tell_object(target, CTPQN+" "+query_verb()+"s you: "+result+""+last+"\n");
  if(present("thisisbartshatblahblahblah",target) || present("piglatinlanguage",target)) {
    tell_object(target,CTPQN+"'s piglatin roughly translates to: \""+original+"\"\n");
  }
  return 1;
}

do_pwiz(str) {
  int i;
  object *wizzies;
  string letter, last, result, original, who, word;
  if(!str) {
    notify_fail("Pwiz what?\n");
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))];
    word = word+letter+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    word = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    word = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    word = str[1..strlen(str)-2];
  }
  word = word+letter+"a";
  word = lower_case(word);
  result += word;

  wizzies = users();

  for (i = 0; i < sizeof(wizzies); i++) {
    if (wizzies[i]->query_level() > MAXMORTAL &&
        wizzies[i]->member_chatline("wiz")) {
      tell_object(wizzies[i], "[Wiz]: "+CTPQN+" mumbles: "+result+""+last+"\n");
      if(present("thisisbartshatblahblahblah",wizzies[i]) || present("piglatinlanguage",wizzies[i])) {
        tell_object(wizzies[i], CTPQN+"'s piglatin roughly translates to: \""+original+"\"\n");
      }
    }
  }
  return 1;
}

do_ssay(str) {
  int i;
  object *people;
  string last, letter, original, result, tmpword, word;
  if(!str) {
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))/2];
    tmpword = word[(strlen(word))/2..(strlen(word))];
    word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))/2];
  tmpword = str[(strlen(str))/2..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    tmpword = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    tmpword = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    tmpword = str[1..strlen(str)-2];
  }
  word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a";
  word = lower_case(word);
  result += word;
  write("You mumble: "+result+""+last+"\n");
  say(CTPQN+" mumbles: "+result+""+last+"\n");
  people = all_inventory(environment(this_player()));
  for (i = 0; i < sizeof(people); i++) {
    if((present("thisisbartshatblahblahblah",people[i]) ||
       present("sheeplatinlanguage",people[i])) &&
       this_player() != people[i]) {
      tell_object(people[i],CTPQN+"'s sheeplatin roughly translates to: \""+original+"\"\n");
    }
  }
  return 1;
}

do_stell(str) {
  int i;
  object target;
  string letter, last, result, original, tmpword, who, word;
  if(!str) {
    return 0;
  }
  if(sscanf(str,"%s %s", who, str) != 2) { 
    write(CAP(query_verb())+" who?\n");
    return 1;
  }
  target = find_living(lower_case(who));
  if(!target) {
    write(CAP(who)+" is not here.\n");
    return 1;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))/2];
    tmpword = word[(strlen(word))/2..(strlen(word))];
    word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))/2];
  tmpword = str[(strlen(str))/2..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    tmpword = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    tmpword = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    tmpword = str[1..strlen(str)-2];
  }
  word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a";
  word = lower_case(word);
  result += word;
  if(this_player()->query_talk_pool() < 5) {
    write("You are low on talk points.\n");
    return 1;
  }
  if(target->query_level() <= MAXMORTAL &&
     this_player()->query_level() <= MAXMORTAL) {
    this_player()->add_talk_pool(-5);
  }
 
  write("You "+query_verb()+" "+target->query_name()+": "+result+""+last+"\n");
  tell_object(target, CTPQN+" "+query_verb()+"s you: "+result+""+last+"\n");
  if(present("thisisbartshatblahblahblah",target) || present("sheeplatinlanguage",target)) {
    tell_object(target,CTPQN+"'s sheeplatin roughly translates to: \""+original+"\"\n");
  }
  return 1;
}

do_swiz(str) {
  int i;
  object *wizzies;
  string letter, last, result, original, tmpword, who, word;
  if(!str) {
    notify_fail("Swiz what?\n");
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))/2];
    tmpword = word[(strlen(word))/2..(strlen(word))];
    word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))/2];
  tmpword = str[(strlen(str))/2..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    tmpword = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    tmpword = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    tmpword = str[1..strlen(str)-2];
  }
  word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a";
  word = lower_case(word);
  result += word;

  wizzies = users();

  for (i = 0; i < sizeof(wizzies); i++) {
    if (wizzies[i]->query_level() > MAXMORTAL &&
        wizzies[i]->member_chatline("wiz")) {
      tell_object(wizzies[i], "[Wiz]: "+CTPQN+" mumbles: "+result+""+last+"\n");
      if(present("thisisbartshatblahblahblah",wizzies[i]) || present("sheeplatinlanguage",wizzies[i])) {
        tell_object(wizzies[i], CTPQN+"'s sheeplatin roughly translates to: \""+original+"\"\n");
      }
    }
  }
  return 1;
}

do_timezone(string str) {
  if(!str) {
    tell_object(environment(this_object()), "Please give an argument for the timezone, valid ones are: \"eastern\", \"central\", \"mountain\", and \"pacific\".\n");
    return 1;
  }
  switch(str) {
    case "eastern":
    case "Eastern":
      adjust = MAGIC * EASTERN;
      break;
    case "central":
    case "Central":
      adjust = MAGIC * CENTRAL;
      break;
    case "mountain":
    case "Mountain":
      adjust = MAGIC * MOUNTAIN;
      break;
    case "pacific":
    case "Pacific":
      adjust = MAGIC * PACIFIC;
      break;
    default:
      str = "local";
      adjust = 0;
      break;
  }
  timezone = lower_case(str);
  tell_object(environment(this_object()), "Timezone set to: "+timezone+".\n");
  return 1;
}

do_date() {
  write(CAP(timezone)+": "+ctime(time()-adjust)+"\n");
  return 1;
}

do_dates(string z) {
  write("Kingdoms: "+environment(this_object())->kingdoms_ctime()+"\n");
  write("Local:    "+ctime(time())+"\n");
  write("Eastern:  "+ctime(time()-(MAGIC*EASTERN))+"\n");
  write("Central:  "+ctime(time()-(MAGIC*CENTRAL))+"\n");
  write("Mountain: "+ctime(time()-(MAGIC*MOUNTAIN))+"\n");
  write("Pacific:  "+ctime(time()-(MAGIC*PACIFIC))+"\n");
  return 1;
}

do_exec(string str) {
  mixed ret;
  string err, file, inc;
    
  if(!str) {
    return notify_fail("Usage:  ex <nerdy code> \n");
  }

  file = "/wiz/"+this_player()->query_real_name()[0..0]+"/"+this_player()->query_real_name()+"/tmpcalc.c";

  if(str || file_size(file) == -1) {
    rm(file);
    if (find_object(file)) {
      destruct(find_object(file));
    }
    inc = "/wiz/"+this_player()->query_real_name()[0..0]+"/"+this_player()->query_real_name()+"/defines.h";
    if (file_size(inc) > 0) {
      write_file(file, "#include \"/" + inc + "\"\n");
    }
    write_file(file,
      "inherit \"\/std\/obj\/treasure\";\n"+
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
  return "/wiz/b/bart/tools/hat:"+timezone;
}

