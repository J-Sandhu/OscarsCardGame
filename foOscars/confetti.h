#ifndef CONFETTI_H
#define CONFETTI_H
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QGraphicsView>

class Confetti
{
public:
    Confetti();
    b2World *world;

    QVector <b2Body*> confettiVectors;

    int screenX; //have to scale to fit screen later
    int screenY;
    int confettiTimeLength;
    int showConfettiCount = 0;

    double minVelocity = 100.0;
    double velocityScaler = 100.0;

    void doConfettiSimulation();

public slots:

signals:
};

#endif // CONFETTI_H
