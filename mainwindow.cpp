#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextCursor>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_findButton_clicked()
{
    QString word, text;

    if (!ui->lineEdit->text().isEmpty() && !ui->textEdit->toPlainText().isEmpty())
    {
        word = ui->lineEdit->text();
        text = ui->textEdit->toPlainText();

        QTextDocument *document = ui->textEdit->document();
        QTextCursor cursor(document);

        QTextCharFormat defaultFormat;
        defaultFormat.setForeground(Qt::black);
        cursor.select(QTextCursor::Document);
        cursor.mergeCharFormat(defaultFormat);

        cursor.beginEditBlock();

        QTextCharFormat colorFormat;
        colorFormat.setForeground(Qt::green);

        int index = text.indexOf(word);
        QVector<int> indices;
        while (index != -1)
        {
            cursor.setPosition(index);
            cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
            cursor.mergeCharFormat(colorFormat);
            indices.append(index);
            index = text.indexOf(word, index + word.length());
        }

        cursor.endEditBlock();
    }
    if (ui->lineEdit->text().isEmpty())
    {
        ui->labelError->setText("Помилка. Введіть слово для пошуку.");
        ui->labelError->setStyleSheet("color: red;");
    }
    if (ui->textEdit->toPlainText().isEmpty())
    {
        ui->labelError_2->setText("Помилка. Введіть текст у якому буде відбуватись пошук слова.");
        ui->labelError_2->setStyleSheet("color: red;");
    }
    if (!ui->lineEdit->text().isEmpty())
    {
        ui->labelError->setText("");
    }
    if (!ui->textEdit->toPlainText().isEmpty())
    {
        ui->labelError_2->setText("");
    }
}
