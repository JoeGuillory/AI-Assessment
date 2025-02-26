# AI Documentation
This is Documentation for the classes that deal with AI.

## Behavior Component
This Component is used to calculate all the different type of steering force.

| Behavior                              | Functions                                          |
|---------------------------------------|----------------------------------------------------|
| Vector2 SeekForce()                   | Calculates the steering force for seek             |
| Vector2 FleeForce()                   | Calculates the steering force for flee             |
| Vector2 PursueForce()                 | Calculates the steering force for pursue           |
| Vector2 EvadeForce()                  | Calculates the sterring force for evade            |
| Vector2 ArriveForce()                 | Calculates the steering force for arrive           |
| Vector2 SeekForcePoint(Vector2 point) | Calculates the steering force to a specified point |
| void setTarget(Actor* target)         | makes the current target the inserted actor        |
| void setWeight(float weight)          | sets the strength of the steering force            |

## Seek, Flee, Pursue, Arrive, Evade, Wander
These are all children of behavior. These work as components as well. They are use to make the actor move according to the behavior is it named.

### Wander
This has a extra function to generate a random position for it to wander too.
| Wander                                | Functions                                          |
|---------------------------------------|----------------------------------------------------|
| Vector2 getDestination                | Generates a random position                        |

## Agent
This is the class for the AI actor.

| Agent                        | Functions                                                      |
|------------------------------|----------------------------------------------------------------|
| void setTarget(Actor* actor) | sets the target to the specified actor                         |
| void CheckState()            | checks the state machine for the current state it should be in |
