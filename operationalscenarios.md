
Operational Scenarios {#operationalscenarios}
=====================

## Operational Scenario OS000001: Create a 3D model of the mine surface ## {#OS1}
\see @ref ssfr1

User Objective:     To create and display a 3D projection of the mine surface.

Scenario Objective: To illustrate how the system collects GPS data and plots the mine surface.

|Source | Step | Action                                           | Comments|
|-------|------|--------------------------------------------------|---------|
|user   | 1    | Call the system                                  |         |
|system | 2    | Get all GPS data from the database               |         |
|system | 3    | Create a subset of GPS data suitable for plotting|         |
|source | 4    | Display the data on the screen                   | stop    |



\ThirdPartyDep #2 doxygen v.1.8.5 has to be manually installed for tables on this page to be generated properly. The default version in the ubuntu 12.04 repositories is v.1.7, which doesn't support markdown out of the box.


## Operational Scenario Template Instructions ##

### Purpose ###
- To hold descriptions of likely operational scenarios followed during program use.
- To ensure that all significant usage issues are considered during program design.
- To specify test scenarios.

### General ###
- Use this template for complete programs,, subsystems, or systems.
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


