#include "clangcompleter.h"
#include "ui_clangcompleter.h"

#include <iostream>

#include <QCompleter>
#include <QProcess>
#include <QDirModel>

ClangCompleter::ClangCompleter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClangCompleter)
{
    ui->setupUi(this);
    QCompleter *completer = new QCompleter(this);
    completer->setModel(new QDirModel(completer));
    ui->clangBinary->setCompleter(completer);
}

ClangCompleter::~ClangCompleter()
{
    delete ui;
}

void ClangCompleter::on_clangBinary_textEdited(const QString &arg1)
{
}

QStringList ClangCompleter::getCompletions(QString arg) {
  bool completeValue = false;
  QString origArg = arg;
  QString value;
  if (arg == "")
    arg = "#";
  if (arg.endsWith("=")) {
    arg += ",";
    completeValue = true;
  } else if (arg.contains("=")) {
    QStringList parts = arg.split("=");
    origArg = parts.front() + "=";
    parts.pop_front();
    arg = origArg + "," + parts.front();
  }
  QProcess pingProcess;
  QString exec = ui->clangBinary->text();
  QStringList params;
  std::cerr << "Completing '" << arg.toStdString() << "'\n";
  params << QString("--autocomplete=" + arg);
  pingProcess.execute(exec, params);
  pingProcess.start(exec, params);
  pingProcess.waitForFinished();
  QString output(pingProcess.readAllStandardOutput());
  QStringList result = output.split("\n");

  if (completeValue)
    for (QString &completion : result)
      completion = origArg + completion;
  return result;
}

void ClangCompleter::on_flags_textEdited(const QString &arg1)
{
  QStringList args = arg1.split(" ");
  if (args.empty()) {
    return;
  }
  QString toComplete = args.back();
  args.pop_back();
  QString prefix = args.join(" ");

  QStringList wordList = getCompletions(toComplete);
  for (QString &completion : wordList) {
    QStringList list = completion.split("\t");
    //std::cerr << "'" << prefix.toStdString() << "'" << std::endl;
    completion = prefix + (args.empty() ? "" : " ") + list.front();
  }
  QCompleter *completer = new QCompleter(wordList, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  //completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
  completer->setFilterMode(Qt::MatchStartsWith);
  ui->flags->setCompleter(completer);

  ui->flags->completer()->complete();
}
