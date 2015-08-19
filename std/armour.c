/* 
   Note: This file can only be used for armours of type
             helmet, shield, cloak, glove, boot, legging
*/


inherit "/std/obj/armour";

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("armour");
  set_short("a white piece of armour");
  set_long("Its color makes it a rather unique piece of armour.\n");
  set_type("armour");
  set_value(100);
  set_new_ac(1);
  set_db(0);
  set_weight(1);
  set_material("iron");
}

void calculate(string newtype, int level) {
  string newcolor;
  int i;

  switch (level) {
    case 2..4: newcolor = "violet"; i = 2; break;
    case 5..7: newcolor = "indigo"; i = 3; break;
    case 8..10: newcolor = "blue"; i = 4; break;
    case 11..13: newcolor = "green"; i = 5; break;
    case 14..16: newcolor = "yellow"; i = 6; break;
    case 17..18: newcolor = "orange"; i = 7; break;
    case 19: newcolor = "red"; i = 8; break;
    default: newcolor = "white"; i = 1; break; 
  }

  set_name(newtype);
  set_alias(newcolor+" "+newtype);
  set_type(newtype);
  set_new_ac(2 + i);
  // Value coefficient changed from 100 to 25 - Ceril 960113
  // Value coefficient changed from 25 to 5 - Ceril 961016
  set_value(5 * i);
  if (newtype == "legging") {
    set_material("cloth");
  }
  if (newtype == "glove" || newtype == "boot" || newtype == "legging") {
    newtype = newtype+"s";
    set_alt_name(newtype);
    set_short("a pair of "+newcolor+" "+newtype+"");
  }
  else {
    if (newcolor == "indigo" || newcolor == "orange") {
      set_short("an "+newcolor+" "+newtype+"");
    }
    else {
      set_short("a "+newcolor+" "+newtype+"");
    }
  }
  set_long("Its unique "+newcolor+" color makes the "+newtype+" kinda special.\n");
}

query_prevent_login() {
  return 1;
}

