#include "jseditor.h"
#include "ui_jseditor.h"

JSEditor::JSEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JSEditor)
{
    ui->setupUi(this);
}

JSEditor::~JSEditor()
{
    delete ui;
}
