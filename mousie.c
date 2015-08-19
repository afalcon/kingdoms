#define Realname this_player()->query_real_name()
#include "/areas/Bird/Wonderland/o/defs.h"
inherit "/std/living/monster";
inherit "/areas/Bird/Wonderland/o/NPC/response";

reset(arg)
{
   if(arg) return;
   ::reset(arg);
   response_reset(arg);
   set_name("mousie");
   set_alias("mouse");
   set_short("A snuggly little mouse");
   set_long( "A cute, snuggly mouse in a very short dress that shows " +
         "off her long legs. She has long eyelashes that she likes to flutter in " +
         "your direction.\nShe is a gift for Bart from Aslan.\n" );

     set_level(19);
     set_new_ac(50);
     set_hp(1000);
     set_wc(30);
     set_db(30);
     set_gender(2);

     set_race("mouse");
}

init() {

   ::init();
response_init();
}
