#include "clangcompleter.h"
#include "ui_clangcompleter.h"
#include "QCompleter"
#include <iostream>

ClangCompleter::ClangCompleter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClangCompleter)
{
    ui->setupUi(this);
}

ClangCompleter::~ClangCompleter()
{
    delete ui;
}

void ClangCompleter::on_clangBinary_textEdited(const QString &arg1)
{
}

void ClangCompleter::on_flags_textEdited(const QString &arg1)
{
  QStringList wordList;
  wordList << "alpha" << "omega" << "omicron" << "zeta";
  QCompleter *completer = new QCompleter(wordList, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  //completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
  completer->setFilterMode(Qt::MatchStartsWith);
  ui->flags->setCompleter(completer);

  ui->flags->completer()->complete();
}
