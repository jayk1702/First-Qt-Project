#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <Student.h>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Student Details");
    connect(ui->AddRecord,SIGNAL(clicked()),this,SLOT(on_AddRecord_clicked));
    connect(ui->Show,SIGNAL(clicked()),this,SLOT(on_Show_clicked()));
    connect(ui->SavetoFiles,SIGNAL(clicked()),this,SLOT(on_SavetoFiles_clicked));
    connect(ui->ReadfromFile,SIGNAL(clicked()),this,SLOT(on_ReadfromFile_clicked()));
    connect(ui->NextBtn,SIGNAL(clicked()),this,SLOT(OnpushBtnNextClicked()));
    connect(ui->ClearButton,SIGNAL(clicked()),this,SLOT(OnClearBtnClicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddRecord_clicked()
{
    Student stdObj;

      stdObj.name = ui->NameLine->text().toStdString();
      bool isValidName = true;
      for (char ch : stdObj.name) {
          if (!isalpha(ch))
          {
              isValidName = false;
              break;
          }
      }

      stdObj.rollno = ui->RollnoLine->text().toInt();
      bool isValidRollno = stdObj.rollno > 0;

      stdObj.age = ui->AgeLine->text().toInt();
      bool isValidAge = stdObj.age > 0;

      if (!isValidName || !isValidRollno || !isValidAge) {
          QMessageBox::warning(this, "Invalid Input", "Please enter valid data.");
          return;
      }

      if (ui->FemaleButton->isChecked()) {
          stdObj.sex = 'F';
      } else if (ui->MaleButton->isChecked()) {
          stdObj.sex = 'M';
      }

      stdObj.SubjectsMap["English"] = ui->EnglishText->toPlainText().toInt();
      stdObj.SubjectsMap["Maths"] = ui->MathsText->toPlainText().toInt();
      stdObj.SubjectsMap["Science"] = ui->ScienceText->toPlainText().toInt();
      stdObj.SubjectsMap["History"] = ui->HistoryText->toPlainText().toInt();
      stdObj.SubjectsMap["Geography"] = ui->GeographyText->toPlainText().toInt();

      StDetails.push_back(stdObj);

      QMessageBox::information(this, "Success", "Student details are saved.");
}

void MainWindow::on_Show_clicked()
{
    QString showData;
        for (unsigned int i = 0; i < StDetails.size(); ++i)
        {
            const Student& obj = StDetails[i];

            showData += "\nName of the student\n ";
            showData += "\nName : ";
            showData += obj.name.c_str();
            showData += "\nAge : ";
            showData += QString::number(obj.age);
            showData += "\nRoll No : ";
            showData += QString::number(obj.rollno);
            showData += "\nSex : ";
            showData += obj.sex.c_str();

            showData += "\nMarks of the student\n ";
            //map<string,int>::iterator it;
            for (auto it = obj.SubjectsMap.begin(); it != obj.SubjectsMap.end(); it++)
            {
                showData += "\n";
                showData += it->first.c_str();
                showData += " : ";
                showData += QString::number(it->second);
            }
        }
        ui->ShowBox->setText(showData);
}



void MainWindow::on_SavetoFiles_clicked()
{
    string line;
       fstream fio;

       fio.open("StudentData.txt", ios::app | ios::out | ios::in);

       for(const auto& obj: StDetails)
       {
           line += (obj.name + ",");
           line += (to_string(obj.age) + ",");
           line += (to_string(obj.rollno) + ",");
           line += (obj.sex + ",");
           for(const auto &sub : obj.SubjectsMap)
           {
               line += (sub.first.c_str());
               line += (":"+to_string(sub.second) + ",");
           }
           line.pop_back();
           fio << line << endl;
       }
    QMessageBox::information(this,"Student Record","Student details are saved.");
}



void MainWindow::on_ReadfromFile_clicked()
{

    QFile file("StudentData.txt");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Error", "Failed to open file.");
            return;
        }

        QTextStream in(&file);
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() >= 5) {
            ui->NameLine->setText(parts[0]);
            ui->AgeLine->setText(parts[1]);
            ui->RollnoLine->setText(parts[2]);

            if (parts[3] == "M")
            {
                ui->MaleButton->setChecked(true);
            }
            else if (parts[3] == "F")
            {
                ui->FemaleButton->setChecked(true);
            }

            ui->EnglishText->setText(parts[4]);
            ui->MathsText->setText(parts[5]);
            ui->ScienceText->setText(parts[6]);
            ui->HistoryText->setText(parts[7]);
            ui->GeographyText->setText(parts[8]);



        } else {
            QMessageBox::warning(this, "Error", "Invalid data format in the file.");
        }

        file.close();
}

void MainWindow::OnpushBtnNextClicked()
{
    static  int currentRecordIndex = 0;
    Student Stdobj;
    QFile file("StudentData.txt");
    if (!file.isOpen()) {
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::warning(this, "Error", "Failed to open file.");
                return;
            }
        }

        QTextStream in(&file);

        for (int i = 0; i < currentRecordIndex; ++i) {
            in.readLine();
        }

        if (!in.atEnd()) {
            QString line = in.readLine();
            QStringList info = line.split(',');

            QString studentInfo;
                   studentInfo += "\nName of the student\n ";
                   studentInfo += "\nName : " + info[0];
                   studentInfo += "\nAge : " + info[1];
                   studentInfo += "\nRoll No : " + info[2];
                   studentInfo += "\nSex : " + info[3];

                   studentInfo += "\nMarks of the student\n ";
                   for (int i = 4; i < info.size(); i++) {
                       studentInfo += "\nSubject " + QString::number(i - 3) + ": " + info[i];
                   }

                   ui->ShowBox->setText(studentInfo);

            ui->NameLine->setText(info[0]);
            ui->AgeLine->setText(info[1]);
            ui->RollnoLine->setText(info[2]);

            if (info[3] == "M") {
                ui->MaleButton->setChecked(true);
                ui->FemaleButton->setChecked(false);
            } else if (info[3] == "F") {
                ui->MaleButton->setChecked(false);
                ui->FemaleButton->setChecked(true);
            }

            ui->EnglishText->setText(info[4]);
            ui->MathsText->setText(info[7]);
            ui->ScienceText->setText(info[8]);
            ui->HistoryText->setText(info[6]);
            ui->GeographyText->setText(info[5]);

            ++currentRecordIndex;
        } else {

            file.seek(0);
            currentRecordIndex = 0;
        }
}

void MainWindow::OnClearBtnClicked()
{
    ui->NameLine->clear();
    ui->RollnoLine->clear();
    ui->AgeLine->clear();
    ui->MaleButton->setEnabled(true);
    ui->FemaleButton->setEnabled(true);

    ui->MaleButton->setChecked(false);
    ui->FemaleButton->setChecked(false);

    ui->EnglishText->clear();
    ui->MathsText->clear();
    ui->ScienceText->clear();
    ui->HistoryText->clear();
    ui->GeographyText->clear();
    ui->ShowBox->clear();
}



