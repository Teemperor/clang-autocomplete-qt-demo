#include "clangcompleter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClangCompleter w;
    w.show();

    return a.exec();
}
