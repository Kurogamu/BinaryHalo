#pragma once


#define NUM_HOUR_BLOCKS 4
#define NUM_MIN_BLOCKS 6

#define NUM_WN_BLOCKS 6 
#define NUM_WD_BLOCKS 3

#define NUM_BATTERY_BLOCKS 10 
#define NUM_DATE_BLOCKS 5
#define NUM_MONTH_BLOCKS 4

/*
    Inner side requires 2 points per block
    Outer side has 4 lines coinsiding with 6 blocks

*/
static const struct GPathInfo HOUR_POINTS[] = {
  { 7, (GPoint []) {
      {0,34},  {13,36}, {25,41}, {35,49},   // outer points
      {18,66}, {10,61}, {0,59}              // inner points
    },
  },
  { 7, (GPoint []) {
      {35,49}, {43,59}, {48,71}, {50,84},
      {25,84}, {23,74}, {18,66}
    },
  }, 
  { 7, (GPoint []) {
      {50,84}, {48,97}, {43,109},{35,119}, 
      {18,102},{23,94}, {25,84} 
    },
  },
  { 7, (GPoint []) {
      {35,119},{25,127},{13,132},{0,134},
      {0,109}, {10,107},{18,102}
    }
  }
};



static const struct GPathInfo MIN_POINTS[] = {
  { 6, (GPoint []) {
      {0, 9}, // outer high
      {19,11}, // outer middle
      {38,19}, // outer low
      {25,41}, // inner low
      {13,36}, // inner middle
      {0,34} // inner high
    },
  },
  { 6, (GPoint []) {
      {38,19}, // outer high
      {53,31}, // outer middle
      {65,47}, // outer low
      {43,59}, // inner low
      {35,49}, // inner middle
      {25,41} // inner high
    },
  },
  { 6, (GPoint []) {
      {65,47}, // outer high
      {72,65}, // outer middle
      {75,84}, // outer low
      {50,84}, // inner low
      {48,71}, // inner middle
      {43,59} // inner high
    },
  },
  { 6, (GPoint []) { //lower half!
      {75,84}, // outer high
      {72,103}, // outer middle
      {65,122}, // outer low
      {43,109}, // inner low
      {48,97}, // inner middle
      {50,84} // inner high
    },
  },
  { 6, (GPoint []) {
      {65,122}, // outer high
      {53,137}, // outer middle
      {38,149}, // outer low
      {25,127}, // inner low
      {35,120}, // inner middle
      {43,109} // inner high
    },
  },
  { 6, (GPoint []) {
      {38,149}, // outer high
      {19,156}, // outer middle
      {0,159}, // outer low
      {0,134}, // inner low
      {13,132}, // inner middle
      {25,127} // inner high
    },
  }
};


static const struct GPathInfo MIDDAY_POINTS[] = {
  { 6, (GPoint []) {
      {0,59},
      {10,61},
      {18,66},
      {23,74},
      {25,84},
      {0,84}
    },
  },
  { 6, (GPoint []) {
      {0,84},
      {25,84},
      {23,94},
      {18,102},
      {10,107},
      {0,109}
    }
  }
};



// upper right circle
static const struct GPathInfo WEEKNUM_POINTS[] = {
  { 7 , (GPoint []) {
      {102,2}, {116, 4}, {128,11}, {137, 22},
      {123,30}, {114,21}, {102,18}
    },
  },
  { 7 , (GPoint []) {
      {137,22}, {141, 35}, {141,49}, {137, 62},
      {123,54}, {126,42}, {123,30}
    },
  },
  { 7 , (GPoint []) {
      {137,62}, {128, 73}, {116,80}, {102, 82},
      {102,66}, {113,63}, {123,54}
    },
  },
  { 7 , (GPoint []) {
      {102,82}, {88,80}, {76,73}, {67, 62},
      {81,54}, {90,63}, {102,66}
    },
  },
  { 7 , (GPoint []) {
      {67,62}, {63,49}, {63,35}, {67, 22},
      {81,30}, {78,42}, {81,54}
    },
  },
  { 7 , (GPoint []) {
      {67,22}, {76,11}, {88,4}, {102,2},
      {102,18}, {90,21}, {81,30}
    },
  },
};

static const struct GPathInfo WEEKDAY_POINTS[] = {
  { 6, (GPoint []) {
      {102,18},{114,21}, {123,30}, {126,42}, {123,54}, 
      {102,42}
    },
  },
  { 6, (GPoint []) {
      {123,54},{113,63},{102,66},{90,63},{81,54},
      {102,42},
    },
  },
  { 6, (GPoint []) {
      {81,54},{78,42},{81,30},{90,21},{102,18},
      {102,42}
    }
  }
};


static const struct GPathInfo BATTERY_POINTS[] = {
  { 4, (GPoint []) {
      {68,168}, {69,156}, {56,154}, {55,168},
    },
  },
  { 4, (GPoint []) {
      {69,156}, {72,145}, {59,141}, {56,154},
    },
  },
  { 4, (GPoint []) {
      {72,145}, {76,134}, {65,128}, {59,141},
    },
  },
  { 4, (GPoint []) {
      {76,134}, {83,123}, {72,116}, {65,128},
    },
  },
  { 4, (GPoint []) {
      {83,123}, {90,114}, {81,105}, {72,116},
    },
  },
  { 4, (GPoint []) {
      {90,114}, {99,106}, {92,96}, {81,105},
    },
  },
  { 4, (GPoint []) {
      {99,106}, {110,100}, {104,88}, {92,96},
    },
  },
  { 4, (GPoint []) {
      {110,100}, {121,96}, {117,83}, {104,88},
    },
  },
  { 4, (GPoint []) {
      {121,96}, {132,93}, {130,81}, {117,83},
    },
  },
  { 4, (GPoint []) {
      {132,93}, {144,92}, {144,79}, {130,81},
    }
  }
};

static const struct GPathInfo DATE_POINTS[] = {
  { 6, (GPoint []) {
      {89,168}, {90,159}, {92,151},
      {72,145}, {69,156}, {68,168}
    },
  },
  { 6, (GPoint []) {
      {92,151}, {95,143}, {100,136},
      {83,123}, {76,134}, {72,145}
    },
  },
  { 6, (GPoint []) {
      {100,136}, {105,129}, {112,124},
      {99,107}, {90,114}, {83,123}
    },
  },
  { 6, (GPoint []) {
      {112,124}, {119,119}, {127,116},
      {121,96}, {110,100}, {99,107}
    },
  },
  { 6, (GPoint []) {
      {127,116}, {135,114}, {144,113},
      {144,92}, {132,93}, {121,96}
    }
  }
};

static const struct GPathInfo MONTH_POINTS[] = {
  { 6, (GPoint []) {
      {89,168},{90,157},{93,147},
      {113,155},{111,161},{110,168}
    },
  },
  { 6, (GPoint []) {
      {93,147},{98,137},{105,129},
      {120,144},{116,149},{113,155}
    },
  },
  { 6, (GPoint []) {
      {105,129},{113,122},{123,117},
      {131,137},{125,140},{120,144}
    },
  },
  { 6, (GPoint []) {
      {123,117},{133,114},{144,113},
      {144,134},{137,135},{131,137}
    }
  }
};


static const GPathInfo BT_POINTS = {
  10, (GPoint []) {
    {110,168},{111,161},{113,155},{116,149},{120,144},{125,140},{131,137},{137,135},{144,134},
    {144,168}
  }
};