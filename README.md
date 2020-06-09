CClient
=======

C++ Client for One Data Share.

Dependencies:
-------------
- Libcurl 7.47.0

Running Tests:
--------------
To run tests, a `token.txt` file must be created in the project root. This file should contain your One Data Share url
on the first line and your One Data Share authentication token on the second line as shown below:
```
http://localhost:8080
YOURAUTHENTICATIONTOKENGOESHERE
```
A more sophisticated method of defining these fields will be introduced at a later time.