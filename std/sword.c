inherit "/std/obj/weapon";

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("sword");
  set_alt_name("longsword");
  set_class(1);
  set_value(100);
  set_weight(3);
  set_short("a white longsword");
  set_long("It is a very ordinary longsword.  There is absolutely nothing special about it.\n");
  set_type("longblade");
  set_material("steel");
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
    case "violet": i = 4; break;
    case "indigo": i = 7; break;
    case "blue": i = 10; break;
    case "green": i = 13; break;
    case "yellow": i = 16; break;
    case "orange": i = 19; break;
    case "red": i = 22; break;
    default: i = 1; break; 
  }
  set_class(i+(i/2));
  set_alias(newcolor+ " longsword");
  // Value coefficient changed from 100 to 20
  set_value(20 * i);
  if (newcolor == "indigo" || newcolor == "orange") {
    set_short("an "+newcolor+" longsword");
  }
  else {
    set_short("a "+newcolor+" longsword");
  }
}

query_prevent_login() {
  return 1;
}





