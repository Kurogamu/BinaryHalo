#include <pebble.h>
#include "binaryhalo.h"
#include "string.h"
#include "stdlib.h"

Layer *simple_bg_layer;


static GPath *hour_blocks[NUM_HOUR_BLOCKS];
static GPath *min_blocks[NUM_MIN_BLOCKS];
static GPath *midday_blocks[2];
static bool is_am;

static GPath *weeknum_blocks[NUM_WN_BLOCKS];
static GPath *weekday_blocks[NUM_WD_BLOCKS];

static int battery_charge;
static GPath *battery_blocks[NUM_BATTERY_BLOCKS];
static GPath *date_blocks[NUM_DATE_BLOCKS];
static GPath *month_blocks[NUM_MONTH_BLOCKS];
static bool bt_connected;
static GPath *bt_block;

Layer *opening_layer;
Layer *time_layer;
Window *window;

static bool opening;
//static AppTimer *timer; //found in feature_timer_animation.c

static void bg_update_proc(Layer *layer, GContext *ctx) {

  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);

  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorBlack);
  /*
  for (int i = 0; i < NUM_HOUR_BLOCKS; i ++) {
    gpath_draw_outline(ctx, hour_blocks[i]);
  }
  for (int i = 0; i < NUM_MIN_BLOCKS; i ++) {
    gpath_draw_outline(ctx, min_blocks[i]);
  }
  */
  
  graphics_draw_circle(ctx, GPoint(0,84), 24);
  graphics_draw_circle(ctx, GPoint(0,84), 25);
  graphics_draw_circle(ctx, GPoint(0,84), 49);
  graphics_draw_circle(ctx, GPoint(0,84), 50);
  graphics_draw_circle(ctx, GPoint(0,84), 74);
  graphics_draw_circle(ctx, GPoint(0,84), 75);
  
  
  graphics_fill_circle(ctx, GPoint(102,42), 40);
  graphics_draw_circle(ctx, GPoint(102,42), 40);
  graphics_draw_circle(ctx, GPoint(102,42), 39);
  graphics_draw_circle(ctx, GPoint(102,42), 24);
  graphics_draw_circle(ctx, GPoint(102,42), 23);
  
  graphics_draw_circle(ctx, GPoint(144,168), 89);
  graphics_draw_circle(ctx, GPoint(144,168), 88);
  graphics_draw_circle(ctx, GPoint(144,168), 76);
  graphics_draw_circle(ctx, GPoint(144,168), 75);
  graphics_draw_circle(ctx, GPoint(144,168), 55);
  graphics_draw_circle(ctx, GPoint(144,168), 54);
  graphics_draw_circle(ctx, GPoint(144,168), 34);
  graphics_draw_circle(ctx, GPoint(144,168), 33);
 
}

/*
static void opening_animation(Layer *layer, GContext* ctx) {
  static int step = 0;
  static bool white = true;
  if (white) {
    graphics_context_set_fill_color(ctx, GColorWhite);
  } else {
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_fill_circle(ctx, GPoint(0,84), 75);
    graphics_context_set_fill_color(ctx, GColorBlack);
  }
  if (step < NUM_HOUR_BLOCKS + 1) {
    for (int i = 0; i < step; i++) {
      gpath_draw_filled(ctx, hour_blocks[i]);
    }
  } else if ( step - (NUM_MIN_BLOCKS + NUM_HOUR_BLOCKS) < 1 ) {
    for (int i = 0; i < NUM_HOUR_BLOCKS; i++) {
      gpath_draw_filled(ctx, hour_blocks[i]);
    }
    for (int i = 0; i < step - NUM_HOUR_BLOCKS; i++) {
      gpath_draw_filled(ctx, min_blocks[NUM_MIN_BLOCKS - i - 1]);
    }
  } else {
    step = -1;
    if (white) {
      white = false;
    } else {
      opening = false; 
    }
  }
  step++;
}


static void timer_callback(void *context) {
  layer_mark_dirty(opening_layer);
  const uint32_t timeout_ms = 100;
  timer = app_timer_register(timeout_ms, timer_callback, NULL);
}
*/


static void battery_status(BatteryChargeState battery) {
  if (battery.is_charging) {
    battery_charge = 10;
  } else {
    battery_charge = (battery.charge_percent / 10);
  }
}

static void bt_status(bool connected) {
  bt_connected = connected;
}

// This is to convert time into 12H format and set AM/PM
unsigned short get_hour(unsigned short hour) {
  if (hour >= 12) {
    hour -= 12;
    is_am = false;
  } else {
    is_am = true;
  }
  
  if (hour == 0) {
    hour = 12;
  }

  return hour;
}

// Sunday is the zeroth day, but I'd like it to be the seventh..
unsigned short get_wday(unsigned short wday) {
  if (wday == 0) {
    wday = 7;
  }

  return wday;
}

static void time_update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);

//  graphics_context_set_fill_color(ctx, GColorBlack);
/*  
  for (int i = 0; i < NUM_HOUR_BLOCKS; i++) {
    gpath_draw_filled(ctx, hour_blocks[i]);
    
  }
  
  for (int i = 0; i < NUM_MIN_BLOCKS; i++) {
    gpath_draw_filled(ctx, min_blocks[i]);
  }
*/

  graphics_context_set_stroke_color(ctx, GColorWhite);
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  unsigned short hour = get_hour(t->tm_hour);
  unsigned short wday = get_wday(t->tm_wday);

  /* This totally magic solution was adapted from example watchface just_a_bit
   * >>     shifts a bit to the right
   * & 0x1  AND operator on least significant bit and 1
   * Each iteration will shift the current time one step right (in binary),
   * compare it to 1, meaning that every 1-valued bit will return true
   */
  for (int i = 0; i < NUM_HOUR_BLOCKS; i++) {
    if ((hour >> i) & 0x1) {
      gpath_draw_filled(ctx, hour_blocks[i]);
      gpath_draw_outline(ctx, hour_blocks[i]);
    } 
  }
  for (int i = 0; i < NUM_MIN_BLOCKS; i++) {
    if ((t->tm_min >> i) & 0x1) {
      gpath_draw_filled(ctx, min_blocks[i]);
      gpath_draw_outline(ctx, min_blocks[i]);
    } 
  }
  

  // Give the weeknumber as an int
  char buffer[4];
  strftime(buffer, 4, "%W", t);
  int weeknum = atoi(buffer);
  weeknum++; 
  for (int i = 0; i < NUM_WN_BLOCKS; i++) {
    if (weeknum >> i & 0x1) {
      gpath_draw_filled(ctx, weeknum_blocks[i]);
      gpath_draw_outline(ctx, weeknum_blocks[i]);
    }
  }

  for (int i = 0; i < NUM_WD_BLOCKS; i++) {
    if ( ( wday >> i) & 0x1) {
      gpath_draw_filled(ctx, weekday_blocks[i]);
      gpath_draw_outline(ctx, weekday_blocks[i]);
    }
  }
  

  for (int i = 0; i < battery_charge; i++) {
    gpath_draw_filled(ctx, battery_blocks[i]);
      gpath_draw_outline(ctx, battery_blocks[i]);
  }

  for (int i = 0; i < NUM_DATE_BLOCKS; i++) {
    if ( ( t->tm_mday >> i) & 0x1) {
      gpath_draw_filled(ctx, date_blocks[i]);
      gpath_draw_outline(ctx, date_blocks[i]);
    }
  }

  for (int i = 0; i < NUM_MONTH_BLOCKS; i++) {
    if ( ( (t->tm_mon + 1) >> i) & 0x1) {
      gpath_draw_filled(ctx, month_blocks[i]);
      gpath_draw_outline(ctx, month_blocks[i]);
    }
  }

  if (bt_connected) {
    gpath_draw_filled(ctx, bt_block);
  }

  if (is_am) {
    gpath_draw_filled(ctx, midday_blocks[0]);
  } else {
    gpath_draw_filled(ctx, midday_blocks[1]);
  }

}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(time_layer);
  battery_status(battery_state_service_peek());
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // init layers
  simple_bg_layer = layer_create(bounds);
  layer_set_update_proc(simple_bg_layer, bg_update_proc);
  layer_add_child(window_layer, simple_bg_layer);

  time_layer = layer_create(bounds);
 // layer_set_update_proc(hour_layer, hourblocks_update_proc);
  layer_set_update_proc(time_layer, time_update_proc);
  layer_add_child(window_layer, time_layer);


}

static void window_unload(Window *window) {
  layer_destroy(simple_bg_layer);
  layer_destroy(time_layer);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  // CURRENT TIME CIRCLE
  for (int i = 0; i < NUM_HOUR_BLOCKS; i++) {
    hour_blocks[i] = gpath_create(&HOUR_POINTS[i]);
  }
  for (int i = 0; i < NUM_MIN_BLOCKS; i++) {
    min_blocks[i] = gpath_create(&MIN_POINTS[i]);
  }

  for (int i = 0; i < 2; i++) {
    midday_blocks[i] = gpath_create(&MIDDAY_POINTS[i]);
  }


  // WEEKNUM AND WEEKDAY CIRCLE
  for (int i = 0; i < NUM_WN_BLOCKS; i++) {
    weeknum_blocks[i] = gpath_create(&WEEKNUM_POINTS[i]);
  }
  for (int i = 0; i < NUM_WD_BLOCKS; i++) {
    weekday_blocks[i] = gpath_create(&WEEKDAY_POINTS[i]);
  }


  // LOWER RIGHT CIRCLE
  for (int i = 0; i < NUM_BATTERY_BLOCKS; i++) {
    battery_blocks[i] = gpath_create(&BATTERY_POINTS[i]);
  }
  for (int i = 0; i < NUM_DATE_BLOCKS; i++) {
    date_blocks[i] = gpath_create(&DATE_POINTS[i]);
  }
  for (int i = 0; i < NUM_MONTH_BLOCKS; i++) {
    month_blocks[i] = gpath_create(&MONTH_POINTS[i]);
  }
  bt_block = gpath_create(&BT_POINTS);


  bt_status(bluetooth_connection_service_peek());
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  const GPoint center = grect_center_point(&bounds);

  // Push the window onto the stack
  const bool animated = true;
  window_stack_push(window, animated);



//  const uint32_t timeout_ms = 100;
//  timer = app_timer_register(timeout_ms, timer_callback, NULL);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(&battery_status);
  bluetooth_connection_service_subscribe(&bt_status);
}

static void deinit(void) {
  for (int i = 0; i < NUM_HOUR_BLOCKS; i++) {
    gpath_destroy(hour_blocks[i]);
  }
  for (int i = 0; i < NUM_MIN_BLOCKS; i++) {
    gpath_destroy(min_blocks[i]);
  }
  for (int i = 0; i < 2; i++) {
    gpath_destroy(midday_blocks[i]);
  }


  for (int i = 0; i < NUM_WN_BLOCKS; i++) {
    gpath_destroy(weeknum_blocks[i]);
  }
  for (int i = 0; i < NUM_WD_BLOCKS; i++) {
    gpath_destroy(weekday_blocks[i]);
  }


  for (int i = 0; i < NUM_BATTERY_BLOCKS; i++) {
    gpath_destroy(battery_blocks[i]);
  }
  for (int i = 0; i < NUM_DATE_BLOCKS; i++) {
    gpath_destroy(date_blocks[i]);
  }
  for (int i = 0; i < NUM_MONTH_BLOCKS; i++) {
    gpath_destroy(month_blocks[i]);
  }

  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}