#ifndef CREATEBRAGGTEXTDOC_H
#define CREATEBRAGGTEXTDOC_H

#include <QPrinter>
#include <QTextDocument>

#include "braggparams.h"

namespace bragg {

void createBraggTextDoc(QTextDocument &doc, const braggParams &p);

}
#endif // CREATEBRAGGTEXTDOC_H
