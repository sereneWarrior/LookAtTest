## Sample Scene
Small sample scene with simple narrative structure.

### Content and goals

- [Project planning](###project-planning)
- [Narrative](###narrative-and-characters)
- [Player character](###player-character) 
- Objects
- Metahuman - as interactible component (NPC)
- Player character clothes 
- Inventory system
- Level / Scene 
- UI design and 
- Soundeffects
- Lighting, Particles effects

## Project planning

Next to working on the demo itself planning it was huge and important part.

I created a Miro board to capture my DOD's, milestones outline,gameplay loop and features and states of player, NPC and interactible objects as well as visual inspirations.
<figure>
<img
  src="images/planning.jpg"
  alt="Class diagramm">
  <figcaption style="font-weight: bold;">A small capture from the planning board containing a small moodboard for the scene set up and some ideas about iteractable objects</figcaption>
</figure>

Below the gameplay loop is drawn. The player is always in explore state, which terminates only if the time is up or all items to finish the game are found.
```mermaid
flowchart TD
    A(Start) --> B[Explore];
    B --> C{Is time up?};
    C -- yes --> D(End);
    C -- no --> B;
    B --> D{Have all items found?};
    D -- yes --> D;
    D -- no --> B;
```

The Explore state can be further defined as:
```mermaid
flowchart LR
    A((idle)) --> B((walk));
    A --> C((interact));
    C --> A;
    B --> A;
```

## Narrative and Characters

I tried to create a small narrative around the game. 
The game contains two characters. The player - who is non-human - and an NPC - human - who are captured in a barn. The environment is cold and therefore the human character gets colder and weaker with time. The  player character has to gather items to make a fire and keep the human alive. 
So, the game ends either by death of the NPC character or accomplishment of saving it.

The UE default mannequin *Quinn* fits that narative idea perfectly so I left her as player character. For the human character a MetaHuman is planned to use.

## Animations

#### Look at behaviour

<img
  src="images/LookAt.gif"
  alt="Class diagramm"
  width="50%"
  style="display: block; 
    margin-left: auto;
    margin-right: auto;">

When passing an interactible object the player actor turns the head to it's direction when close it.

<figure>
<img
  src="images/LookAt.jpg"
  alt="Class diagramm">
  <figcaption style="font-weight: bold;">UML class diagram showing classes handling the LookAtbehaviour and their relationships </figcaption>
</figure>

The movement of the bones is set up in the **Look** Control rig. The target location is specified with variable **LookAtLocation**  which is set in the **ABP_Base**'s AnimGraph (parent: UBaseAnimInstance). To toggle the head rotation two conditions need to met:
- The player has overlapped the **ALookAtTarget**'s trigger (a object reference will then be stored in a field of the Character)
- The angle of the head rotation needs to be in the specified range (set in the **LOOK_AT_RANGE_OFFSET** variable) 


<figure>
<img
  src="images/LookAtAnimGraph.jpg"
  alt="Class diagramm"
  width="49%">
  <img
  src="images/LookControl.jpg"
  alt="Class diagramm"
  width="49%">
  <figcaption style="font-weight: bold;">Left - Set up of Look control rig in ABP_Base; Right - Set up of the head rotation using LookAtLoaction coordinates to manipulate head, neck and spine bones</figcaption>
</figure>
