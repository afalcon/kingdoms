// Clear Skies.
string *weather_zero = ({
  90.0,
  "lovely",
  "This message shouldn't ever get printed since this is the first state.",
  "The sky is completely clear.",
  "The clouds vanish and the sky is completely clear.",
  1,
  1,
  0,
  0,
  0,
  0,
  0,
});

// Light clouds
string *weather_one = ({
  30.0, 
  "almost clear",
  "A few small clouds appear in the sky.",
  "A few scattered clouds dot the sky.",
  "The clouds thin out and almost vanish.",
  1,
  1,
  1,
  0,
  0,
  0,
  0,
});

// Partly cloudy  
string *weather_two = ({
  45.0, 
  "partly cloudy",
  "Larger and thicker clouds begin to form.",
  "Fluffy white clouds drift lazily overhead.",
  "The clouds begin to break apart and the sky shows through.",
  1,
  1,
  2,
  0,
  0,
  0,
  0,
});

// Cloudy
string *weather_three = ({
  45.0, 
  "cloudy",
  "The sky gets covered by thick, dark clouds.",
  "The sky is overcast with dark clouds.",
  "The rain slowly stops, but dark clouds still loom over the sky.",
  0,
  0,
  3,
  1,
  0,
  0,
  0,
});
  
// Light rain
string *weather_four = ({
  30.0, 
  "muggy",
  "It begins to rain, you hear distant \athunder.",
  "A light rain is falling from a cloudy sky.",
  "The rain thins out, but doesn't stop.",
  0,
  0,
  3,
  2,
  0,
  1,
  0,
});

// Steady rain
string *weather_five = ({
  45.0, 
  "wet",
  "It begins to rain steadily, and there is nearby \athunder.",
  "A steady rain is falling.",
  "The heavy rain starts to let up, but there is still a steady downpour of rain.",
  0,
  0,
  4,
  3,
  0,
  2,
  1,
});
  
// Heavy rain
string *weather_six = ({
  30.0, 
  "very wet",
  "It starts to rain even harder.",
  "A heavy downpour of rain falls from the dark and gloomy sky.",
  "The \athunderstorm slowly dissipates, but a heavy downpour of rain continues.",
  0,
  0,
  4,
  4,
  0,
  2,
  1,
});

// Thunderstorm 
string *weather_seven = ({
  20.0,
  "very wet, windy and loud",
  "There is a big clap of \a\a\athunder.",
  "You notice that you are in the middle of a thunderstorm.",
  "The \athunderstorm continues.",
  0,
  0,
  4,
  4,
  0,
  2,
  2,
});

// Hailstorm
string *weather_eight = ({
  20.0,
  "dangerous",
  "Hail stones start falling from the sky, you had better take cover.",
  "Hail stones are falling from the sky, staying outside could be hazardous to your health.",
  "Hail stones stop falling from the sky, you breathe a heavy sigh of relief.",
  0,
  0,
  4,
  4,
  1,
  0,
  0,
});

// Lightning storm
string *weather_nine = ({
  20.0,
  "great",
  "You notice a spectacular lightning show in the sky.",
  "There is a spectacular lightning show in the sky, although it might be wise to stay indoors.",
  "The lightning show suddenly stops, leaving you a bit sad.  The thunderstorm continues.",
  0,
  0,
  4,
  4,
  0,
  2,
  2,
});

string *weather_ten = ({
  50.0,
  "freezing cold",
  "Snow starts falling from the sky.  YEAH!!!!",
  "A blanket of snow covers everything.",
  "The winter season passes, and all the snow melts.",
  1,
  1,
  1,
  0,
  0,
  0,
  0,
});

