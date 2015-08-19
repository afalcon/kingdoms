#define HM "/wiz/b/bart/rooms/harbor_master"
#define CTPQN capitalize(this_player()->query_real_name())
#define GM "/wiz/b/bart/rooms/galley_master"
#define SEA_ROOM "/wiz/b/bart/rooms/sea"
#define MAX_SPEED 10
#define MIN_SPEED 1
#define POINT_BLANK_RANGE 10.0
#define SHORT_RANGE 20.0
#define MEDIUM_RANGE 30.0
#define LONG_RANGE 38.0
inherit "/std/room/room";

status aimed, fired;

string galley_owner = "";
string galley_shipname = "";
int galley_hp = 0;
int galley_wc = 0;
int galley_ac = 0;
int galley_vertical = 0; 
int galley_horizontal = 0; 
int galley_aim_ver = 0; 
int galley_aim_hor = 0; 
string galley_aim_dir = ""; 
int galley_aim_dist = 0; 
int galley_speed = 0; 
string galley_direction = "";
int galley_cannons = 0;
int galley_cannonballs = 0;
int galley_aimers = 0;
int galley_firers = 0;
int galley_rowers = 0;
int galley_scanners = 0;
int galley_crew = 0;
string galley_frequency = "";
string galley_mode = "";

int do_sail_id, 
    check_spin_id, 
    move_to_target_id, 
    do_aim_id, 
    check_aim_id,
    do_scan_id;

reset(arg) {
  ::reset(arg);
  if (arg)  return;
  aimed = 0;
  fired = 0;
  set_light(1);
  set_short("a galley");
  set_long("You are in a galley.\n");
  set_skip_obvious(1);
  efun::move_object("/wiz/b/bart/rooms/void");
  set_alarm(1.0, 0.0, "add_me", this_object());
}

add_me(object ob) {
  GM->add_ship(ob);
  return 1;
}

set_owner(string str) { galley_owner = str; }
set_shipname(string str) { galley_shipname = str; }
set_hp(int num) { galley_hp = num; }
set_wc(int num) { galley_wc = num; }
set_ac(int num) { galley_ac = num; }
set_location(int hor, int vert) {
  galley_horizontal = hor;
  galley_vertical = vert;
}
set_speed(int num) { galley_speed = num; }
set_direction(string str) { galley_direction = str; }
set_cannons(int num) { galley_cannons = num; }
set_cannonballs(int num) { galley_cannonballs = num; }
set_aimers(int num) { galley_aimers = num; }
set_firers(int num) { galley_firers = num; }
set_rowers(int num) { galley_rowers = num; }
set_scanners(int num) { galley_scanners = num; }
set_crew(int num) { galley_crew = num; }
set_frequency(string str) { galley_frequency = str; }
set_mode(string str) { galley_mode = str; }

string query_owner() { return galley_owner; }
string query_shipname() { return galley_shipname; }
int query_hp() { return galley_hp; }
int query_wc() { return galley_wc; }
int query_ac() { return galley_ac; }
int query_vertical() { return galley_vertical; }
int query_horizontal() { return galley_horizontal; }
int query_aim_ver() { return galley_aim_ver; }
int query_aim_hor() { return galley_aim_hor; }
string query_aim_dir() { return galley_aim_dir; }
int query_aim_dist() { return galley_aim_dist; }
int query_speed() { return galley_speed; }
string query_direction() { return galley_direction; }
int query_cannons() { return galley_cannons; }
int query_cannonballs() { return galley_cannonballs; }
int query_aimers() { return galley_aimers; }
int query_firers() { return galley_firers; }
int query_rowers() { return galley_rowers; }
int query_scanners() { return galley_scanners; }
int query_crew() { return galley_crew; }
string query_frequency() { return galley_frequency; }
string query_mode() { return galley_mode; }

reduce_hp(int num) {
  if(num > galley_hp) {
    destroy_ship();
  }
  else {
    galley_hp -= num;
  }
  return 1;
}

reduce_ac(int num) {
  if(num > galley_ac) {
    destroy_ship();
  }
  else {
    galley_ac -= num;
  }
  return 1;
}

init() {
  ::init();
  add_action("do_abandon","abandon");
  add_action("do_report","report");
  add_action("do_sail","sail");
  add_action("do_speed","speed");
  add_action("do_stop","stop");
  add_action("do_aim","aim");
  add_action("do_fire","fire");
  add_action("do_scan","scan");
  add_action("do_frequency","frequency");
  add_action("do_radio","radio");
  add_action("do_mode","mode");
  add_action("do_dir","north");
  add_action("do_dir","n");
  add_action("do_dir","south");
  add_action("do_dir","s");
  add_action("do_dir","east");
  add_action("do_dir","e");
  add_action("do_dir","west");
  add_action("do_dir","w");
  add_action("do_dir","northeast");
  add_action("do_dir","ne");
  add_action("do_dir","northwest");
  add_action("do_dir","nw");
  add_action("do_dir","southeast");
  add_action("do_dir","se");
  add_action("do_dir","southwest");
  add_action("do_dir","sw");
  add_action("do_help","help");
}

do_help(string str) {
  if(!str) {
    return 0;
  }
  if(str == "galley" || str == "galleys" || str == "ship" || str == "ships") {
    write("Here are some commands:\n"+
          "  report \n"+
          "  abandon ship\n"+
          "  aim <direction> <distance>\n"+
          "  fire \n"+
          "  frequency <number> \n"+
          "  mode <type> \n"+                
          "  radio <message> \n"+
          "  sail <direction> <distance>\n"+
          "  scan <range> \n"+
          "  speed <int>\n"+             
          "  stop sailing \n"+  
          "  stop scanning \n"+  
          "\n");
    return 1;
  }
  return 0;
}
  
destroy_ship() {
  int i;
  object *stuff;

  tell_room(this_object(), "Abandon ship! Abandon ship!\n");
  stuff = all_inventory(this_object());
  for (i = 0; i < sizeof(stuff); i++) {
    if(interactive(stuff[i])) {
      tell_object(stuff[i], "You jump out of the sinking galley.\n");
      stuff[i]->move_player("X#"+SEA_ROOM);
    }
    transfer(stuff[i], SEA_ROOM);
  }
  // will code wreckege later...
  set_alarm(10.0, 0.0, "do_wreck");
  return 1;
}

do_wreck() {
  this_object()->destroy();
  return 1;
}

int do_report() {
  write("Owner:              Captain "+capitalize(galley_owner)+"\n");
  write("Ship Name:          "+capitalize(galley_shipname)+"\n");
  write("Location:           ["+galley_horizontal+", "+galley_vertical+"]\n");
  write("Ship HP:            "+galley_hp+"\n");
  write("Ship WC:            "+galley_wc+"\n");
  write("Ship AC:            "+galley_ac+"\n");
  write("Sailing direction:  "+galley_direction+"\n");
  write("Mode:               "+galley_mode+"\n");
  write("Aimers:             "+galley_aimers+"\n");
  write("Firers:             "+galley_firers+"\n");
  write("Rowers:             "+galley_rowers+"\n");
  write("Scanners:           "+galley_scanners+"\n");
  write("Crew:               "+galley_crew+"\n");
  write("Frequency:          "+galley_frequency+"\n");
  if (!move_to_target_id) {
    if(!aimed) {
      write("Aim distance:       *** not aimed ***\n");
      write("Aim direction:      *** not aimed ***\n");
      write("Aim target:         *** not aimed ***\n");
    }
    else {
      write("Aim distance:       "+galley_aim_dist+"\n");
      write("Aim direction:      "+galley_aim_dir+"\n");
      write("Aim target:         ["+galley_aim_hor+", "+galley_aim_ver+"]\n");
    }
    write("Cannons:            "+galley_cannons+"\n");
    write("Ammunition:         "+galley_cannonballs+"\n");
  }
  else {
    write("Speed:              "+galley_speed+"\n");
  }
  return 1;
}

do_dir() {
  this_object()->do_sail(query_verb()+" 1");
  return 1;
}

int do_sail(string str) {
  string dir; 
  int dist;
  if(!str) {
    tell_room(this_object(), "Error: No arguments were given.\n");
    tell_room(this_object(), "Syntax: sail <direction> <distance>\n");
    return 1;
  }
  if(sscanf(str,"%s %d",dir,dist) != 2) {
    if(sscanf(str,"%d",dist) != 1) {
      if(sscanf(str,"%s",dir) != 1) {
        tell_room(this_object(), "Error: Wrong arguments were given.\n");
        tell_room(this_object(), "Syntax: sail <direction> <distance>\n");
        return 1;
      }
    }
  }
  if(!dir) {
    dir = galley_direction;
  }
  if(!dist) {
    dist = 1;
  }
  if(!intp(dist)) {
    tell_room(this_object(), "Error: <distance> must be an integer.\n");
    tell_room(this_object(), "Syntax: sail <direction> <distance>\n");
    return 1;
  }
  if(!galley_rowers) {
    tell_room(this_object(), "You can't sail anywhere without rowers.\n");
    return 1;
  }
  if(!galley_speed) {
    tell_room(this_object(), "Please set your speed first.\n");
    return 1;
  }
  if(do_scan_id) {
    tell_room(this_object(), "You stop scanning the area.\n");
    remove_alarm(do_scan_id);
    do_scan_id = 0;
  }
  if (do_sail_id || check_spin_id || move_to_target_id) {
    tell_room(this_object(), "Your galley is already moving.\n"); 
    return 1;
  }
  do_sail_id = set_alarmv(1.0, 0.0, "check_spin", ({ dir, dist }));
  return 1;
}

check_spin(string dir, int dist) {
  float delay;
  status derror = 0;
  remove_alarm(do_sail_id);
  do_sail_id = 0;
  switch(dir) {
    case "n": 
      dir = "north";
      break;
    case "s": 
      dir = "south";
      break;
    case "e": 
      dir = "east";
      break;
    case "w": 
      dir = "west";
      break;
    case "ne": 
      dir = "northeast";
      break;
    case "nw": 
      dir = "northwest";
      break;
    case "se": 
      dir = "southeast";
      break;
    case "sw": 
      dir = "southwest";
      break;
  }
  if(query_direction() == dir) {
    delay = 0.0;
  }
  else {
    delay = itof(random(8) + random(8));
  }
  switch(dir) {
    case "north": case "south": case "east": case "west": 
    case "northeast": case "northwest": case "southwest": case "southeast": 
      check_spin_id = set_alarmv(delay, 0.0, "move_to_target", ({ dir, dist, galley_speed }));
      break;
    default:
      derror = 1;
      break;
  }
  if(derror) {
    tell_room(this_object(), "Error: <direction> given wasn't valid.\n");
    tell_room(this_object(), "Syntax: sail <direction> <distance>\n");
    return 1;
  }
  if(query_direction() == dir) {
    tell_room(this_object(),"The galley starts to sail "+dir+".\n");
  }
  else {
    tell_room(this_object(),"The galley slowly turns around and sails "+dir+".\n");
    galley_direction = dir;
  }
  GM->sail_message(this_object(), dir, dist);
  return 1;
}

move_to_target(string dir, int dist, int speed) {
  remove_alarm(check_spin_id);
  check_spin_id = 0;
  if(dist) {
    switch(dir) {
      case "north":
        galley_vertical += 1;
        break;
      case "south":
        galley_vertical -= 1;
        break;
      case "east":
        galley_horizontal += 1;
        break;
      case "west":
        galley_horizontal -= 1;
        break;
      case "northeast":
        galley_vertical += 1;
        galley_horizontal += 1;
        break;
      case "northwest":
        galley_vertical += 1;
        galley_horizontal -= 1;
        break;
      case "southeast":
        galley_vertical -= 1;
        galley_horizontal += 1;
        break;
      case "southwest":
        galley_vertical -= 1;
        galley_horizontal -= 1;
        break;
    }
    if(HM->landp(galley_vertical, galley_horizontal)) {
      int i;
      string where_to = HM->wreckp(galley_vertical,galley_horizontal);
      object *stuff;

      tell_room(this_object(), "The galley ship runs aground!\n");
      stuff = all_inventory(this_object());
      for (i = 0; i < sizeof(stuff); i++) {
        if(interactive(stuff[i])) {
          tell_object(stuff[i], "You swim to shore.\n");
          stuff[i]->move_player("X#"+where_to);
        }
        transfer(stuff[i], where_to);
      }
      set_alarm(10.0, 0.0, "do_wreck");
      return 1;
    }
/*
    tell_room(this_object(),"The galley sails "+dir+" ("+galley_horizontal+", "+galley_vertical+").\n");
*/
    if(query_mode() == "sail") {
      move_to_target_id = set_alarmv(itof(200/(galley_rowers * speed)), 0.0, "move_to_target", ({ dir , dist - 1, speed }));
    }
    else {
      move_to_target_id = set_alarmv(itof(100/(galley_rowers * speed)), 0.0, "move_to_target", ({ dir , dist - 1, speed }));
    }
    GM->move_message(this_object());
  }
  else {
    remove_alarm(move_to_target_id);
    move_to_target_id = 0;
    set_alarmv(1.0, 0.0, "check_aim", ({ galley_aim_dir, galley_aim_dist, 0 }));
    tell_room(this_object(),"You have reached your destination.\n");
    GM->arrive_message(this_object());
    return 1;
  }
}

do_speed(string str) {
  int speed;
  if(!str) {
    tell_room(this_object(), "Error: No argument was given.\n");
    tell_room(this_object(), "Syntax: speed <int>\n");
    return 1;
  }
  if(sscanf(str,"%d",speed) == 1) {
    galley_speed = speed;
    if(speed > MAX_SPEED) {
      tell_room(this_object(), "Error: Speed set too high.\n");
      galley_speed = MAX_SPEED;
    }
    if(speed < MIN_SPEED) {
      tell_room(this_object(), "Error: Speed set too low.\n");
      galley_speed = MIN_SPEED;
    }
    tell_room(this_object(), "Speed set to: "+galley_speed+"\n");
    return 1;
  }
  tell_room(this_object(), "Error: Argument given was not valid.\n");
  tell_room(this_object(), "Syntax: speed <int>\n");
  return 1;
}

do_stop(string str) {
  if(!str) {
    return 0;
  }
  if(str == "sailing") {
    if (do_sail_id) remove_alarm(do_sail_id);
    if (check_spin_id) remove_alarm(check_spin_id);
    if (move_to_target_id) remove_alarm(move_to_target_id);
    do_sail_id = check_spin_id = move_to_target_id = 0;
    set_alarmv(1.0, 0.0, "check_aim", ({ galley_aim_dir, galley_aim_dist, 0 }));
    tell_room(this_object(), "You order your rowers to stop paddling.\n");
    GM->stop_sail_message(this_object());
    return 1;
  }
  if(str == "scanning") {
    if (do_scan_id) remove_alarm(do_scan_id);
    do_scan_id = 0;
    tell_room(this_object(), "You order your crew to stop scanning the area.\n");
    GM->stop_scan_message(this_object());
    return 1;
  }
  return 0;
}

do_stop_silently() {
  remove_alarm(do_sail_id);
  remove_alarm(check_spin_id);
  remove_alarm(move_to_target_id);
  do_sail_id = check_spin_id = move_to_target_id = 0;
  set_alarmv(1.0, 0.0, "check_aim", ({ galley_aim_dir, galley_aim_dist, 0 }));
  return 1;
}

do_stop_by_ramming() {
  remove_alarm(do_sail_id);
  remove_alarm(check_spin_id);
  remove_alarm(move_to_target_id);
  do_sail_id = check_spin_id = move_to_target_id = 0;
  set_alarmv(1.0, 0.0, "check_aim", ({ galley_aim_dir, galley_aim_dist, 0 }));
  GM->stop_by_ramming_message(this_object());
  return 1;
}

int do_aim(string str) {
  string dir; 
  int dist;
  if(!str) {
    tell_room(this_object(), "Error: No arguments were given.\n");
    tell_room(this_object(), "Syntax: aim <direction> <distance>\n");
    return 1;
  }
  if(query_mode() == "ram") {
    tell_room(this_object(), "You are currently in ramming mode.  Your poor little aimers have assumed the crash position, and cannot aim the cannons at the moment.\n");
    return 1;
  }
  if(sscanf(str,"%s %d",dir,dist) != 2) {
    if(sscanf(str,"%d",dist) != 1) {
      if(sscanf(str,"%s",dir) != 1) {
        tell_room(this_object(), "Error: Wrong arguments were given.\n");
        tell_room(this_object(), "Syntax: aim <direction> <distance>\n");
        return 1;
      }
    }
  }
  if(!dir) {
    dir = galley_aim_dir;
  }
  if(!dist) {
    dist = 1;
  }
  if(!intp(dist)) {
    tell_room(this_object(), "Error: <distance> must be an integer.\n");
    tell_room(this_object(), "Syntax: aim <direction> <distance>\n");
    return 1;
  }
  if(!galley_aimers) {
    tell_room(this_object(), "You have no aimers to move the cannons.\n");
    return 1;
  }
  if (do_sail_id || check_spin_id || move_to_target_id) {
    tell_room(this_object(), "Your galley needs to be as still as possible, if you want to hit the enemy.\n"); 
    return 1;
  }
  if(dist > 10) {
    tell_room(this_object(), "Your galley doesn't have scud missiles.\n"); 
    return 1;
  }
  galley_aim_dist = dist;
  do_aim_id = set_alarmv(itof(galley_cannons)/itof(galley_aimers), 0.0, "check_aim", ({ dir, dist, 1 }) );
  return 1;
}

check_aim(string dir, int dist, status message) {
  float delay;
  status derror = 0;
  switch(dir) {
    case "n": 
      dir = "north";
      break;
    case "s": 
      dir = "south";
      break;
    case "e": 
      dir = "east";
      break;
    case "w": 
      dir = "west";
      break;
    case "ne": 
      dir = "northeast";
      break;
    case "nw": 
      dir = "northwest";
      break;
    case "se": 
      dir = "southeast";
      break;
    case "sw": 
      dir = "southwest";
      break;
  }
  galley_aim_dir = dir;
  remove_alarm(do_aim_id);
  do_aim_id = 0;
  switch(dir) {
    case "north": case "south": case "east": case "west": case "northeast": case "northwest": case "southwest": case "southeast": 
     if(query_aim_dir() == dir) {
        if(message) {
          tell_room(this_object(), "The cannons are quickly turned "+dir+".\n");
        }
        delay = 0.0;
      }
      else {
        if(message) {
          tell_room(this_object(), "The cannons are slowly turned "+dir+".\n");
        }
        delay = itof(1 + random(8));
      }
      aimed = 1;
      check_aim_id = set_alarmv(delay, 0.0, "aim_at_target", ({ dir, dist, galley_speed, message }));
      break;
    default:
      derror = 1;
      break;
  }
  if(derror && aimed) {
    tell_room(this_object(), "Error: <direction> given wasn't valid.\n");
    tell_room(this_object(), "Syntax: aim <direction> <distance>\n");
    return 1;
  }
  return 1;
}

aim_at_target(string dir, int dist, int speed, status message) {
  galley_aim_ver = galley_vertical;
  galley_aim_hor = galley_horizontal;
  while(dist) {
    switch(dir) {
      case "north":
      case "n":
        galley_aim_ver += 1;
        break;
      case "south":
      case "s":
        galley_aim_ver -= 1;
        break;
      case "east":
      case "e":
        galley_aim_hor += 1;
        break;
      case "west":
      case "w":
        galley_aim_hor -= 1;
        break;
      case "northeast":
      case "ne":
        galley_aim_ver += 1;
        galley_aim_hor += 1;
        break;
      case "northwest":
      case "nw":
        galley_aim_ver += 1;
        galley_aim_hor -= 1;
        break;
      case "southeast":
      case "se":
        galley_aim_ver -= 1;
        galley_aim_hor += 1;
        break;
      case "southwest":
      case "sw":
        galley_aim_ver -= 1;
        galley_aim_hor -= 1;
        break;
    }
    dist--;
  }
  remove_alarm(check_aim_id);
  check_aim_id = 0;
  if(message) {
    tell_room(this_object(),"Your crew members aim the cannons at (HOR):"+galley_aim_hor+", (VER):"+galley_aim_ver+".\n");
    GM->aim_message(this_object());
  }
  return 1;
}

do_fire(string str) {
  if(str) {
    tell_room(this_object(), "Error: No arguments are needed.\n");
    tell_room(this_object(), "Syntax: fire\n");
    return 1;
  }
  if(query_mode() == "ram") {
    tell_room(this_object(), "You are currently in ramming mode.  Your poor little cannon people have assumed the crash position, and cannot fire the cannons at the moment.\n");
    return 1;
  }
  if(!galley_firers) {
    tell_room(this_object(), "You have no people assigned to operate the cannons.\n");
    return 1;
  }
  if(!galley_cannonballs) {
    tell_room(this_object(), "You have no more ammunition.\n");
    return 1;
  }
  if(!aimed) {
    galley_aim_ver = galley_vertical;
    galley_aim_hor = galley_horizontal;
  }
  if(fired) {
    tell_room(this_object(), "The cannons are being reloaded...be patient.\n");
    return 1;
  }
  if(galley_vertical == galley_aim_ver &&
     galley_horizontal == galley_aim_hor) {
    tell_room(this_object(), "Blowing up your own galley isn't very smart.  Try aiming the cannons elsewhere.\n");
    return 1;
  }
  if (do_sail_id || check_spin_id || move_to_target_id) {
    tell_room(this_object(), "Your crew is a little preoccupied, you might want to stop the ship for a while.\n"); 
    return 1;
  }
  if (do_aim_id || check_aim_id) {
    tell_room(this_object(), "Your crew is in the process of aiming the cannons.\n"); 
    return 1;
  }
  tell_room(this_object(), "\a***** B * O * O * M *****\a\n");
  galley_cannonballs = galley_cannonballs - 1;
  GM->fire_message(this_object());
  fired = set_alarm(itof(random(galley_aim_dist) + 1), 0.0, "do_boom");
  return 1;
}

do_boom() {
  GM->hit_location(this_object(), galley_aim_hor, galley_aim_ver);
  remove_alarm(fired);
  fired = 0;
  return 1;
}

do_scan(string str) {
  float delay;
  status derror = 0;
  if(!str) {
    tell_room(this_object(), "Error: No arguments were given.\n");
    tell_room(this_object(), "Syntax: scan <range>\n");
    tell_room(this_object(), "Options for <range>: [p]oint blank, [s]hort, [m]edium or [l]ong.\n");
    tell_room(this_object(), "Additional options for <range> while in _SCAN_ mode:\n");
    tell_room(this_object(), "  north, east, west, south, northeast, northwest, southeast, southwest.\n");
    return 1;
  }
  if(!galley_scanners) {
    tell_room(this_object(), "You have no people assigned to scan the area.\n");
    return 1;
  }
  if (do_sail_id || check_spin_id || move_to_target_id) {
    tell_room(this_object(), "Your scanning people are a little preoccupied, you might want to stop the ship for a while.\n"); 
    return 1;
  }
  if(do_scan_id) {
    tell_room(this_object(), "Your people are still scanning the area, they should be done real soon.\n");
    return 1;
  }
  switch(str) {
    case "pointblank":
    case "point blank":
    case "p":
    case "pb":
      str = "point blank";
      delay = POINT_BLANK_RANGE;
      break;
    case "short":
    case "s":
      str = "short";
      delay = SHORT_RANGE;
      break;
    case "medium":
    case "m":
      str = "medium";
      delay = MEDIUM_RANGE;
      break;
    case "long":
    case "l":
      str = "long";
      delay = LONG_RANGE;
      break;
    case "north": case "south": case "east": case "west": 
    case "northeast": case "northwest": case "southwest": case "southeast": 
      GM->scan_area_by_dir(this_object(), str);
      return 1;
      break;
    default:
      derror = 1;
      break;
  }
  if(derror) {
    tell_room(this_object(), "Error: Argument given was invalid.\n");
    tell_room(this_object(), "Syntax: scan <range>\n");
    tell_room(this_object(), "Options for <range>: [p]oint blank, [s]hort, [m]edium or [l]ong.\n");
    tell_room(this_object(), "Additional options for <range> while in scan mode:\n");
    tell_room(this_object(), "  north, east, west, south, northeast, northwest, southeast, southwest.\n");
    return 1;
  }
  if(query_mode() == "ram") {
    tell_room(this_object(), "You are currently in ramming mode.  Your poor little scanning people have assumed the crash position, and can only scan at point blank range.\n");
    str = "point blank";
    delay = POINT_BLANK_RANGE;
  }
  if(query_mode() == "scan") {
    delay = delay/10.0;
  }
  tell_room(this_object(), "You order your crew to begin scanning the area...at "+str+" range.\n");
  do_scan_id = set_alarm(delay/itof(galley_crew), 0.0, "scan_check", str);
  return 1;
}

scan_check(string str) {
  GM->scan_area(this_object(), str);
  remove_alarm(do_scan_id);
  do_scan_id = 0;
  return 1;
}

do_frequency(string str) {
  int before;
  int after;
  if(!str) {
    tell_room(this_object(), "What's the frequency, "+capitalize(this_player()->query_real_name())+"?\n");
    return 1;
  }
  if(sscanf(str,"%d.%d",before,after) != 2 || 
     !intp(before) || 
     !intp(after) ||
     strlen(ftoa(itof(after))) > 1) {
    tell_room(this_object(), "Error: Argument given was invalid.\n");
    tell_room(this_object(), "Syntax: frequency <number>\n");
    tell_room(this_object(), "Format for <number>: xXX.X\n");
    return 1;
  }
  galley_frequency = str;
  tell_room(this_object(), "Frequency set to: "+galley_frequency+"\n");
  return 1;
}

do_radio(string str) {
  if(!str) {
    tell_room(this_object(), "Error: No message given.\n");
    tell_room(this_object(), "Syntax: radio <message> \n");
    return 1;
  }
  if(!galley_frequency) {
    tell_room(this_object(), "What's the frequency, "+capitalize(this_player()->query_real_name())+"?\n");
    tell_room(this_object(), "Error: Frequency hasn't been set.\n");
    tell_room(this_object(), "Syntax: frequency <number>, then \n");
    tell_room(this_object(), "        radio <message> \n");
    return 1;
  }
  GM->radio_message(this_player(), this_object(), str);
  return 1;
}

do_mode(string str) {
  status derror = 0;
  if(!str) {
    tell_room(this_object(), "Error: No mode type given.\n");
    tell_room(this_object(), "Syntax: mode <type> \n");
    tell_room(this_object(), "Options for <type>: board, ram, sail, scan.\n");
    return 1;
  }
  str = lower_case(str);
  switch(str) {
    case "scanning": 
    case "scan": 
      galley_mode = "scan";
      tell_room(this_object(), "You yell: Look out for enemies!  Open your bloody eyes!!!\n");
      break;
    case "sailing": 
    case "sail": 
      galley_mode = "sail";
      tell_room(this_object(), "You yell: Off to sail!!!\n");
      break;
    case "ramming": 
    case "ram": 
      galley_mode = "ram";
      tell_room(this_object(), "You yell: Assume the crash position!!!\n");
      break;
    case "boarding": 
    case "board": 
      galley_mode = "board";
      tell_room(this_object(), "You yell: Prepare to board the other ship!!!\n");
      break;
    default:
      derror = 1;
      break;
  }
  if(derror) {
    tell_room(this_object(), "Error: Invalid mode type given.\n");
    tell_room(this_object(), "Syntax: mode <type> \n");
    return 1;
  }
  tell_room(this_object(), "You are now in "+galley_mode+" mode.\n");
  return 1;
}

do_abandon(str) {
  if(!str) {
    notify_fail("Abandon what?\n");
    return 0;
  }
  if(str == "ship") {
    if(this_player()->query_real_name() == galley_owner) {
      write("Ok, boss.\n");
      set_alarm(1.0, 0.0, "destroy_ship");
      return 1;
    }
    else {
      write("You jump out into the ocean.\n");
      say(CTPQN+" abandons the ship.\n");
      this_player()->move_player("X#"+SEA_ROOM);
      return 1;
    }
  }
  return 0;
}

