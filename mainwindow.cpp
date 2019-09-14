#include "mainwindow.h"
int flag = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()  //新建
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    //打开文件选择对话框，选择文件，获取文件路径
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("Choose Source Directory");
    //fd->setDirectory(buf);
    fileDialog->setFileMode( QFileDialog::DirectoryOnly );
    QStringList filepath;
    if ( fileDialog->exec() == QDialog::Accepted )
    {
        filepath = fileDialog->selectedFiles();
        //srcDir.setPath(fileName.at(0));
        // QString fileName;        //fileName为全局变量
        fileName  = filepath.join(",");
        QString str;                        //写一个输入str的窗口
        QInputDialog dia(this);
        dia.setWindowTitle("Input filename");
        dia.setLabelText("Please input filename：");
        dia.setInputMode(QInputDialog::TextInput);//可选参数：DoubleInput  TextInput

        if(dia.exec() == QInputDialog::Accepted)
        {
            str = dia.textValue();
        }

        fileName = fileName + "\\" + str + ".c";
        QFile f(fileName);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->textEdit->setText("Fail！！");
            return;
        }
    }
    else
    {
        return;
    }


}

void MainWindow::on_pushButton_2_clicked()    //另存为
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    //打开文件选择对话框，选择文件，获取文件路径
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("List files(*.txt *.php *.dpl *.m3u *.m3u8 *.xspf *.c);;All files (*.*)"));
    if(fileName.isEmpty()){
        ui->textEdit->setText("用户取消操作！！");
    }
    else {
            //ui->textEdit->setText(fileName);//显示文件路径
            QFile f(fileName);
            if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                ui->textEdit->setText("Fail！！");
                return;
            }
            QTextStream Output(&f);
            Output.setCodec(codec);
            Output << ui ->textEdit->toPlainText();   //向文件中输入数据
         }
}

void MainWindow::on_pushButton_3_clicked()   //编译并运行
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
       QFile f("D:\S1.c");
       if(!f.open(QFile::WriteOnly | QFile::Text))
       {
           ui->textEdit->setText("Fail！！");
           return;
       }
       QTextStream Output(&f);
       Output.setCodec(codec);
       Output << ui ->textEdit->toPlainText();   //向文件中输入数据
       f.close();
       system("gcc D:\\S1.c -o D:\\test.exe 2>D:\\status.txt");    //目标源文件 test1.c 可修改     ，status为编译信息文件
        FILE *file;
         file = fopen("D:\\status.txt", "r");
         char s[100] ;
         int len;
         char *fi=fgets(s, 100, file) ;
          if(fi != NULL){    //如果含有error则返回
             while(fgets(s, 100, file) != NULL)

               {

               len= strlen(s);

               s[len-1] = '\0'; /*去掉换行符*/

               printf("%s %d \n",s,len - 1);

               }





            }
        else{
           WinExec("D:\\test.exe",SW_SHOW);
        }


}

void MainWindow::on_pushButton_4_clicked()     //保存
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString fileName = "123.c";
       QFile f(fileName);
       if(!f.open(QFile::WriteOnly | QFile::Text))
       {
           ui->textEdit->setText("Fail！！");
           return;
       }
       QTextStream Output(&f);
       Output.setCodec(codec);
       Output << ui ->textEdit->toPlainText();   //向文件中输入数据
}

void MainWindow::on_pushButton_5_clicked()      //隐藏/显示注释
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString fileName = "D:\S.c";    //测试用
    QFile f(fileName);                // fileName文件路径，设全局变量
    if(flag == 0)                     // flag 为一初始值为0的int型全局变量
    {
        // 去掉注释
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->textEdit->setText("Fail！！");
            return;
        }
        QTextStream Input(&f);
        Input.setCodec(codec);
        QString lineStr;
        QString se;
        QString str[4];
        int flag1=0;
        int flag2=0;
        int flag3=0;
        while(!Input.atEnd())
        {
            se = Input.read(1);
            str[0] = str[1];
            str[1] = str[2];
            str[2] = str[3];
            str[3] = se;
            //对于此种注释方式的应对
            if(str[1] == "\n" && flag1 == 1 && flag2 ==0)
            {
                flag1 = 0;
                if(flag3 != 1)
                {
                    lineStr = lineStr + str[1];
                    flag3 = 0;
                }
            }
            if(str[2] == "/" && str[3] == "/")
            {
                flag1 = 1;
                if(str[1] == "\n")
                {
                    flag3 = 1;
                }
            }
            /*对于此种注释方式的应对*/
            if(str[0] == "*" && str[1] == "/")
            {
                 flag2 =0 ;
                if(str[2] == "\n")
                {

                    continue;
                }
            }
            if(str[2] == "/" && str[3] == "*")
            {
                flag2 = 1;
            }
            if(flag1 == 0 && flag2 == 0)
            lineStr = lineStr + str[2];
        }
        if(flag1 == 0 && flag2 == 0)
        lineStr = lineStr + str[3];
        ui->textEdit->setText(lineStr);//显示文件内容
        f.close();
        flag=1;
        return;
    }
    if(flag ==1)
    {
        //显示注释
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->textEdit->setText("Fail！！");
            return;
        }
        QTextStream Input(&f);
        Input.setCodec(codec);
        QString lineStr;
        while(!Input.atEnd())
        {
             lineStr = lineStr + Input.readLine() + "\n";
        }
        ui->textEdit->setText(lineStr);//显示文件内容
        f.close();
        flag=0;
        return;
    }
}
void MainWindow::on_pushButton_6_clicked() //打开
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    //打开文件选择对话框，选择文件，获取文件路径
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("List files(*.txt *.php *.dpl *.m3u *.m3u8 *.xspf *.c);;All files (*.*)"));
    if(fileName.isEmpty()){
        ui->textEdit->setText("用户取消操作！！");
    }
    else {
            //ui->textEdit->setText(fileName);//显示文件路径
            QFile f(fileName);
            if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                ui->textEdit->setText("Fail！！");
                return;
            }
            QTextStream Input(&f);
            Input.setCodec(codec);
            QString lineStr;
            while(!Input.atEnd())
            {
                lineStr = lineStr + Input.readLine() + "\n";
            }
            ui->textEdit->setText(lineStr);//显示文件内容
            f.close();
    }
}







