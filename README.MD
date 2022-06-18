# Advisorbot
AdvisorBot is a command-line application in C++ that reads currency exchange data from a CSV file input and gives users relevant useful information to help users assess the market. The app has a list of functions and option available to the user where the user can obtain analytical insights from the bot based on the info the bot has read.


## How to install
-  Clone the repository git@github.com:ahmedMshaban/Advisorbot.git
-  Use Text editor, like VSC, 
-  A compiler, like GCC, to translate the C++ code into a language that the computer will understand.
    

## List of Commands

### help
Purpose: list all available commands
Parameters: None
Example: help

### prod
Purpose: list available products
Parameters: None
Example: prod

### min
Purpose: find minimum bid or ask for product in current time step
Parameters: <product> <ask/bid>
Example: min ETH/BTC ask

### max
Purpose: find maximum bid or ask for product in current time step
Parameters: <product> <ask/bid>
Example: max ETH/BTC ask

### avg
Purpose: Purpose: compute average ask or bid for the sent product for the last N time steps.
Parameters: <product> <ask/bid> <timesteps>
Example: avg ETH/BTC ask 10

### volatility
Purpose: Purpose: Compute the percentage of how much the product price changed over the last N timesteps
Parameters:  <min/max> <product> <type> <timesteps>
Example: volatility min ETH/BTC bid 1

### time
Purpose: state current time in dataset, i.e. which timeframe are we looking at
Parameters: None
Example: time

### step
Purpose: step (no parameters): move to next time step
Parameters: None
Example: step
Purpose: step <index>: print current time step index.
Parameters: <index>
Example: step
Purpose: step <reset>: reset the timestep to the initial from the start.
Parameters: <reset>
Example: step rese




