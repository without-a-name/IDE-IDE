#include<stdio.h>
#include<gtk/gtk.h>
//#include<windows.h>

gboolean delete_handle(GtkWidget *self,GdkEvent *event,gpointer data);
//gboolean destroy_handle(GtkWidget *self,GdkEvent *event,gpointer data);

//bottun controlling
void NewName(void);
void CreateFile(void);
GtkWidget* createfw,* npath;

void SaveData(void);

void Openfile(void);
void ResetFilename(void);
GtkWidget* openfw,* opath;

void SaveAs(void);
void AsName(void);
GtkWidget* asfw,* apath;

void Compile(void);
void Run(void);
void ComRun(void);

char *filename;
FILE *fp;
//msgbox

GtkWidget *text;
int main(int argc, char* argv[]){
	//控件
	GtkWidget *window;
	GtkWidget *boxmain,* boxbutton;
//	GtkWidget *menufile, *menurun;
	GtkWidget *save, *new,* open,* saveas,* compile,* run,* comrun;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//赋值窗体
	gtk_window_set_title(GTK_WINDOW(window), "WhatYourName");
	gtk_widget_show(window);
	
	boxmain = gtk_vbox_new(FALSE,2);//主组装盒
	gtk_container_add (GTK_CONTAINER (window), boxmain);
	gtk_widget_show(boxmain);
	
	//按钮盒
	boxbutton = gtk_hbox_new(FALSE,5);
	gtk_box_pack_start(GTK_BOX(boxmain),boxbutton,FALSE,FALSE,10);
	gtk_widget_show(boxbutton);
	
	//menu_file
//	menufile = gtk_menu_item_new_with_label("files");
	
	
	//new
	new = gtk_button_new_with_label("new");
	gtk_box_pack_start(GTK_BOX(boxbutton),new,FALSE,FALSE,2);
	g_signal_connect (G_OBJECT (new), "clicked" , G_CALLBACK(NewName), NULL);
	gtk_widget_show(new);
	
	//save
	save = gtk_button_new_with_label("save");
	gtk_box_pack_start(GTK_BOX(boxbutton),save,FALSE,FALSE,0);
	g_signal_connect (G_OBJECT (save), "clicked" , G_CALLBACK(SaveData), NULL);
	gtk_widget_show(save);
	
	//open
	open = gtk_button_new_with_label("open");
	gtk_box_pack_start(GTK_BOX(boxbutton),open,FALSE,FALSE,2);
	g_signal_connect (G_OBJECT (open), "clicked" , G_CALLBACK(ResetFilename), NULL);
	gtk_widget_show(open);
	
	//saveas
	saveas = gtk_button_new_with_label("saveas");
	gtk_box_pack_start(GTK_BOX(boxbutton),saveas,FALSE,FALSE,0);
	g_signal_connect (G_OBJECT (saveas), "clicked" , G_CALLBACK(AsName), NULL);
	gtk_widget_show(saveas);
	
	//compile
	compile = gtk_button_new_with_label("compile");
	gtk_box_pack_start(GTK_BOX(boxbutton),compile,FALSE,FALSE,2);
	g_signal_connect (G_OBJECT (compile), "clicked" , G_CALLBACK(Compile), NULL);
	gtk_widget_show(compile);
	
	//run
	run = gtk_button_new_with_label("run");
	gtk_box_pack_start(GTK_BOX(boxbutton),run,FALSE,FALSE,0);
	g_signal_connect (G_OBJECT (run), "clicked" , G_CALLBACK(Run), NULL);
	gtk_widget_show(run);
	
	//compile and run
	comrun = gtk_button_new_with_label("comrun");
	gtk_box_pack_start(GTK_BOX(boxbutton),comrun,FALSE,FALSE,2);
	g_signal_connect (G_OBJECT (comrun), "clicked" , G_CALLBACK(ComRun), NULL);
	gtk_widget_show(comrun);
	
	//text
	text = gtk_text_view_new();
	gtk_widget_set_size_request(text,200,200);
	gtk_box_pack_start(GTK_BOX(boxmain),text,FALSE,FALSE,5);
	gtk_widget_show(text);

	gtk_signal_connect(GTK_OBJECT(window),"delete_event",G_CALLBACK(delete_handle),NULL);
//    gtk_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(destroy_handle),NULL);
	
	gtk_main();
	
	return 0;
}

//close window
gboolean delete_handle(GtkWidget *self,GdkEvent *event,gpointer data){
	gtk_main_quit();
    return FALSE;
}
/*gboolean destroy_handle(GtkWidget *self,GdkEvent *event,gpointer data){
    
    return FALSE;
}*/

void NewName(void){
	//新建一个窗体
	createfw = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(createfw), "输入文件名称");//
	gtk_widget_show(createfw);

	npath = gtk_entry_new();
	gtk_container_add (GTK_CONTAINER (createfw), npath);
	gtk_widget_show(npath);
	//按回车时开始给出路径
	g_signal_connect(npath,"activate",G_CALLBACK(CreateFile),NULL);
	return;
}

void CreateFile(void){
	const char* b = gtk_entry_get_text(npath);
	
	filename = strcat(b,".c");
    //使用“写入”方式创建文件
    fp=fopen(filename, "w");
    //关闭文件
//    fclose(fp);
	gtk_widget_hide(createfw);
	return;
}

void SaveData(void){
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	GtkTextIter start,end;
	
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
	
	const GtkTextIter s = start, e = end;
	const char* a = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&s,&e,FALSE);

    //将缓冲区文本写入文件
//    FILE *fp;
//    fp=fopen(filename,"w");
    if(fp==NULL)
    {
        printf("no file to save\n");
		/*MessageBox(NULL,TEXT("Please Create or Open a File to Save!"),
			TEXT("No File to Save!"),MB_OK);*/
        return;
    }
    fprintf(fp,"%s",a);
//    fclose(fp);
	return;
}

void ResetFilename(void){
	openfw = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(openfw), "输入文件名称");//
	gtk_widget_show(openfw);

	opath = gtk_entry_new();
	gtk_container_add (GTK_CONTAINER (openfw), opath);
	gtk_widget_show(opath);
	//按回车时开始给出路径
	g_signal_connect(opath,"activate",G_CALLBACK(Openfile),NULL);
	
	return;
	
}

void Openfile(){

	const gchar* b = gtk_entry_get_text(opath);
	
	filename = strcat((char*)b,".c");
	
	gtk_widget_hide(createfw);
	
    const gchar *a;
    
//    FILE *fp;
	fp = NULL;
    fp=fopen(filename,"r");    //打开文件
    int flen;
    //读取文件内容
    fseek(fp,0L,SEEK_END);
    flen=ftell(fp);
    a = (gchar *)malloc(flen);
    fseek(fp,0L,SEEK_SET);
    fread(a,flen,1,fp);
//    fclose(fp);
    
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	GtkTextIter start,end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);/*获得缓冲区开始和结束位置的Iter*/
	gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer),&start,&end);//清空缓冲区
	
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&start,a,strlen(a));/*插入文本到缓冲区*/
	return;
}

void AsName(void){
	asfw = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(asfw), "输入文件名称");//
	gtk_widget_show(asfw);

	apath = gtk_entry_new();
	gtk_container_add (GTK_CONTAINER (asfw), apath);
	gtk_widget_show(apath);
	//按回车时开始给出路径
	g_signal_connect(apath,"activate",G_CALLBACK(SaveAs),NULL);
	return;
}

void SaveAs(void){

	const gchar* b = gtk_entry_get_text(apath);
	
	filename = strcat((char*)b,".c");
	
	gtk_widget_hide(asfw);
	
	fp=fopen(filename, "w");
	
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	GtkTextIter start,end;
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
	
	const GtkTextIter s = start, e = end;
	const char* a = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer),&s,&e,FALSE);
	fprintf(fp,"%s",a);
	
	return;	
}

void Compile(void){}

void Run(void){}

void ComRun(void){}

