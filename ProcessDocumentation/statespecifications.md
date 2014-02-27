
State Specifications {#statespecifications}
====================

## State Specification SS000001: Create a 3D model of the mine surface 
\see @ref ssfr1

State Name                      | Description
--------------------------------|-----------------------------------------------------------------------------------------------------
start                           | Start condition for system.
buildingModelFromLocalCache     | The state of the system when it is building a 3D model from a local cache.
buildingModelFromExternalSource | The state of the machine when it is building a 3D model from an external source such as a datatbase.
dataOK                          | The state of the system after the 3D model of the mine surface has been created.
end                             | The state of the system after the 3d Model has been displayed.


Function / Parameter|Description
--------------------|---------------------------------------------------------------------------------------------
hasLocalDataCache   | true or false; the system has a local cache of dbQueryResult data matching the dbQuery supplied by the user.
getGPSData          | returns all GPS data, either sourced locally or built via an SQL query
buildModel          | build a 3D model.
displayModel        | display the model


|States / Next States                   |Transition Condition                                        	| Action              | 
|---------------------------------------|---------------------------------------------------------------|---------------------|
|start                                  | 							     	|                     |
|->start                                | no transition from start to start                          	|                     |
|->buildingModelFromLocalCache     	| local model definition matches desired model definition    	| buildModel          |
|->buildingModelFromExternalSource 	| no local model available                                   	| getGPSData          |
|->dataOK                          	| no                                                         	|                     |
|->end                            	| user supplied invalid args                                 	| usage, exit().      |
|buildingModelFromLocalCache         	|                                                         	|                     |
|->start                           	| no                               				|                     |
|->buildingModelFromLocalCache     	| no                                                      	|                     |
|->buildingModelFromExternalSource 	| no                                                      	|                     |
|->dataOK                          	| model built                                             	| displayModel        |
|->end                             	| no                                                      	|                     |
|buildingModelFromExternalSource     	|                                                         	|                     |
|->start                           	| no                                                      	|                     |
|->buildingModelFromLocalCache     	| no                                                      	|                     |
|->    buildingModelFromExternalSource 	| no                                                      	|                     |
|->    dataOK                          	| model built                                             	| displayModel        |
|->    end                             	| no                                                      	|                     |
|dataOK                              	|                                                         	|                     |
|->    start                           	| no                                                      	|                     |
|->    buildingModelFromLocalCache     	| no                                                      	|                     |
|->    buildingModelFromExternalSource 	| no                                                      	|                     |
|->    dataOK                          	| no                                                      	|                     |
|->    end                             	| model displayed                                         	| exit()              |
|end                                 	|                                                         	|                     |
|                                    	| no transitions from end to any state                    	|                     |
  
  

## State Specification Template Instructions ##

### Purpose ###
- To hold the state and state transition specifications for a system, class or program
- To support state-machine analysis during design, design reviews, and design inspections

### General ###
- This form shows each system, program, or routine state, the attributes of that state, and the transition conditions among the states.
- Use this template to document the state specifications during planning, design, test development, implementation and test.
- After implementation and testing, update the template to reflect the actual implemented product.

### State Name ###
- Name all of the program's states.
- Also enter each state name in the header space at the top of each 'States/Next States' section of the template.

### State Name Description ###
- Describe each state and any parameter values that characterize it. 
- For example, if a state is described by SetSize=10 and SetPosition=3, list SetSize=10 and SetPosition=4.

### Function / Parameter ###
- List the principal functions and parameters.
- Include all key variables or methods used to define state transitions or actions.

### Function / Parameter Description ###
- For each function, provide its declaration, parameters, and returns.
- For each parameter, define its type and significant values.

### Next State ###
- For each state, list the names of all possible next states.
- Include the state itself.

### Transition Condition ###
- List the conditions for transition to each next state.
- Use a mathematical or otherwise precise notation.
- If the transition is impossible, list "impossible", with a note saying why.

### Action ###
- List the actions taken with each state transition.

### Source ###
- Enter the source of the scenario action.
- Example sources could be user, program and system.

### Step ###
- Provide sequence numbers for the scenario steps. These facilitate reviews and inspections.

### Action ###
- Describe the action taken, such as:
  + Enter incorrect mode selection.
  + Provide error message.

### Comments ###
- List significant information relating to the action, such as:
  + User enters an incorrect value.
  + An error is possible with this action.


