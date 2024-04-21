#include "confetti.h"
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QRandomGenerator>

Confetti::Confetti()
{
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 30.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    world = new b2World(gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // QVector <b2Body> confettiVectors;
    b2BodyDef confettiDef;
    confettiDef.type = b2_dynamicBody;

    //set con


    //500 confetti pieces
    for(int i = 0; i < 600; i++)
    {
        b2Vec2 initialPosition (std::rand() % 1184, (std::rand()%200)-100);
        b2Body* body = world->CreateBody(&confettiDef);
        body->SetTransform(initialPosition, 30);
        confettiVectors.append(body);

        //apply force to confetti in some direction
        double xDir = (QRandomGenerator::global()->generateDouble() * velocityScaler) - (velocityScaler/2);
        double yDir = (QRandomGenerator::global()->generateDouble() * velocityScaler);

        b2Vec2 initialVelocity ((float)xDir, (float)yDir);
        confettiVectors.at(i)->SetLinearVelocity(initialVelocity);

    }
}

void Confetti::doConfettiSimulation()
{
    float32 timeStep = 1.0f/30.0f;
    int32 velocityIterations = 6;
    int positionIterations = 2;

    world->Step(timeStep, velocityIterations, positionIterations);
}
