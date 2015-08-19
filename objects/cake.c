inherit "/std/healing/food";

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_name("cake");
  set_short("a cake with 1251 candles");
  set_long("This cake has 1251 candles...to celebrate Firestorm's promotion."+
  "\nWritten in frosting are the words:\n"+
  "\"CONGRATULATIONS, STORMIE!!! You did well!\"\n");
  set_value(100);
  set_weight(1);
  set_strength(100);
  set_eater_mess("Yyyyyyyyyyyyyuuuuuuuuuuuuummmmmmmmmmmmmmm!!!\n");
  set_eating_mess(" says: This cake is nummy!\n");
}
