Getting Started
===============

Table of Contents
-----------------

- [Overview](#overview)
- [Registering Credentials](#registering-credentials)
- [Accessing Endpoints](#accessing-endpoints)
- [Making Transfers](#making-transfers)
- [Error Handling](#error-handling)

Overview
--------

One Data Share provides a uniform interface for accessing and transfering files between different otherwise incompatible
endpoints. The SDK allows users to:
- Register endpoints with One Data Share.
- View registered endpoints.
- View contents of endpoints.
- Create directories on endpoints.
- Remove files and directories from endpoints.
- Directly download files from endpoints.
- Efficiently transfer files between endpoints.
- View status of ongoing transfers.

Including the header file `onedatashare.h` will import all other headers required to use the SDK. This is the
recommended approach, although including each header file individually is also supported.

The API of the SDK is exposed through three primary classes: `Credential_service`, `Endpoint`, and `Transfer_service`.
Each class has a static `create` method that returns a new instance of the class. For all three classes, the `create`
method requires a One Data Share authentication token which must be obtained from the
[One Data Share website](https://www.onedatashare.org/).

All classes and structs defined by the SDK are located in the `One_data_share` namespace. Be sure to reference the
[documentation](https://didclab.github.io/CClient)
as you go through this tutorial.

Registering Credentials
-----------------------

One Data Share's primary goal is to provide a uniform interface for making efficient and reliable transfers between
different endpoints. To take advantage of this functionality, it is first necessary to have endpoints registered with
One Data Share. The SDK provides this functionality through the
[`Credential_service`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html)
class. A `Credential_service` object can be instantiated by calling its
[`create`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#a35d157e76a51329e44cea9df8c06c355)
method like so:
```
auto credential_service {One_data_share::Credential_service::create("YOURONEDATASHARETOKEN")};
```

`Credential_service::create`'s sole argument is the One Data Share authentication token obtained from the One Data Share website.

Before using the new `Credential_service` object, there are a few points to be aware of. The endpoint types supported by
One Data Share can be divided into two categories: **OAuth Endpoints** and **Credential Endpoints**. In the SDK, these
two sets of endpoint types are indicated by the
[`Oauth_endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#a638c03654eebf7030e7e5318f5ef0040)
and
[`Credential_endpoint_type`](https://didclab.github.io/CClient/namespaceOne__data__share.html#a8a22739a674b139dbcc385b50e2ab21a)
enumerations respectively. **OAuth Endpoints** are registered by visiting a URL provided by the endpoint type in which
you log into the endpoint and give One Data Share permission to use the endpoint. **Credential Endpoints** are
registered by giving the endpoint's credentials to One Data Share directly. One other note is the idea of
**Credential Identifiers**. These are strings associated with a specific endpoint registered on your account.
For **Oauth Endpoints**, the **Credential Identifier** is set automatically as the email of the account used to log into the endpoint. For
**Credential Endpoints**, the **Credential Identifer** is specified as part of uploading credentials to One Data Share.

To register an **OAuth Endpoint**, first use the
[`oauth_url`](https://didclab.github.io/CClient/classOne__data__share_1_1Credential__service.html#a83e81a11a3f1731958a5d11cd48163ca)
method.
```
auto url {credential_service.oauth_url(One_data_share::Oauth_endpoint_type::box)};
```
This method returns the URL you must visit to register an endpoint of the specified type.

Accessing Endpoints
-------------------



Making Transfers
----------------



Error Handling
--------------


