#include <QUuid>

#include "uuidgenerator.h"

UUIDGenerator::UUIDGenerator(QObject *parent)
    : QObject{parent}
{}

QString UUIDGenerator::v4() const noexcept {
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}
