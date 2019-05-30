#include <gtk/gtk.h>

typedef struct proxy_data{
    GtkWidget *buffer1;
    GtkWidget *buffer2;
    GtkWidget *cb1;
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

    const char* arg1[1];
    sprintf(arg1,"%d",cb1);
    char* args[]={"./gproxy_set.sh",entry1,entry2,arg1,(char*)0};
    execProcess(args);
    //g_print("%s:%s %d",entry1,entry2,cb1);
    gtk_main_quit();
}
int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkTextBuffer *field1;
    GtkTextBuffer *field2;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *cb1;

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
    cb1=gtk_check_button_new_with_label("env");

    data->cb1=cb1;

    table=gtk_table_new(3,2,FALSE);
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
    gtk_table_attach(GTK_TABLE(table), button, 1, 2, 2, 3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_container_add(GTK_CONTAINER(window),table);

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(on_window_destroy),NULL);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked),(gpointer)data);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}