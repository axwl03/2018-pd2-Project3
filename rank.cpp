#include "rank.h"
#include "ui_rank.h"

rank::rank(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rank)
{
    widget = parent;
    ui->setupUi(this);
    display();
}

rank::~rank()
{
    delete ui;
}
void rank::display(){
    QFile input("rank");
    if (!input.open(QIODevice::ReadWrite))
        QMessageBox::warning(this, "Oops!", "file not open");
    QTextStream s(&input);
    int i;
    s >> i;
    while(i != 0){
        score.push_back(i);
        s >> i;
    }
    input.close();
    QString str;
    str.append("Rank: \n\n");
    QFile output("rank");
    if(!output.open(QIODevice::WriteOnly))
        QMessageBox::warning(this, "Oops!", "file not open");
    QTextStream out(&output);
    if(score.size() == 0){
        ui->textBrowser->setText("Did not have score yet.");
        return;
    }
    std::sort(score.begin(),score.end());
    int rank = 1;
    for(int j = score.size() - 1; j >= 0; --j){
        if(score.size() - j > 10)
            break;
        str.append(QString::number(rank++));
        str.append(".\t");
        str.append(QString::number(score.at(j)));
        str.append("\n\n");
        out << score.at(j) << '\n';
    }ui->textBrowser->setText(str);
}
void rank::closeEvent(QCloseEvent *event){
    event->accept();
    widget->show();
    delete this;
}

