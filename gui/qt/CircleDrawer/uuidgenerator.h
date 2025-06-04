#ifndef UUIDGENERATOR_H
#define UUIDGENERATOR_H

#include <QObject>
#include <QQmlEngine>
#include <QString>

class UUIDGenerator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit UUIDGenerator(QObject *parent = nullptr);

    Q_INVOKABLE QString v4() const noexcept;

signals:
};

#endif // UUIDGENERATOR_H
