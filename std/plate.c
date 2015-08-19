inherit "/std/obj/armour";

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("armour");
  set_alt_name("plate");
  set_short("a white plate armour");
  set_long("Its color makes it a rather unique plate armour.\n");
  set_value(100);
  set_weight(4);
  set_new_ac(1);
  set_db(0);
  set_type("armour");
  set_material("iron");
}

void calculate(int level) {
  string s;
  switch (level) {
    case 2..4: s = "violet"; break;
    case 5..7: s = "indigo"; break;
    case 8..10: s = "blue"; break;
    case 11..13: s = "green"; break;
    case 14..16: s = "yellow"; break;
    case 17..18: s = "orange"; break;
    case 19: s = "red"; break;
    default: s = "white"; break; 
  }
  this_object()->set_color(s);
}
    
void set_color(string newcolor) {
  int i;
  switch (newcolor) {
    case "violet": i = 2; break;
    case "indigo": i = 3; break;
    case "blue": i = 4; break;
    case "green": i = 5; break;
    case "yellow": i = 6; break;
    case "orange": i = 7; break;
    case "red": i = 8; break;
    default: i = 1; break; 
  }
  set_new_ac(14 + (i * 2));
  // Value changed from 100 * i * to 100 + 10 * i * i
  // Ceril 960113
  set_value(200 + 10 * i * i );
  if (newcolor == "indigo" || newcolor == "orange") {
    set_short("an "+newcolor+" plate armour");
  }
  else {
    set_short("a "+newcolor+" plate armour");
  }
}

query_prevent_login() {
  return 1;
}

