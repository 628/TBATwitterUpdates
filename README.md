# TBA Twitter Updates
[![License](https://img.shields.io/github/license/628/TBATwitterUpdates)](https://choosealicense.com/licenses/mit/)
[![LastCommit](https://img.shields.io/github/last-commit/628/TBATwitterUpdates)](https://github.com/628/TBATwitterUpdates/commits/master)  

*Created for [FRC Team 1718](http://www.fightingpi.org/)*

TBA Twitter Updates automagically pulls match data from TheBlueAlliance in real-time and posts updates to Twitter.

## Setup

### Twitter
In order to be able to send Tweets from the Twitter API, you must sign up for a [Twitter developer account](https://developer.twitter.com/en/apply-for-access.html).  
Be sure to setup an [app](https://developer.twitter.com/en/apps) and the Account Activity API [dev environment](https://developer.twitter.com/en/account/environments).
### The Blue Alliance
You need to create a webhook in order for TBA Twitter Updates to receive real-time match information, you can set one up from your [TBA Account](https://www.thebluealliance.com/account).  
You must also add the team you wish to send tweets for in [myTBA](https://www.thebluealliance.com/account/mytba#my-teams).
### Compiling
Before compiling, be sure that you have all of the required packages:
* libcurl
* liboauth
* libpthread
* libcrypto++

To compile, execute the following commands:
```
$ git clone https://github.com/628/TBATwitterUpdates.git
$ cd TBATwitterUpdates
$ mkdir src/build
$ cd src/build
$ cmake ..
$ make
$ sudo make install
```

## Usage

```
$ TBATwitterUpdates [pathToConfigFile]
```

## Config
Here's the config file format:
```json
{
  "port": "3141",
  "team": "frc1718",
  "secret": "verySecret",
  "accessToken": "",
  "accessTokenSecret": "",
  "consumerApiKey": "",
  "consumerApiKeySecret": ""
}
```

`port`: The port you want to run the webserver on (for the TBA webhook)  
`team`: The team you want to send tweets for (be sure to append "frc" to the beginning)  
`secret`: The webhook secret (Can be found in the [TBA Dashboard](https://www.thebluealliance.com/account))  
`accessToken`: Your Twitter access token  
`accessTokenSecret`: Your Twitter access token secret  
`consumerApiKey`: Your Twitter consumer API key  
`consumerApiKeySecret` Your Twitter consumer API key secret

## Contributing
Pull requests are welcome! If your change is a new feature, please create an issue before submitting a pull request.  
Please use the Allman indentation style.

## Acknowledgement
TBA Twitter Updates uses the following third-party libraries:
* [Pistache](https://github.com/oktal/pistache)
* [nlohmann JSON](https://github.com/nlohmann/json)

