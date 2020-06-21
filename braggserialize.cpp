#include "braggserialize.h"

bool braggSerialize::saveToFile(QFile &file, const braggParams &p)
{
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_14);
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);

    // write header
    out << static_cast<quint32>(magicNumber);
    out << static_cast<qint32>(braggVersion);
    out << p;

    file.close();
    return true;
}


braggParams braggSerialize::loadFromFile(QFile &file)
{
    QDataStream in(&file);

    // Read and check the header
    quint32 magic;
    in >> magic;
    if (magic != this->magicNumber)
        throw std::runtime_error("Wrong file format.");

    // Read the version
    qint32 version;
    in >> version;
    if (version < braggVersion)
        throw std::runtime_error("File format too old.");
    if (version > braggVersion)
        throw std::runtime_error("File format too new, please upgrade Bragg Calculator");

    if (version == braggVersion)
        in.setVersion(QDataStream::Qt_5_14);

    // Read the actual data
    braggParams p {};
    in >> p;

    file.close();

    return p;
}
