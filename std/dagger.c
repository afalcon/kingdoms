inherit "/std/obj/weapon";

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("dagger");
  set_class(1);
  set_value(100);
  set_weight(1);
  set_short("a regular white dagger");
  set_long("It is a very ordinary dagger.  There is absolutely nothing special about it.\n");
  set_type("dagger");
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
  set_class(i);
  set_alias(newcolor+ " dagger");
  set_value(10 * i);
  if (newcolor == "indigo" || newcolor == "orange") {
    set_short("an "+newcolor+" dagger");
  }
  else {
    set_short("a "+newcolor+" dagger");
  }
}

query_prevent_login() {
  return 1;
}

