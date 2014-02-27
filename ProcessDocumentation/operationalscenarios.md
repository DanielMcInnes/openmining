
Operational Scenarios {#operationalscenarios}
=====================

## Operational Scenario OS000001: Create a 3D model of the mine surface 
\see @ref ssfr1

User Objective:     To create and display a 3D projection of the mine surface.

Scenario Objective: To illustrate how the system collects GPS data and plots the mine surface.

|Source | Step | Action                                           | Comments|
|-------|------|--------------------------------------------------|---------|
|user   | 1    | Tell the system to plot the mine surface.        |         |
|system | 2    | Get all GPS data from the database               |         |
|system | 3    | Create a subset of GPS data suitable for plotting|         |
|source | 4    | Display the data on the screen                   | stop    |



## Operational Scenario OS000002: Maintain a list of GPS vehicles and their current locations.
\see @ref ssfr2

User Objective:     To see a list of GPS vehicles and their current locations.

Scenario Objective: To illustrate how the system creates and maintains the list of GPS vehicles.

|Source | Step | Action                                                                  | Comments|
|-------|------|-------------------------------------------------------------------------|---------|
|user   | 1    | Call the system                                                         |         |
|system | 2    | Get all GPS data from the database                                      |         |
|system | 3    | Find all unique GPS vehicles described in the GPS data                  |         |
|source | 4    | Display the data on the screen                                          | stop    |


## Operational Scenario OS000003: Run Mode
\see @ref ssfr4

User Objective:    To see a 3D model of the mine surface and the vehicles upon it. 

Scenario Objective: To illustrate how the system runs in'live' mode

|Source | Step | Action                                                                  | Comments|
|-------|------|-------------------------------------------------------------------------|---------|
|user   | 1    | Call the system                                                         |         |
|system | 2    | Plot the mine surface                                                   |         |
|system | 3    | Plot all GPS vehicles at their last known locations on the mine surface | stop    |


## Operational Scenario OS000004: Replay Mode
\see @ref ssfr5

User Objective:    To see a replay of a 3D model of the mine surface and the vehicles upon it over a given timeframe. 

Scenario Objective: To illustrate how the system runs in 'replay' mode

|Source | Step | Action                                                                                         | Comments|
|-------|------|------------------------------------------------------------------------------------------------|---------|
|user   | 1    | Call the system, supplying the time frame to replay                                            |         |
|system | 2    | Get all GPS data from the database in chronological order                                      |         |
|system | 3    | Plot the mine surface.                                                                         |         |
|system | 4    | Starting at the earliest record, plot the appropriate vehicle at the approproate point.        |         |
|system | 5    | Plot each subsequent point until finished.                                                     | stop    |





\ThirdPartyDep doxygen v.1.8.5 has to be manually installed for tables on this page to be generated properly. The default version in the ubuntu 12.04 repositories is v.1.7, which doesn't support markdown out of the box.


## Operational Scenario Template Instructions ##

### Purpose ###
- To hold descriptions of likely operational scenarios followed during program use.
- To ensure that all significant usage issues are considered during program design.
- To specify test scenarios.

### General ###
- Use this template for complete programs, subsystems, or systems.
- Group multiple small scenarios on a single template, as long as they are clearly distinguished and have related objectives.
- List the major scenarios and reference other exception, error or special cases under comments.
- Use this template to document the operational specifications during planning, design, test development, implementation and test.
- After implementation and testing, update the template to reflect the actual implemented product.

### Scenario Number ###
- Where several scenarios are involved, reference numbers are needed.

### User Objective ###
- List the user's likely purpose for the scenario, for example, to log onto the system or to handle an error condition.

### Scenario Objective ###
- List the designer's purpose for the scenario, for example, to define common user errorsor to detail a test scenario.

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


