#define CTPQN capitalize(environment(this_object())->query_real_name())
#define TPQN environment(this_object())->query_real_name()
#define CTPQPRO capitalize(environment(this_object())->query_pronoun())
#define TPQPRO environment(this_object())->query_pronoun()
#define TPQPOS environment(this_object())->query_possessive()
#define GM "/wiz/b/bart/rooms/galley_master"
#define SEA_ROOM "/wiz/b/bart/rooms/sea"
inherit "/std/obj/treasure";

string galley_owner;
string galley_shipname;
string galley_longdesc;
int galley_hp;
int galley_wc;
int galley_ac;
int galley_cannons;
int galley_cannonballs;
int galley_aimers;
int galley_firers;
int galley_rowers;
int galley_scanners;
int galley_victories;
string galley_frequency;

set_owner(string str) { galley_owner = str; save_me(); }
set_shipname(string str) { galley_shipname = str; save_me(); }
set_longdesc(string str) { galley_longdesc = str; save_me(); }
set_hp(int num) { galley_hp = num; save_me(); }
set_wc(int num) { galley_wc = num; save_me(); }
set_ac(int num) { galley_ac = num; save_me(); }
set_cannons(int num) { galley_cannons = num; save_me(); }
set_cannonballs(int num) { galley_cannonballs = num; save_me(); }
set_aimers(int num) { galley_aimers = num; save_me(); }
set_firers(int num) { galley_firers = num; save_me(); }
set_rowers(int num) { galley_rowers = num; save_me(); }
set_scanners(int num) { galley_scanners = num; save_me(); }
set_victories(int num) { galley_victories = num; save_me(); }
set_frequency(string str) { galley_frequency = str; save_me(); }

string query_owner() { return galley_owner; }
string query_shipname() { return galley_shipname; }
string query_longdesc() { return galley_longdesc; }
int query_hp() { return galley_hp; }
int query_wc() { return galley_wc; }
int query_ac() { return galley_ac; }
int query_cannons() { return galley_cannons; }
int query_cannonballs() { return galley_cannonballs; }
int query_aimers() { return galley_aimers; }
int query_firers() { return galley_firers; }
int query_rowers() { return galley_rowers; }
int query_scanners() { return galley_scanners; }
int query_victories() { return galley_victories; }
string query_frequency() { return galley_frequency; }

int drop() { return 1; }
int get() { return 0; }

restore_me() {
  restore_object("/wiz/b/bart/galley/save/"+TPQN);
  return 1;
}

save_me() {
  save_object("/wiz/b/bart/galley/save/"+TPQN);
  return 1;
}

init_arg(str) {
  tell_object(this_player(), "Your hook-shaped pin starts to glow.\n");
  set_alarm(1.0, 0.0, "restore_me");
  return 1;
}

init() {
  ::init();
  add_action("do_info","squeeze");
  add_action("do_shipinfo","shipinfo");
}

do_info(string str) {
  if(!str) {
    return 0;
  }
  if(str == "hook" || str == "pin") {
    write("Here are some commands you can use when you are in your ship:\n"+
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
    write("Here are some commands you can use anywhere:\n"+
          "  shipinfo \n"+  
          "\n");
    say(CTPQN+" fondly squeezes "+TPQPOS+" pin.\n");
    return 1;
  }
  return 0;
}
 
do_shipinfo() {
  write("Galley Ship Name:       "+capitalize(galley_shipname)+"\n");
  write("Galley Ship HP:         "+galley_hp+"\n");
  write("Galley Ship WC:         "+galley_wc+"\n");
  write("Galley Ship AC:         "+galley_ac+"\n");
  write("Aiming crew:            "+galley_aimers+"\n");
  write("Firing crew:            "+galley_firers+"\n");
  write("Rowing crew:            "+galley_rowers+"\n");
  write("Scanning crew:          "+galley_scanners+"\n");
  write("Ship Radio Frequency:   "+galley_frequency+"\n");
  write("Number of Cannons:      "+galley_cannons+"\n");
  write("Ammunition Count:       "+galley_cannonballs+"\n");
  return 1;
}

query_extra_description() {
  if(galley_victories != 1) {
    return CTPQN + " is one of the Competitors.\n"+CTPQPRO+" is a proud owner of a galley ship, with "+galley_victories+" victories under "+TPQPOS+" belt";
  }
  else {
    return CTPQN + " is one of the Competitors.\n"+CTPQPRO+" is a proud owner of a galley ship, with "+galley_victories+" victory under "+TPQPOS+" belt";
  }
}

extra_look() { 
    return query_extra_description();
}

reset(arg){
  if(arg) return;
  set_weight(1);
  set_name("pin");
  set_alias("hook");
  set_alt_name("vroomvroomgalleycaptainshook");
  set_value(0);
  set_short("a tiny pin shaped like a galley captain's hook");
  set_long("This hook identifies you as being one of the Competitors.  It sets you apart from the rest of the land-loving losers that you encounter every day, for not many can call themselves galley captains.  Try squeezing it sometimes.\n");
}

add_victory() {
  tell_object(environment(this_object()), "Your hook-shaped pin shines intensely for a brief moment.\n");
  galley_victories = galley_victories + 1;
  save_me();
  return 1;
}

query_auto_load() {
  return "/wiz/b/bart/objects/hook:";
}

