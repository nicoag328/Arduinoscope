#include <cairo.h>
#include <gtk/gtk.h>
#include <unistd.h>

#include "serial.h"
#include "queue.h"

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080
#define MEMORY_LIMIT 10320

struct queue_t queue;

int trigger_level = 100;

static void do_drawing(cairo_t *);

static void get_serial(GtkWidget* window) {
		while(1){
				u_int16_t* data;
				data = serial_read();
				insert(&queue, data[0]);
				insert(&queue, data[1]); 
		}

}

static gboolean on_click_event(GtkWidget *widget, GdkEventButton *event,
				gpointer user_data) {

		if (event->button == 1) {

				trigger_level = WINDOW_HEIGHT - WINDOW_HEIGHT / 4 + event->y;
		}

		return TRUE;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
				gpointer user_data)
{
		do_drawing(cr);

		return FALSE;
}

static void do_drawing(cairo_t *cr)
{
		cairo_set_source_rgb(cr, 0, 255, 0);
		cairo_set_line_width(cr, 2);
		cairo_move_to(cr, 0, WINDOW_HEIGHT / 2);

		while(!(read_queue(&queue, (MEMORY_LIMIT / 4) + 30) < trigger_level &
					   	read_queue(&queue, MEMORY_LIMIT / 4) >= trigger_level)) {

				continue;

		} 

		int i;
		for (i = (MEMORY_LIMIT / 4) - (WINDOW_WIDTH / 2); i <= (MEMORY_LIMIT / 4) + WINDOW_WIDTH - 2; i++ ) {
				cairo_move_to(cr, i - (MEMORY_LIMIT / 4), (WINDOW_HEIGHT / 4) * 3 - read_queue(&queue, i));
				cairo_line_to(cr, i - (MEMORY_LIMIT / 4) + 1, (WINDOW_HEIGHT / 4) * 3 - read_queue(&queue, i + 1));
		}

		cairo_stroke(cr);    
}


int main(int argc, char *argv[])
{
		GtkWidget *window;
		GtkWidget *darea;

		queue.array_size = MEMORY_LIMIT / 2;
		queue.array = calloc(MEMORY_LIMIT, 2);

		if (argc < 1 || argc > 2) {
				printf("Bad arguments");
				abort();
		}

		serial_init(argv);

		gtk_init(&argc, &argv);

		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

		darea = gtk_drawing_area_new();
		gtk_container_add(GTK_CONTAINER(window), darea);

		g_signal_connect(G_OBJECT(darea), "draw", 
						G_CALLBACK(on_draw_event), NULL); 

		g_signal_connect(window, "button-press-event",
						G_CALLBACK(on_click_event), NULL);

		g_signal_connect(window, "destroy",
						G_CALLBACK(gtk_main_quit), NULL);  

		g_thread_new(NULL, (GThreadFunc) get_serial, window);
		g_timeout_add(115, (GSourceFunc) gtk_widget_queue_draw, window);
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT); 
		gtk_window_set_title(GTK_WINDOW(window), "Arduinoscope");

		gtk_widget_show_all(window);

		gtk_main();

		free(queue.array);
		serial_free();

		return 0;
}
