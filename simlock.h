#ifndef SIMLOCK_H
#define SIMLOCK_H

#include <QObject>
#include <QString>
#include <simlockservice.h>
#include <notifications.h>

class SIMLock : public QObject
{
    Q_OBJECT

public:
    explicit SIMLock();
    virtual ~SIMLock();
    void Run();

private:
    SIMLockService simlock;
    bool canExit;

};

#endif // SIMLOCK_H
