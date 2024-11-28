#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <direct.h>
#include <math.h>
#include "playlists.h"

// ************************************************************************************************
// Compilação necessária
// cd C:/Users/Amage/Desktop/Programacao/Playlists_Final_Prog2/Final_Project_Prog2_Playlists/bin/
// gcc -o main.exe main.c -mwindows `pkg-config --cflags --libs gtk+-3.0 glib-2.0 pango`

// ================================================================================================

// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=++=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=++=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// Funções referentes a tela

// Inicializações
void registerSignals(GtkBuilder *builder);
void switchPage(GtkButton *btn, gpointer user_data);

// -----------------------------------------------------------------

// Animações
void button_set_click_animation(GtkWidget *button); 
gboolean button_click_animation(gpointer data);

// --------------------------------------------------------------

// Edição
void change_label_text(GtkLabel *label, gchar *text);

// -------------------------------------------------------------------

// =======================================================================================================

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Ponteiros globais

// Main window
GtkWidget *window; 
GtkBuilder *builder;
GtkStack *main_stack;


// =========================================================================================================

int main (int argc, char *argv[]) {
    // Inicialização da tela
    // *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
    setlocale(LC_ALL, "en_US.utf8");
    gtk_init(&argc, &argv); // Init gtk

    // Inicialização dos ponteiros GTK
    GtkCssProvider *css_provider;
    // Iniciando interface XML para C
    builder = gtk_builder_new_from_file("../assets/ui_files/playlists.glade");
    gtk_builder_connect_signals(builder, NULL);

    // Inicialização de objetos principais da interface
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "../assets/ui_images/playlists_ico.png", NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Fecha a tela
    
    GdkGeometry hints_window;
    hints_window.max_width = 1000;  
    hints_window.max_height = 600; 
    gtk_window_set_geometry_hints(GTK_WINDOW(window), NULL, &hints_window, GDK_HINT_MAX_SIZE);

    // Carregar e aplicar o arquivo CSS
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "../assets/css/style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(css_provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Main stack principal
    main_stack = GTK_STACK(gtk_builder_get_object(builder, "main_stack"));

    // ================================================================================================

    // Funções da tela
    //GtkLabel *label1 = GTK_LABEL(gtk_builder_get_object(builder, "label1"));
    //change_label_text(label1, "teste");
    
    // ************************************************************************************************

    // Registrando sinais de callback para botões executarem funções
    registerSignals(builder);
    //g_signal_connect(window, "map", G_CALLBACK(set_cursor_window), NULL);

    gtk_widget_show_all(window);

    gtk_main();


    return 0;
}
/*
================================================================================================ 
Inicializations */

void switchPage(GtkButton *btn, gpointer user_data) {
    // Obtém o nome do botão clicado
    const gchar *button_name = gtk_widget_get_name(GTK_WIDGET(btn));

    /*// Frame 2 Elementos para limpar
    GtkLabel *fr2_label_elements[] = {NULL};
    GtkEntry *fr2_input_elements[] = {fr2_inp_user, fr2_inp_pass, NULL};

    // Frame 3 Elementos para limpar
    GtkLabel *fr3_label_elements[] = {NULL};
    GtkEntry *fr3_input_elements[] = {NULL};

    // Frame 5 Elementos para analisar e limpar
    GtkEntry *fr5_cave_inp_name = GTK_ENTRY(gtk_builder_get_object(builder, "fr5_cave_inp_name"));
    GtkLabel *fr5_cave_dragon_name_error = GTK_LABEL(gtk_builder_get_object(builder, "fr5_cave_dragon_name_error"));
    */

    // Altera a página visível da GtkStack com base no nome do botão
    // Frame 1
    if (g_strcmp0(button_name, "fr1_btn_music") == 0) {
        button_set_click_animation(GTK_WIDGET(btn));
        gtk_stack_set_visible_child_name(main_stack, "page_main");
    }

    if (g_strcmp0(button_name, "fr1_btn_playlist") == 0) {
        gtk_stack_set_visible_child_name(main_stack, "page_main");
    }
}

void registerSignals(GtkBuilder *builder) {

    // Registrar sinais de callback

    // Frame 1 Botões
    GObject *fr1_btn_music = gtk_builder_get_object(builder, "fr1_btn_music");
    g_signal_connect(fr1_btn_music, "clicked", G_CALLBACK(switchPage), main_stack);
}

/**********************************************************************************************
Settings 
*/
void setting_musics_list(int type, ) {

}


/*
================================================================================================
Animations */

void button_set_click_animation(GtkWidget *button) {
    gtk_widget_set_opacity(button, 0.7);
    g_timeout_add(100, button_click_animation, button);
}

gboolean button_click_animation(gpointer data) {
    GtkWidget *button = GTK_WIDGET(data);
    gtk_widget_set_opacity(button, 1.0);
    return FALSE;
}

/***********************************************************************************************/
/* Editions */

void change_label_text(GtkLabel *label, gchar *text) {
    gtk_label_set_text(label, text);
}

/*=============================================================================================*/