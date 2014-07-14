enum GolfCourse_t {
  THREE_HOLE,
  SIX_HOLE,
  NINE_HOLE
};

enum GolfPosition_t {
  GOLF_LEFT,
  GOLF_CENTER,
  GOLF_RIGHT
};

//Hole Name	Position	Aim	Strength	Notes
//Afternoon Tee	Center	straight	72	Hole in one!! confirmed
//Down the Hatch	Center	straight	81	
//Hole in Fun	Center	straight	52-55	Hit up arrow first.  Hole in One
//Hole on the Range	Center	straight	68	Hole in One
//Holy Mackerel!	Center	straight	44-46	Hole in One
//Hot Links	Right	straight	82	Hole in One (be sure to hit up arrow)
//One Little Birdie	Left	32 right	77	
//Peanut Putter	Center	straight	70-75	Hole in one (got one on 68 and 89)
//Seeing Green	Center	straight	54-57	Hole in one!! confirmed
//Swing Along	Center	11 right	78	
//Swing Time	Center	16 right	55	

struct GolfingHoles {
  const char *name_;
  GolfCourse_t course_;
  GolfPosition_t position_;
  int aim_;       // A neg number is turn left, pos is turn right.. number is ms to pause
  bool center_before_hitting_;
  int strength_;  // How long to pause before hitting
} holes_[] = {
  { "Afternoon Tea",     THREE_HOLE, GOLF_CENTER, 25, false, 2000},
  { "Down the hatch",    THREE_HOLE, GOLF_CENTER, 0, false, 2100},
  { "Hole in fun",       THREE_HOLE, GOLF_CENTER, 0, true, 1300},
  { "Hole on the Range", THREE_HOLE, GOLF_CENTER, 10, false, 1800},
  { "Holy Mackererl",    THREE_HOLE, GOLF_CENTER, 0, false, 995},
  { "Hot Links",         THREE_HOLE, GOLF_RIGHT,  0, true, 2400},
  { "One Little Birdie", THREE_HOLE, GOLF_RIGHT,   450, false, 2350},
  { "Peanut Putter",     THREE_HOLE, GOLF_CENTER, 20, false, 1850},
  { "Seeing Green",      THREE_HOLE, GOLF_CENTER, 0, false, 1500},
  { "Swing Along",       THREE_HOLE, GOLF_CENTER, -10, false, 2200},
  { "Swing Time",        THREE_HOLE, GOLF_CENTER, 698, false, 1300}
};
