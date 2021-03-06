#include <gtk/gtk.h>
#include <unistd.h>

typedef struct proxy_data{
    GtkWidget *buffer1;
    GtkWidget *buffer2;
    GtkWidget *cb1;
    GtkWidget *cb2;
    GtkWidget *cb3;
}proxy_data;

void execProcess(char **args)
{
    pid_t pid;
    pid=fork();
    if(pid==-1){
        g_print("Failed forming fork\n");
        return;
    }else if(pid==0){
      	execv(args[0],args);
      	perror("execv");
      	exit(0);
    }else{
      	int returnStatus;
      	waitpid(pid,&returnStatus,0);
    }
}
void on_window_destroy(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}
void on_button_clicked(GtkWidget *widget, gpointer data)
{
    proxy_data* pd=(proxy_data*)data; 
    const gchar *entry1=gtk_entry_buffer_get_text(pd->buffer1);
    const gchar *entry2=gtk_entry_buffer_get_text(pd->buffer2);
    const gint cb1=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pd->cb1));
    const gint cb2=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pd->cb2));
    const gint cb3=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pd->cb3));
    const char* arg1[1], *arg2[1], *arg3[1];
    sprintf(arg1,"%d",cb1);
    sprintf(arg2,"%d",cb2);
    sprintf(arg3,"%d",cb3);

    char* args[]={"/usr/local/lib/gproxy.sh",entry1,entry2,arg1,arg2,arg3,(char*)0};
    execProcess(args);
    gtk_main_quit();
}
int main(int argc, char *argv[])
{
    gint root=geteuid();

    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkTextBuffer *field1;
    GtkTextBuffer *field2;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *cb1;
    GtkWidget *cb2;
    GtkWidget *cb3;
    GtkWidget *warn;

    proxy_data* data=(proxy_data*)malloc(sizeof(proxy_data));
    gtk_init(&argc,&argv);

    data->buffer1=gtk_entry_buffer_new(NULL,-1);
    data->buffer2=gtk_entry_buffer_new(NULL,-1);

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),300,200);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    field1=gtk_entry_new_with_buffer(data->buffer1);
    field2=gtk_entry_new_with_buffer(data->buffer2);
    label1=gtk_label_new("Host");
    label2=gtk_label_new("Port");
    button=gtk_button_new_with_label("Save");
    warn=gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(warn),"<span background=\"#0022ff\" foreground=\"#ff0044\">Root permissions required</span>");

    cb1=gtk_check_button_new_with_label("env");
    cb2=gtk_check_button_new_with_label("bash");
    cb3=gtk_check_button_new_with_label("apt");

    data->cb1=cb1;
    data->cb2=cb2;
    data->cb3=cb3;

    table=gtk_table_new(4,2,FALSE);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_table_attach(GTK_TABLE(table), field1, 1, 2, 0, 1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), field2, 1, 2, 1, 2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_table_attach(GTK_TABLE(table), cb1, 0, 1, 2, 3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), cb2, 0, 1, 3, 4, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), cb3, 0, 1, 4, 5, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), button, 1, 2, 3, 4, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    if(root)
    {
      gtk_widget_set_sensitive(cb1,0);
      gtk_widget_set_sensitive(cb3,0);
      gtk_table_attach(GTK_TABLE(table), warn, 1, 2, 4, 5, 
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    }
    gtk_container_add(GTK_CONTAINER(window),table);

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(on_window_destroy),NULL);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked),(gpointer)data);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
