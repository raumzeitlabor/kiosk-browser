/**
Original Code by Peter Schultz, http://github.com/pschulktz/kiosk-browser
Edited by repat<repat[at]repat[dot]de>, March 2013.
*/
#include <stdio.h>
#include <signal.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <webkit/webkit.h>

gboolean on_key_press(GtkWidget*, GdkEventKey*, gpointer);

void reload_browser(int);

static WebKitWebView* web_view;
static GtkWidget *window;

// hardwired default page
gchar* DEFAULT_URL = "http:\/\/repat.de;
// hardẃired size
int HEIGHT = 1600;
int WIDTH = 900;

int main(int argc, char** argv) {
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), HEIGHT, WIDTH);
  // hardwired position GTK_WIN_POS_CENTER_ALWAYS
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

  g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());

  signal(SIGHUP, reload_browser);

  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

  webkit_web_view_load_uri(web_view, DEFAULT_URL);
  
  // maximize()
  gtk_window_maximize(GTK_WINDOW(window));
  gtk_window_fullscreen(GTK_WINDOW(window));
  gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

gboolean on_key_press(GtkWidget* window, GdkEventKey* key, gpointer userdata) {
  if(key->type == GDK_KEY_PRESS && key->keyval == GDK_F5) {
    reload_browser(0);
  }
  return FALSE;
}

void reload_browser(int signum) {
  webkit_web_view_reload_bypass_cache(web_view);
}

