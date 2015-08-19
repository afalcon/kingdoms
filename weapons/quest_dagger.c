#define TELLME(X) tell_object(environment(this_object()), X);
#define TELLTHEM(X) my_tell_room(environment(environment(this_object())), capitalize(environment(this_object())->query_name())+ X ,environment(this_object()));

inherit "/std/obj/weapon";

static string color = "white";

void my_tell_room(object room, string message, object me) {
  object *people;
  int i;

  people = all_inventory(room);
  for (i = 0; i < sizeof(people); i++) {
    if(interactive(people[i]) && people[i] != me) {
      tell_object(people[i], message);
    }
  }
}

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("dagger");
  set_class(1);
  set_value(100);
  set_weight(1);
  set_short("a magical white dagger");
  set_long("A very special and quite magical dagger.\n");
  set_type("dagger");
  set_material("magic");
}

void set_color(string newcolor) {
  TELLME("Your dagger suddenly starts glowing.\n");
  TELLTHEM("'s dagger suddenly starts glowing.\n");
  set_short("a glowing magical dagger");
  set_alarm(4.0, 0.0, "do_unwield", newcolor);
}

void do_unwield(string newcolor) {
  if(query_wield()) {
    environment(this_object())->stop_wielding();
  }
  set_alarm(4.0, 0.0, "do_change", newcolor);
}

void do_change(string newcolor) {
  int i;
  switch (newcolor) {
    case "violet": i = 3; break;
    case "indigo": i = 5; break;
    case "blue": i = 7; break;
    case "green": i = 9; break;
    case "yellow": i = 11; break;
    case "orange": i = 13; break;
    case "red": i = 15; break;
    case "black": i = 18; break;
    default: i = 1; break; 
  }
  TELLME("Your old "+color+" dagger magically changes colors and turns "+newcolor+"!\n");
  TELLTHEM("'s old "+color+" dagger magically changes colors and turns "+newcolor+"!\n");
  set_class(i);
  set_alias(newcolor + " dagger");
  set_alt_name("magical dagger");
  set_value(100 * i);
  set_short("a magical "+newcolor+" dagger");
  color = newcolor;
}

void do_upgrade() {
  string tmpcolor;
  switch (color) {
    case "white": tmpcolor = "violet"; break;
    case "violet": tmpcolor = "indigo"; break;
    case "indigo": tmpcolor = "blue"; break;
    case "blue": tmpcolor = "green"; break;
    case "green": tmpcolor = "yellow"; break;
    case "yellow": tmpcolor = "orange"; break;
    case "orange": tmpcolor = "red"; break;
    case "red": tmpcolor = "black"; break;
    default: tmpcolor = "white"; break; 
  }
  set_color(tmpcolor);
}

string query_color() {
  return color;
}

