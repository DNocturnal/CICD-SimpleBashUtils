# CICD


Development of a simple **CI/CD** for the *SimpleBashUtils* project. Building, testing, deployment.

### 1. Gitlab-runner

##### install gitlab-runner on the virtual machine

##### register it for use in the current project

### 2. Building

##### In the `gitlab-ci.yml` file, add a stage to start the building via makefile from the project

##### Save artifacts to a random directory with a 30-day retention period.

### 3. Tests

#### Write a stage for **CI** that runs:
`a codestyle test`
`integration test`

### 5. Deployment 


#### Write a stage for **CD** that "deploys" the project on another virtual machine:
##### a bash script which copies the files received after the building (artifacts) into the */usr/local/bin* directory of the second virtual machine using **ssh** and **scp**

###  6. Notifications

##### Set up notifications of successful/unsuccessful pipeline execution via bot named "CI/CD" in *Telegram*
- The text of the notification must contain information on the successful passing of both **CI** and **CD** stages.
- The rest of the notification text may be arbitrary.
