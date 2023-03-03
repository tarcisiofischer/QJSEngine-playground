#ifndef QJSENGINE_PLAYGROUND_MYJSFUNC_H
#define QJSENGINE_PLAYGROUND_MYJSFUNC_H

#include <QObject>
#include <QJSValue>

class MyJsFunction : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QJSValue f();
};

#endif //QJSENGINE_PLAYGROUND_MYJSFUNC_H
