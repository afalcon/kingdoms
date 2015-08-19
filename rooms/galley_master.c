#define HM "/wiz/b/bart/rooms/harbor_master"
#define HP_LIMIT 300
#define WC_LIMIT 30
#define AC_LIMIT 30
#define AIMERS_LIMIT 10
#define FIRERS_LIMIT 10
#define SCANNERS_LIMIT 10
#define ROWERS_LIMIT 10
#define CANNON_LIMIT 10
#define AMMO_LIMIT 50
#define CAP(X) capitalize(X)
#define RAND "/wiz/b/bart/std/randomizer"
inherit "/std/room/room";

object *ships;

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_light(1);
  set_short("a galley master");
  set_long(
"You are in the galley master.\n"+
"\n"+
"Here's some commands:\n"+
"  list         - lists all the ships out in the ocean.\n"+
"  new          - puts a new galley in the ocean, moves you there too.\n"+
"  board <num>  - enter a galley, <num> corresponds to the ones in \"list\".\n"+
"  nuke         - destroys every galley in the \"list\".\n"+
"\n\n");
  add_exit("/wiz/b/bart/workroom","up");
  ships = ({ });
}

init() {
  ::init();
  add_action("do_list","list");
  add_action("do_new","new");
  add_action("do_board","board");
  add_action("do_nuke","nuke");
}

do_list() {
  int i;
  remove_zeroes();
  write(sprintf("%|13s %|20s %|3s %|3s %|3s %|3s %|3s %|3s %|3s %|3s",
      "Owner",
      "Ship name",
      "Hor",
      "Ver",
      "Can",
      "HP",
      "WC",
      "AC",
      "Ah",
      "Av"
      )+"\n");
  for(i = 0; i < sizeof(ships); i++) {
    write((i+1) +". "+sprintf("%O",ships[i])+"\n");
    write(
      sprintf("%|13s %|20s %3d %3d %3d %3d %3d %3d %3d %3d",
      ships[i]->query_owner(),
      ships[i]->query_shipname(),
      ships[i]->query_horizontal(),
      ships[i]->query_vertical(),
      ships[i]->query_cannonballs(),
      ships[i]->query_hp(),
      ships[i]->query_wc(),
      ships[i]->query_ac(),
      ships[i]->query_aim_hor(),
      ships[i]->query_aim_ver()
      )+"\n");
  }
  return 1;
}

do_new() {
  object s;
  s = make("/wiz/b/bart/std/galley");
  s->set_light(1);
  s->set_long(
"You are in a galley.   \n"+
"Here are some commands:\n"+
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
  s->set_skip_obvious(1);
  s->set_owner(this_player()->query_real_name());
  s->set_shipname("galley");
  s->set_short("a mean looking galley");
  s->set_hp(100);
  s->set_wc(30);
  s->set_ac(30);
  s->set_location(1 + random(10), 500 + random(10));
  s->set_speed(0);
  s->set_direction("south");
  s->set_cannons(10);
  s->set_cannonballs(100);
  s->set_aimers(10);
  s->set_crew(10);
  s->set_firers(10);
  s->set_rowers(10);
  s->set_scanners(10);
  s->set_frequency("123.4");
  s->set_mode("sail");
  transfer(s,"/wiz/b/bart/rooms/void");
  this_player()->move_player("to another galley",s,"from somewhere");
  return 1;
}

do_board(string str) {
  int num;
  if(!str) {
    notify_fail("Syntax: board <num>\n");
    return 0;
  }
  if(sscanf(str,"%d",num) != 1) {
    notify_fail("Syntax: board <num>\n");
    return 0;
  }
  num -= 1;
  if(num < 0 || num > sizeof(ships)) {
    write("<Num> is not valid, bunghole.\n");
    return 1;
  }
  this_player()->move_player("to "+ships[num]->query_shipname(),ships[num],"from the galley master");
  return 1;
}

do_nuke() {
  int i;
  for(i = 0; i < sizeof(ships); i++) {
    ships[i]->destroy_ship();
  }
  remove_zeroes();
  return 1;
}
  
add_ship(object ob) {
  if(member_array(ob, ships) < 0) {
    ships += ({ ob });
  }
  remove_zeroes();
  return 1;
}

remove_ship(object ob) {
  if(member_array(ob, ships) < 0) {
    ships -= ({ ob });
  }
  remove_zeroes();
  return 1;
}

aim_message(object ob) {
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" at ["+
    ob->query_horizontal()+","+ob->query_vertical()+"] aims at ["+
    ob->query_aim_hor()+","+ob->query_aim_ver()+"].\n");
}

sail_message(object ob, string dir, int dist) {
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" at ["+
    ob->query_horizontal()+","+ob->query_vertical()+"] sails "+
    dir+" ("+dist+"), speeding at "+ob->query_speed()+" kph.\n");
}

stop_sail_message(object ob) {
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" abruptly stops at ["+
    ob->query_horizontal()+","+ob->query_vertical()+"].\n");
}

stop_scan_message(object ob) {
  tell_room(this_object(),
    ob->query_owner()+"'s "+ob->query_shipname()+" abruptly stops scanning.\n");
}

stop_by_ramming_message(object ob) {
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" abruptly stops at ["+
    ob->query_horizontal()+","+ob->query_vertical()+"].\n");
  tell_room(ob, "The galley stops as you order your crew to inspect the damages.\n");
}

arrive_message(object ob) {
  int i;
  int up, down, right, left;
  int ver, hor;
  int range;
  ver = ob->query_vertical();
  hor = ob->query_horizontal();
  range = 10;
  up = ver + range;
  down = ver - range;
  right = hor + range;
  left = hor - range;
  for (i = 0; i < sizeof(ships); i++) {
    if(ships[i] != ob) {
      if(ships[i]->query_vertical() <= up &&  
         ships[i]->query_vertical() >= down &&  
         ships[i]->query_horizontal() <= right &&
         ships[i]->query_horizontal() >= left) {
        find_message(ships[i], ob);
        find_message(ob, ships[i]);
      }
    }
  }
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" reaches ["+
    ob->query_horizontal()+","+ob->query_vertical()+"].\n");
  return 1;
}

fire_message(object ob) {
  int i;
  int up, down, right, left;
  int ver, hor;
  int range;
  ver = ob->query_vertical();
  hor = ob->query_horizontal();
  range = 10;
  up = ver + range;
  down = ver - range;
  right = hor + range;
  left = hor - range;
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" at ["+
    ob->query_horizontal()+","+ob->query_vertical()+"] fires its cannons.\n");
  for (i = 0; i < sizeof(ships); i++) {
    if(ships[i] != ob) {
      if(ships[i]->query_vertical() <= up &&  
         ships[i]->query_vertical() >= down &&  
         ships[i]->query_horizontal() <= right &&
         ships[i]->query_horizontal() >= left) {
        hear_message(ships[i]);
      }
    }
  }
  return 1;
}

hear_message(object ob) {
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" at ["+
    ob->query_horizontal()+","+ob->query_vertical()+"] hears the shots being fired.\n");
  tell_room(ob, "\aYou hear the sounds of cannons being fired from another ship.\n");
  return 1;
}

hit_location(object enemy, int horizontal, int vertical) {
  int i;
  status hitsomeone = 0;
  for (i = 0; i < sizeof(ships); i++) {
    if(ships[i]->query_vertical() == vertical &&  
       ships[i]->query_horizontal() == horizontal) {
      hit_message(enemy, ships[i]);
      hitsomeone = 1;
    }
  }
  if(!hitsomeone) {
    no_hit_message(enemy);
  }
  return 1;
}

destroy_ship(object enemy, object target) {
  tell_room(this_object(), 
    enemy->query_owner()+"'s "+enemy->query_shipname()+" at ["+
    enemy->query_horizontal()+","+enemy->query_vertical()+"] sinks "+
    target->query_owner()+"'s "+target->query_shipname()+" at ["+
    target->query_horizontal()+","+target->query_vertical()+"]\n");
  tell_room(enemy, "*** V I C T O R Y ***\n");
  tell_room(enemy, "You have sunk the enemy ship!\n");
  ships -= ({ target });
  remove_zeroes();
  target->destroy_ship();
  return 1;
}

hit_message(object enemy, object target) {
  int hp, damage, defense, offense;
  tell_room(target, "*** Oof! ***\n");
  tell_room(target, "Your galley has been struck by a cannon ball fired from an enemy ship!\n");
  tell_room(enemy, "*** Yay! ***\n");
  tell_room(enemy, "Your crew celebrates as a cannon ball lands right smack on the enemy's ship!\n");

  hp = target->query_hp();
  defense = target->query_ac();
  offense = enemy->query_wc();
  if(offense > defense) {
    damage = random(offense) + (random(offense - defense) * 2);
  }
  else {
    damage = 1 + random(offense / 2);
  }

  tell_room(this_object(), 
    enemy->query_owner()+"'s "+enemy->query_shipname()+" at ["+
    enemy->query_horizontal()+","+enemy->query_vertical()+"] hits "+
    target->query_owner()+"'s "+target->query_shipname()+" at ["+
    target->query_horizontal()+","+target->query_vertical()+"] with "+
    damage+" damage.\n");
  if(hp > damage) {
    target->reduce_hp(damage);
  }
  else {
    destroy_ship(enemy, target);
  }
  return 1;
}

no_hit_message(object enemy) {
  tell_room(enemy, "*** WOOSH ***\n");
  tell_room(enemy, "Large amounts of water splash up in the air, indicating that you had missed.\n");
  tell_room(this_object(), 
    enemy->query_owner()+"'s "+enemy->query_shipname()+" at ["+
    enemy->query_horizontal()+","+enemy->query_vertical()+"] fires at ["+
    enemy->query_aim_hor()+","+enemy->query_aim_ver()+"] but hits nothing but water.\n");
  return 1;
}

scan_area(object ob, string name_range) {
  int i;
  int up, down, right, left;
  int range;
  int col, row;
  int ver = ob->query_vertical();
  int hor = ob->query_horizontal();
  status found = 0;
  status found_myself = 0;
  switch(name_range) {
    case "point blank":
      range = 10;
      break;
    case "short":
      range = 20;
      break;
    case "medium":
      range = 30;
      break;
    case "long":
      range = 38;
      break;
  }
  up = ver + range/2;
  down = ver - range/2;
  right = hor + range/2;
  left = hor - range/2;
  tell_room(ob,"\n");
  for (row = up; row > down - 1 ; row--) {
    for (col = left; col < right + 1; col++) {
      found = 0;
      for (i = 0; i < sizeof(ships) && !found; i++) {
        if(ships[i]->query_vertical() == row &&  
           ships[i]->query_horizontal() == col &&
           !found) {
          found = 1;
        }
      }
      if (found) {
        if(ob->query_vertical() == row &&  
           ob->query_horizontal() == col &&
           !found_myself) {
          tell_room(ob,"o ");
          found_myself = 1;
        }
        else {
          if(HM->harbourp(row,col)) {
            tell_room(ob,"H ");
          }
          else {
            if(HM->landp(row,col)) {
              tell_room(ob,"L ");
            }
            else {
              tell_room(ob,"x ");
            }
          }
        }
      }
      else {
        if(HM->harbourp(row,col)) {
          tell_room(ob,"H ");
        }
        else {
          if(HM->landp(row,col)) {
            tell_room(ob,"L ");
          }
          else {
            tell_room(ob,". ");
          }
        }
      }
    }
    tell_room(ob,"\n");
  }
  found = 0;
  for (i = 0; i < sizeof(ships); i++) {
    if(ships[i] != ob) {
      if(ships[i]->query_vertical() <= up &&  
         ships[i]->query_vertical() >= down &&  
         ships[i]->query_horizontal() <= right &&
         ships[i]->query_horizontal() >= left) {
        find_message(ob, ships[i]);
        found = 1;
      }
    }
  }
  if (!found) {
    no_find_message(ob);
  }
  return 1;
}

scan_area_by_dir(object ob, string dir_range) {
  int i;
  int up, down, right, left;
  int range = 10;
  int col, row;
  int ver = ob->query_vertical();
  int hor = ob->query_horizontal();
  status found = 0;
  status found_myself = 0;

  if(ob->query_mode() != "scan") {
    tell_room(ob,"You better get into scan mode before trying that.\n");
    return 1;
  }

  up = ver + range;
  down = ver - range;
  right = hor + range;
  left = hor - range;
  switch(dir_range) {
    case "north":
      up = up + range;
      down = down + range;
      break;
    case "east":
      right = right + range;
      left = left + range;
      break;
    case "west":
      right = right - range;
      left = left - range;
      break;
    case "south":
      up = up - range;
      down = down - range;
      break;
    case "northeast":
      up = up + range;
      down = down + range;
      right = right + range;
      left = left + range;
      break;
    case "northwest":
      up = up + range;
      down = down + range;
      right = right - range;
      left = left - range;
      break;
    case "southeast":
      up = up - range;
      down = down - range;
      right = right + range;
      left = left + range;
      break;
    case "southwest":
      up = up - range;
      down = down - range;
      right = right - range;
      left = left - range;
      break;
  }
  tell_room(ob,"\n");
  for (row = up; row > down - 1; row--) {
    for (col = left; col < right + 1; col++) {
      found = 0;
      for (i = 0; i < sizeof(ships) && !found; i++) {
        if(ships[i]->query_vertical() == row &&  
           ships[i]->query_horizontal() == col &&
           !found) {
          found = 1;
        }
      }
      if (found) {
        if(ob->query_vertical() == row &&  
           ob->query_horizontal() == col &&
           !found_myself) {
          tell_room(ob,"o ");
          found_myself = 1;
        }
        else {
          if(HM->harbourp(row,col)) {
            tell_room(ob,"H ");
          }
          else {
            if(HM->landp(row,col)) {
              tell_room(ob,"L ");
            }
            else {
              tell_room(ob,"x ");
            }
          }
        }
      }
      else {
        if(HM->harbourp(row,col)) {
          tell_room(ob,"H ");
        }
        else {
          if(HM->landp(row,col)) {
            tell_room(ob,"L ");
          }
          else {
            tell_room(ob,". ");
          }
        }
      }
    }
    tell_room(ob,"\n");
  }
  found = 0;
  for (i = 0; i < sizeof(ships); i++) {
    if(ships[i] != ob) {
      if(ships[i]->query_vertical() <= up &&  
         ships[i]->query_vertical() >= down &&  
         ships[i]->query_horizontal() <= right &&
         ships[i]->query_horizontal() >= left) {
        find_message(ob, ships[i]);
        found = 1;
      }
    }
  }
  if (!found) {
    no_find_message(ob);
  }
  return 1;
}

find_message(object finder, object found) {
  tell_room(this_object(), 
    finder->query_owner()+"'s "+finder->query_shipname()+" at ["+
    finder->query_horizontal()+","+finder->query_vertical()+"] scans the area and finds "+
    found->query_owner()+"'s "+found->query_shipname()+" at ["+
    found->query_horizontal()+","+found->query_vertical()+"]\n");
  if(finder->query_vertical() == found->query_vertical()) {
    if(finder->query_horizontal() == found->query_horizontal()) {
      tell_room(finder, "There is a ship right next to yours.\n"); 
      return 1;
    }
    else {
      if(finder->query_horizontal() > found->query_horizontal()) {
        tell_room(finder, "Your crew reports seeing a ship directly to the west.\n"); 
        return 1;
      }
      else {
        tell_room(finder, "Your crew reports seeing a ship directly to the east.\n"); 
        return 1;
      }
    }
  }
  if(finder->query_horizontal() == found->query_horizontal()) {
    if(finder->query_vertical() > found->query_vertical()) {
      tell_room(finder, "Your crew reports seeing a ship directly to the south.\n"); 
      return 1;
    }
    else {
      tell_room(finder, "Your crew reports seeing a ship directly to the north.\n"); 
      return 1;
    }
  }
  if(finder->query_vertical() > found->query_vertical()) {
    if(finder->query_horizontal() > found->query_horizontal()) {
      tell_room(finder, "Your crew reports seeing a ship to the southwest.\n"); 
      return 1;
    }
    else {
      tell_room(finder, "Your crew reports seeing a ship to the southeast.\n"); 
      return 1;
    }
  }
  else {
    if(finder->query_horizontal() > found->query_horizontal()) {
      tell_room(finder, "Your crew reports seeing a ship to the northwest.\n"); 
      return 1;
    }
    else {
      tell_room(finder, "Your crew reports seeing a ship to the northeast.\n"); 
      return 1;
    }
  }
}

no_find_message(object ob) {
  tell_room(ob, "Your crew reports that they've found nothing in the area.\n");
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" at ["+ 
    ob->query_horizontal()+","+ob->query_vertical()+"] scans the area, "+
    "but finds nothing.\n");
  return 1;
}

radio_message(object who, object where, string msg) {
  int i;
  string freq = where->query_frequency();
  tell_room(this_object(), 
     "<"+freq+"> "+CAP(who->query_real_name())+" ["+where->query_shipname()+"]: "+msg+"\n");
  for (i = 0; i < sizeof(ships); i++) {
    if (ships[i]->query_frequency() == freq) {
      tell_room(ships[i], 
        "<"+freq+"> "+CAP(who->query_real_name())+" ["+where->query_shipname()+"]: "+msg+"\n");
      tell_room(this_object(), 
        ships[i]->query_owner()+"'s "+ships[i]->query_shipname()+" hears the radio message.\n");
    }
  }
  return 1;
}

remove_zeroes() {
  while (member_array(0, ships) != -1)
    ships -= ({ 0 });
}

move_message(object ob) {
  int i;
  int up, down, right, left;
  int ver, hor;
  int range;
  ver = ob->query_vertical();
  hor = ob->query_horizontal();
  range = 10;
  up = ver + range;
  down = ver - range;
  right = hor + range;
  left = hor - range;
  tell_room(this_object(), 
    ob->query_owner()+"'s "+ob->query_shipname()+" sails ["+
    ob->query_horizontal()+","+ob->query_vertical()+"].\n");
  for (i = 0; i < sizeof(ships); i++) {
    if(ships[i] != ob) {
      if(ships[i]->query_vertical() <= up &&  
         ships[i]->query_vertical() >= down &&  
         ships[i]->query_horizontal() <= right &&
         ships[i]->query_horizontal() >= left) {
        move_find_message(ships[i], ob);
      }
    }
  }
  return 1;
}

move_find_message(object finder, object found) {
  tell_room(this_object(), 
    finder->query_owner()+"'s "+finder->query_shipname()+" at ["+
    finder->query_horizontal()+","+finder->query_vertical()+"] sees "+
    found->query_owner()+"'s "+found->query_shipname()+" sailing at ["+
    found->query_horizontal()+","+found->query_vertical()+"]\n");
  if(finder->query_vertical() == found->query_vertical()) {
    if(finder->query_horizontal() == found->query_horizontal()) {
      if(finder->query_mode() == "ram" && found->query_mode() == "ram") {
        do_rammage(finder, found);
        return 1;
      }
      else {
        tell_room(finder, "You see another ship sail past you.\n"); 
        return 1;
      }
    }
    else {
      if(finder->query_horizontal() > found->query_horizontal()) {
        tell_room(finder, "You see a galley (west) sail "+found->query_direction()+".\n"); 
        return 1;
      }
      else {
        tell_room(finder, "You see a galley (east) sail "+found->query_direction()+".\n"); 
        return 1;
      }
    }
  }
  if(finder->query_horizontal() == found->query_horizontal()) {
    if(finder->query_vertical() > found->query_vertical()) {
      tell_room(finder, "You see a galley (south) sail "+found->query_direction()+".\n"); 
      return 1;
    }
    else {
      tell_room(finder, "You see a galley (north) sail "+found->query_direction()+".\n"); 
      return 1;
    }
  }
  if(finder->query_vertical() > found->query_vertical()) {
    if(finder->query_horizontal() > found->query_horizontal()) {
      tell_room(finder, "You see a galley (southwest) sail "+found->query_direction()+".\n"); 
      return 1;
    }
    else {
      tell_room(finder, "You see a galley (southeast) sail "+found->query_direction()+".\n"); 
      return 1;
    }
  }
  else {
    if(finder->query_horizontal() > found->query_horizontal()) {
      tell_room(finder, "You see a galley (northwest) sail "+found->query_direction()+".\n"); 
      return 1;
    }
    else {
      tell_room(finder, "You see a galley (northeast) sail "+found->query_direction()+".\n"); 
      return 1;
    }
  }
}

destroy_ship_by_ramming(object victim, object hitter) {
  tell_room(this_object(), 
    victim->query_owner()+"'s "+victim->query_shipname()+" at ["+
    victim->query_horizontal()+","+victim->query_vertical()+"] survives the "+
    hitter->query_shipname()+"'s fail attempt at ramming, and watches them sink below the ocean.\n");
  tell_room(victim, "*** C R U N C H ***\n");
  tell_room(victim, "Your mighty galley survives an attack from the enemy ship!\n");
  tell_room(victim, "You see the poor bastards sink in the water!\n");
  ships -= ({ hitter });
  remove_zeroes();
  hitter->destroy_ship();
  return 1;
}

do_rammage(object victim, object hitter) {
  int victim_damage, hitter_damage;
  victim_damage = random(hitter->query_wc() * hitter->query_speed()) - victim->query_ac();
  hitter_damage = random((victim->query_wc()/2) + victim->query_ac());
  tell_room(this_object(), 
    hitter->query_owner()+"'s "+hitter->query_shipname()+" rams "+
    victim->query_owner()+"'s "+victim->query_owner()+".\n");

  tell_room(victim, "*** Dooh! ***\n");
  tell_room(victim, "Your galley gets struck by a another ship!\n");
  tell_room(hitter, "*** Crunch! ***\n");
  tell_room(hitter, "Your galley crashes into the enemy ship!\n");

  tell_room(this_object(), 
    hitter->query_owner()+"'s "+hitter->query_shipname()+" rams "+
    victim->query_owner()+"'s "+victim->query_shipname()+" at ["+
    victim->query_horizontal()+","+victim->query_vertical()+"] with "+
    victim_damage+" damage, while sustaining "+hitter_damage+" damage.\n");

  if(victim->query_hp() > victim_damage || 
     victim->query_ac() > victim_damage/2) {
    victim->do_stop_by_ramming();
    victim->reduce_hp(victim_damage);
    victim->reduce_ac(victim_damage/2);
  }
  else {
    destroy_ship(hitter, victim);
  }
  if(hitter->query_hp() > hitter_damage ||
     hitter->query_ac() > hitter_damage/2) {
    hitter->do_stop_by_ramming();
    hitter->reduce_hp(hitter_damage);
    hitter->reduce_ac(hitter_damage/2);
  }
  else {
    destroy_ship(victim, hitter);
  }
  return 1;
}

query_ac_limit() {
  return AC_LIMIT;
}

query_ammo_limit() {
  return AMMO_LIMIT;
}

query_cannon_limit() {
  return CANNON_LIMIT;
}

query_hp_limit() {
  return HP_LIMIT;
}

query_wc_limit() {
  return WC_LIMIT;
}

query_aimers_limit() {
  return AIMERS_LIMIT;
}

query_firers_limit() {
  return FIRERS_LIMIT;
}

query_scanners_limit() {
  return SCANNERS_LIMIT;
}

query_rowers_limit() {
  return ROWERS_LIMIT;
}
 
