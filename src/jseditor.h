#ifndef JSEDITOR_H
#define JSEDITOR_H

#include <QWidget>

namespace Ui {
class JSEditor;
}

class JSEditor : public QWidget
{
    Q_OBJECT

public:
    explicit JSEditor(QWidget *parent = nullptr);
    ~JSEditor();

private:
    Ui::JSEditor *ui;
};

#endif // JSEDITOR_H
