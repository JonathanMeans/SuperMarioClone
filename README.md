# Super Mario Bros Clone

## Bug List
* While on an entity, Big Mario continuously falls through the entity slightly (creates a "vibration" motion)
  
## Resolved
* Mario lands on the far left or far right side on top of an entity and changes position, 
appearing on the left or right side of the pipe (see `test_entity_collision::MarioCanStandOnEdgeOfPipe`)