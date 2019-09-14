#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //on_action_find_triggerded();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_action_find_triggerded()));
}
void MainWindow::on_action_find_triggerded()
{
    QDialog *findDlg = new QDialog(this);

    findDlg->setWindowTitle(tr("查找"));
    find_textLineEdit = new QLineEdit(findDlg);
    QPushButton *find_Btn = new QPushButton(tr("查找下一个"),findDlg);
    QVBoxLayout* layout = new QVBoxLayout(findDlg);
    layout->addWidget(find_textLineEdit);
    layout->addWidget((find_Btn));
    findDlg->show();
    connect(find_Btn,SIGNAL(clicked()),this,SLOT(show_findText()));
}
void MainWindow::show_findText()
{
    QString findText = find_textLineEdit->text();
    if(! ui->textEdit->find(findText,QTextDocument::FindBackward)){
        QMessageBox::warning(this,tr("查找失败"),tr("找不到该内容"));
    }
    ui->plainTextEdit->find()
}
