#include "src/app.h"
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    startApp(argv);

    gtk_main();

    return 0;
}