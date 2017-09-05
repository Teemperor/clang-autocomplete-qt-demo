#ifndef CLANGCOMPLETER_H
#define CLANGCOMPLETER_H

#include <memory>

#include <QMainWindow>
#include <QCompleter>

namespace Ui {
class ClangCompleter;
}

class ClangCompleter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClangCompleter(QWidget *parent = 0);
    ~ClangCompleter();

private slots:
    void on_clangBinary_textEdited(const QString &arg1);
    void on_flags_textEdited(const QString &arg1);

private:
    Ui::ClangCompleter *ui;
};

#endif // CLANGCOMPLETER_H
