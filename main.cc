#include "myjsfunc.h"

#include <QCoreApplication>
#include <QJSEngine>
#include <QDebug>

#include <iostream>
#include <chrono>

QJSValue MyJsFunction::f()
{
    return 42;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Is it possible to call C++ from js?
    {
        QJSEngine engine;
        QJSValue myJsFunc = engine.newQObject(new MyJsFunction{});
        engine.globalObject().setProperty("MyPkg", myJsFunc);
        engine.installExtensions(QJSEngine::ConsoleExtension);
        auto m = engine.importModule("test3.js");
        auto r = m.property("do_run").call({"test1.js"});
        if (r.isError()) {
            qDebug()
                    << "Uncaught exception at line"
                    << r.property("lineNumber").toInt()
                    << ":" << r.toString();
        }
    }

    // Is it cheap to initialize the engine? (Loop below takes 63ms)
    {
        auto start = std::chrono::steady_clock::now();
        for (auto i = 0; i < 100; ++i) {
            QJSEngine engine;
            (void) engine;
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    // Is it cheap to eval a simple function? (Loop below takes ~2s with 100000 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        QJSEngine engine;
        engine.evaluate("var x = 1;");
        for (auto i = 0; i < 100000; ++i) {
            // Note: Variable redefinition? Or each eval is independent from the other?
            engine.evaluate("var x = 1;");
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    // Is it cheap to run the same from file? (Loop below takes ~1s with 100000 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        QJSEngine engine;
        for (auto i = 0; i < 100000; ++i) {
            engine.importModule("test1.js");
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    // Is it cheap to send simple variables and get return values? (Loop below takes 63ms with 100000 iterations)
    {
        auto start = std::chrono::steady_clock::now();
        QJSEngine engine;
        auto m = engine.importModule("test2.js");
        for (auto i = 0; i < 100000; ++i) {
            auto r = m.property("some_f").call({i}).toNumber();
            (void) r;
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    }

    return 0;
}
