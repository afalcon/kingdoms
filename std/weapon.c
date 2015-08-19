#include "/wiz/b/bart/include/defines.h"
inherit "/std/obj/weapon";

string *stuff;
string newweapon, newtype;
int newclass, newweight, newvalue, i;


reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("thingy");
}

calculate(mixed arg) {
  int hmm;
    /*   stuff = ({  */
    /* NAME           WC   TYPE         WT      VALUE  */
   /*  "sickle",          9, "thrusting",  2,        45,
    "dagger",          6, "dagger",     1,        30,
    "dirk",            8, "dagger",     1,        40,
    "knife",           4, "dagger",     1,        20,
    "scimitar",       10, "shortblade", 2,        50,
    "broadsword",     12, "longblade",  3,        300,
    "falchion",       12, "longblade",  2,        300,
    "khopesh",        11, "longblade",  2,        550,
    "longsword",      13, "longblade",  3,        750,
    "shortsword",     10, "shortblade", 2,        500,
    "rapier",         12, "longblade",  2,        600,
    "sabre",          10, "shortblade", 2,        500,
    "cutlass",        11, "longblade",  3,        550,
    "halberd",        13, "polearm",    3,        750,
    "pike",           12, "polearm",    3,        600,
    "lance",          10, "polearm",    3,        500,
    "ranseur",        11, "polearm",    3,        550,
    "spear",          10, "polearm",    3,        500,
    "trident",        10, "polearm",    3,        500,
    "club",            9, "blunt",      2,        900,
    "flail",          10, "chain",      3,        500,
    "hammer",         11, "blunt",      2,        550,
    "war hammer",     11, "blunt",      3,        550,
    "staff",          12, "blunt",      3,        600,
    "rod",            12, "blunt",      3,        600,
    "mace",           12, "blunt",      3,        600,
    "battle axe",     12, "axe",        3,        600,
    "hand axe",        8, "axe",        2,        800,
    "axe",            10, "axe",        2,        500,
    "twohandedsword", 25, "twohanded",  4,        1250,
    "bastardsword",   21, "longsword",  3,        1050,
    "morning  star",   9, "cleave",     2,        450,
    "morningstar",     9, "cleave",     2,        450,
    "claymore",       20, "greatchain", 3,        1000,
  }); */
  stuff = ({ 
    /* NAME           WC   TYPE         WT      VALUE  */
    "sickle",          9, "thrusting",  2,        45,
    "dagger",          6, "dagger",     1,        30,
    "dirk",            8, "dagger",     1,        40,
    "knife",           4, "dagger",     1,        20,
    "scimitar",       10, "shortblade", 2,        50,
    "broadsword",     12, "longblade",  3,        300,
    "falchion",       12, "longblade",  2,        300,
    "khopesh",        11, "longblade",  2,        550,
    "longsword",      13, "longblade",  3,        750,
    "shortsword",     10, "shortblade", 2,        500,
    "rapier",         12, "longblade",  2,        600,
    "sabre",          10, "shortblade", 2,        500,
    "cutlass",        11, "longblade",  3,        550,
    "halberd",        13, "polearm",    3,        750,
    "pike",           12, "polearm",    3,        600,
    "lance",          10, "polearm",    3,        500,
    "ranseur",        11, "polearm",    3,        550,
    "spear",          10, "polearm",    3,        500,
    "trident",        10, "polearm",    3,        500,
    "club",            9, "blunt",      2,        900,
    "flail",          10, "chain",      3,        500,
    "hammer",         11, "blunt",      2,        550,
    "war hammer",     11, "blunt",      3,        550,
    "staff",          12, "blunt",      3,        600,
    "rod",            12, "blunt",      3,        600,
    "mace",           12, "blunt",      3,        600,
    "battle axe",     12, "axe",        3,        600,
    "hand axe",        8, "axe",        2,        800,
    "axe",            10, "axe",        2,        500,
    "twohandedsword", 25, "twohanded",  4,        1250,
    "bastardsword",   21, "longsword",  3,        1050,
    "morning  star",   9, "cleave",     2,        450,
    "morningstar",     9, "cleave",     2,        450,
    "claymore",       20, "greatchain", 3,        1000,
  }); 
  if(stringp(arg)) {
    if(member_array(lower_case(arg), stuff) > -1) {
      i = member_array(lower_case(arg), stuff);
    }
    else {
      i = 0;
    }
  }
  else {
    hmm = arg * 5;
    if(intp(arg) && hmm < sizeof(stuff)) {
      i = hmm;
    }
    else {
      i = 0;
    }
  }
  newweapon = stuff[i];
  newclass  = stuff[i + 1];
  newtype   = stuff[i + 2];
  newweight = stuff[i + 3];
  newvalue  = stuff[i + 4];
  set_name(newweapon);
  set_class(newclass);
  set_value(newvalue);    
  set_weight(newweight);
  set_short("A steel "+newweapon);
  set_long("An authentic "+newweapon+", carefully forged by the best weapon smith in the North Pole.\n");
  set_type(newtype);
  set_material("steel");
}

void rand_weapon() {
  calculate(random(sizeof(stuff)) + 5);
}

query_prevent_login() {
  return 1;
}

