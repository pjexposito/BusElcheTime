#include "ventana_info.h"

static Window *s_main_window;
static TextLayer *s_label_layer;
static BitmapLayer *s_icon_layer;
int i_parada;
char i_lineas[200];

static GBitmap *s_icon_bitmap;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  s_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ICONO_PRINCIPAL);
  GRect bitmap_bounds = gbitmap_get_bounds(s_icon_bitmap);

  s_icon_layer = bitmap_layer_create(GRect(10, 10, bitmap_bounds.size.w, bitmap_bounds.size.h));
  bitmap_layer_set_bitmap(s_icon_layer, s_icon_bitmap);
  bitmap_layer_set_compositing_mode(s_icon_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_icon_layer));

  s_label_layer = text_layer_create(GRect(10, 10 + bitmap_bounds.size.h + 5, 124, 168 - (10 + bitmap_bounds.size.h + 10)));
  text_layer_set_text(s_label_layer, i_lineas);
  text_layer_set_background_color(s_label_layer, GColorClear);
  text_layer_set_font(s_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(s_label_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_label_layer);

  bitmap_layer_destroy(s_icon_layer);
  gbitmap_destroy(s_icon_bitmap);

  window_destroy(window);
  s_main_window = NULL;
}

void dialog_message_window_push(int parada, char lineas[200]) {
  if(!s_main_window) {
    i_parada = parada;
    memset(&i_lineas[0], 0, sizeof(i_lineas));
    strcat(i_lineas, lineas);
    s_main_window = window_create();
    window_set_background_color(s_main_window, GColorYellow);
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}
